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
	int I1;
	int I2;
	char Sentence[256];
} chown_event_t;

BPF_PERF_OUTPUT(chown_events);

int xdp_perf(struct xdp_md *ctx) {
	chown_event_t event = {};
	event.I1 = 500;
	event.I2 = 1000;
	event.Sentence[0] = "H";
	event.Sentence[1] = "\0";
	chown_events.perf_submit(ctx, &event, sizeof(event));
	return XDP_PASS;
}