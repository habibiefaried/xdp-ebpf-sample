#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <uapi/linux/if_ether.h>
#include <uapi/linux/if_packet.h>
#include <uapi/linux/ip.h>
#include <uapi/linux/in.h>
#include <uapi/linux/udp.h>
#include <bcc/proto.h>

struct Leaf {
	int I2;
	char p[256];
};

BPF_HASH(cache, int, struct Leaf, 256);

int xdp_hash(struct xdp_md *ctx) {
	return XDP_PASS;
}