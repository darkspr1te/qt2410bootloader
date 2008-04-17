#ifndef __ICMP_H
#define	__ICMP_H

#include "skbuff.h"
#include "ip.h"

struct icmphdr
{
	unsigned char type;
	unsigned char code;
	unsigned short check;
}__attribute__((__packed__));

int icmp_rcv_packet(struct sk_buff *skb);

#endif