#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <uapi/linux/ptrace.h>
#include <bcc/proto.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <linux/ipv6.h>

typedef struct {
	u32 I1;
	int I2;
	char Sentence[256];
} chown_event_t;

BPF_PERF_OUTPUT(chown_events);


char *strcpy_local(char *dest, const char *src) {
	//taken from: https://github.com/torvalds/linux/blob/master/lib/string.c
	char *tmp = dest;
	while ((*dest++ = *src++) != '\0');
	return tmp;
} 

int xdp_perf(struct xdp_md *ctx) {
	chown_event_t event = {};
	event.I1 = 500;
	event.I2 = 1000;
	strcpy_local(event.Sentence,"Hello World");
	chown_events.perf_submit(ctx, &event, sizeof(event));
	return XDP_PASS;
}