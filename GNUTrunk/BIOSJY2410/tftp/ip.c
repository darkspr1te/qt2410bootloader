//#include "../../inc/config.h"
#include "skbuff.h"
#include "eth.h"
#include "ip.h"
#include "arp.h"
#include "icmp.h"
#include "udp.h"
#include "utility.h"



static unsigned long local_ip = 0;

unsigned short ip_fast_csum(unsigned char * iph, unsigned int ihl)
{
	unsigned int sum, tmp1;

	__asm__ __volatile__(
	"ldr	%0, [%1], #4		@ ip_fast_csum		\n\
	ldr	%3, [%1], #4					\n\
	sub	%2, %2, #5					\n\
	adds	%0, %0, %3					\n\
	ldr	%3, [%1], #4					\n\
	adcs	%0, %0, %3					\n\
	ldr	%3, [%1], #4					\n\
1:	adcs	%0, %0, %3					\n\
	ldr	%3, [%1], #4					\n\
	tst	%2, #15			@ do this carefully	\n\
	subne	%2, %2, #1		@ without destroying	\n\
	bne	1b			@ the carry flag	\n\
	adcs	%0, %0, %3					\n\
	adc	%0, %0, #0					\n\
	adds	%0, %0, %0, lsl #16				\n\
	addcs	%0, %0, #0x10000				\n\
	mvn	%0, %0						\n\
	mov	%0, %0, lsr #16"
	: "=r" (sum), "=r" (iph), "=r" (ihl), "=r" (tmp1)
	: "1" (iph), "2" (ihl)
	: "cc");
	return sum;
} 

int ip_init(unsigned long ip)
{
	local_ip = ip;
	return 0;
}

int ip_rcv_packet(struct sk_buff *skb)
{
	struct iphdr *ip_hdr = (struct iphdr *)(skb->data);

	if (ntohl(ip_hdr->daddr) == local_ip)
	{
		skb->len = ntohs(ip_hdr->tot_len);
		skb_pull(skb, sizeof(struct iphdr));

		if (ip_hdr->protocol == UDP)
			udp_rcv_packet(skb);
		if(ip_hdr->protocol == ICMP)
			icmp_rcv_packet(skb);			
	}

	return 0;
}

int ip_send(struct sk_buff *skb, unsigned long ip, unsigned char proto)
{
	struct iphdr *ip_hdr;
	static unsigned short ip_id = 32;	
	unsigned char dest_eth_addr[ETH_ALEN];	

	if (arp_get_eth_addr(ip, dest_eth_addr))
		return -1;

	ip_hdr = (struct iphdr *)skb_push(skb, sizeof(struct iphdr));

	ip_hdr->ihl = 5;
	ip_hdr->version = 4;
	ip_hdr->tos = 0;
//	ip_hdr->tot_len = htons(32);
		ip_hdr->tot_len = htons(skb->len);	
	ip_hdr->id = htons(ip_id++);
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = 20;
	ip_hdr->protocol = proto;
	ip_hdr->check = 0;
	ip_hdr->saddr = htonl(local_ip);
	ip_hdr->daddr = htonl(ip);	
	ip_hdr->check = ip_fast_csum((unsigned char *)ip_hdr,ip_hdr->ihl);

	eth_send(skb, dest_eth_addr, ETH_P_IP);

	return 0;
}

void ip_skb_reserve(struct sk_buff *skb)
{
	eth_skb_reserve(skb);
	skb_reserve(skb, sizeof(struct iphdr));
}

unsigned long ip_get_source_ip(struct sk_buff *skb)
{
	struct iphdr *ip_hdr;
	
	ip_hdr = (struct iphdr *)(skb->buf + ETH_HLEN);
	return ntohl(ip_hdr->saddr);
}

