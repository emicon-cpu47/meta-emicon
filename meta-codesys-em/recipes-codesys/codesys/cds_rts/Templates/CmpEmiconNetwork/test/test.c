
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <errno.h>
#include <netinet/in.h>
#include <net/route.h>

#if defined(__GLIBC__) && __GLIBC__ >=2 && __GLIBC_MINOR__ >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#else
#include <sys/types.h>
#include <netinet/if_ether.h>
#endif

#include <arpa/inet.h>

int sys_set_ip(char *iface_name, char *ip_addr, char *mask,
	       char *gateway_addr);

// prints unsigned int in binary form
void printBits(unsigned int num)
{
   const int bit_cnt = sizeof(unsigned int) * 8;
   unsigned int mask = (1 << (bit_cnt - 1));

   do
   {
      fprintf(stderr, "%u", (num & mask) != 0?1:0);
      mask >>= 1;
   } while (mask > 0);
   fprintf(stderr, "\n");
}

void main(void)
{
	sys_set_ip("eth0", "192.168.0.10", "255.255.254.0", "192.168.0.1");
	
	return;
}


int sys_set_ip(char *iface_name, char *ip_addr, char *mask,
	       char *gateway_addr)
{
// ip route flush dev interface
// ip addr flush dev interface
// ip addr add 192.168.1.2/24 broadcast 192.168.1.255 dev eth0
// ip route add default via 192.168.1.1

	uint32_t n;
	uint32_t n_mask = 1;
	uint8_t bits = 0;
	int i = 0;
	char str[100];
	char buffer [33];

	inet_pton(AF_INET, mask, &n);
	fprintf(stderr, "%d\n", n);

	printBits(n);

	while (n > 0) {
		if (n & n_mask)
			bits++;

		n = n >> 1;
	}

	fprintf(stderr, "%d\n", bits);

 //   	sprintf(str, "ip route flush dev %s", iface_name);
	// system(str);

	// sprintf(str, "ip addr flush dev %s", iface_name);
	// system(str);

	// sprintf(str, "ip addr add %s/%d dev %s", ip_addr, i - 1, iface_name);
	// fprintf(stderr, "%s\n", str);
	// system(str);

	// sprintf(str, "ip route add default via  %s", gateway_addr);
	// fprintf(stderr, "%s\n", str);
	// system(str);

	return 0;
}

