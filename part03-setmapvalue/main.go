package main

import (
	"fmt"
	"os"
	"os/signal"
	"io/ioutil"
    "unsafe"
    "encoding/binary"
    "bytes"
	bpf "github.com/iovisor/gobpf/bcc"
)

/*
#cgo CFLAGS: -I/usr/include/bcc/compat
#cgo LDFLAGS: -lbcc
#include <bcc/bcc_common.h>
#include <bcc/libbpf.h>
void perf_reader_free(void *ptr);
*/
import "C"

func usage() {
    fmt.Printf("Usage: %v <ifdev>\n", os.Args[0])
    fmt.Printf("e.g.: %v eth0\n", os.Args[0])
    os.Exit(1)
}

type cacheData struct {
    I2          int32
    Sentence    []byte
}

func main() {
    var device string
    if len(os.Args) != 2 {
        usage()
    }
    device = os.Args[1]

    /* Module compilation */
    fmt.Println("Compiling....")
    source, err := ioutil.ReadFile("xdp_kern.c") // just pass the file name
    if err != nil {
        fmt.Print(err)
         os.Exit(1)
    }

    module := bpf.NewModule(string(source), []string{
        "-w",
    })
    defer module.Close()

    /* Load the xdp function */
    fn, err := module.Load("xdp_hash", C.BPF_PROG_TYPE_XDP, 1, 65536) //check xdp_kern.c, you can choose which function you want to use
    if err != nil {
        fmt.Fprintf(os.Stderr, "Failed to load xdp prog: %v\n", err)
        os.Exit(1)
    } else {
        fmt.Println("Successfully compile & load the xdp program")
    }

     /* Attach xdp into device */
    err = module.AttachXDP(device, fn)
    if err != nil {
        fmt.Fprintf(os.Stderr, "Failed to attach xdp prog: %v\n", err)
        os.Exit(1)
    } else {
        fmt.Println("Successfully attach program")
    }

    /* With deferred function to remove xdp after the program exits */
    defer func() {
        if err := module.RemoveXDP(device); err != nil {
            fmt.Fprintf(os.Stderr, "Failed to remove XDP from %s: %v\n", device, err)
        }
    }()

    /* Initialize bpf map table */
    table := bpf.NewTable(module.TableId("cache"), module)
    cd := cacheData{
        I2 : 1,
        Sentence: []byte("Hello"),
    }

    /* Try to set the bpf map "cache" */
    bufIdx := new(bytes.Buffer)
    err := binary.Write(bufIdx, binary.LittleEndian, 5)
    bufCD := new(bytes.Buffer)
    err := binary.Write(bufCD, binary.LittleEndian, cd)
    _ = table.Set(bufIdx,bufCD)
    /* */

    /* Waiting for interrupt signal to close the program */
    fmt.Println("The program is already started, hit CTRL+C to stop")
	sig := make(chan os.Signal, 1)
	signal.Notify(sig, os.Interrupt, os.Kill)
	<-sig
}