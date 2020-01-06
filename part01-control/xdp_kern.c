#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <linux/ipv6.h>

int xdp_prog_pass(struct xdp_md *ctx) {
	return XDP_PASS;
}

int xdp_prog_drop(struct xdp_md *ctx) {
	return XDP_DROP;
}

int xdp_prog_aborted(struct xdp_md *ctx) {
	return XDP_ABORTED;
}