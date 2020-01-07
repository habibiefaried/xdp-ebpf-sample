#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <uapi/linux/if_ether.h>
#include <uapi/linux/if_packet.h>
#include <uapi/linux/ip.h>
#include <uapi/linux/in.h>
#include <uapi/linux/udp.h>
#include <bcc/proto.h>

struct number {
    unsigned int num;
};

BPF_HASH(cache, int, int, 256);
BPF_HASH(cache2, int, struct number, 256);

int xdp_hash(struct xdp_md *ctx) {
	int key = 2;
	if(cache.lookup(&key)) {
		bpf_trace_printk("Tested %d\n",cache.lookup(&key));
    } else {
    	bpf_trace_printk("NULL VALUE DETECTED\n");
    }

    key = 3;
    if(cache2.lookup(&key)) {
    	struct number * n = cache.lookup(&key);
		bpf_trace_printk("Tested %d\n",n->num);
    } else {
    	bpf_trace_printk("NULL VALUE DETECTED\n");
    }

	return XDP_PASS;
}