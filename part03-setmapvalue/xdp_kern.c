#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <linux/ipv6.h>

struct Leaf {
	int I2;
	char p[256];
};

BPF_HASH(cache, int Key, struct Leaf, 128);

int xdp_hash(struct xdp_md *ctx) {
	return XDP_PASS;
}