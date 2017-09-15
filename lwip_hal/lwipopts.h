/**
 ********************************************************************************************
 @file: lwipopts.h
 @author: ABB Robotics Shanghai - System Integration Department
 @brief: lwIP Options Configuration
 @note: this file has been derived from the lwIP/src/include/lwip/opt.h header file
 @history:
    - 2015.07.10, v1.0 created by Matteo Russi
 ********************************************************************************************
 */
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* General Options -------------------------------------------------------------------------*/
/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT		1
/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS						1
/**
 * NO_SYS_NO_TIMERS==1: Drop support for sys_timeout when NO_SYS==1
 * Mainly for compatibility to old versions.
 */
#define NO_SYS_NO_TIMERS			1

/* Memory Options --------------------------------------------------------------------------*/
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT				4
/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE					(64*1024)
/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF				16//100
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB			4//6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB			16//10
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN		8//6
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG			16//12
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT		10

/* Pbuf Options ----------------------------------------------------------------------------*/
/* PBUF_LINK_HLEN: the number of bytes that should be allocated for a link level header */
#define PBUF_LINK_HLEN				16

/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE				16//10

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE			1536//500

/* TCP Options -----------------------------------------------------------------------------*/
#define LWIP_TCP					1
#define TCP_TTL						255
/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ				0
/* TCP Maximum segment size. */
#define TCP_MSS						(1500 - 40)/* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */
/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF					(6*TCP_MSS)//(4*TCP_MSS)
/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */
#define TCP_SND_QUEUELEN			(2* TCP_SND_BUF/TCP_MSS)
/* TCP receive window. */
#define TCP_WND						(4*TCP_MSS)//(2*TCP_MSS)

/* ICMP Options ----------------------------------------------------------------------------*/
#define LWIP_ICMP					1

/* DHCP Options ----------------------------------------------------------------------------*/
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP					1

/* UDP Options -----------------------------------------------------------------------------*/
#define LWIP_UDP					1
#define UDP_TTL						255

/* Statistics Options ----------------------------------------------------------------------*/
#define LWIP_STATS					0
#define LWIP_PROVIDE_ERRNO			1

/* Link Callback Options -------------------------------------------------------------------*/
/**
 * LWIP_NETIF_HOSTNAME==1: use DHCP_OPTION_HOSTNAME with netif's hostname
 * field.
 */
#define LWIP_NETIF_HOSTNAME			1
#define LWIP_NETIF_HOSTNAME_NAME	APP_NAME
/* LWIP_NETIF_LINK_CALLBACK==1: Support a callback function from an interface
 * whenever the link changes (i.e., link down)
 */
#define LWIP_NETIF_LINK_CALLBACK	1

/* Checksum Options ------------------------------------------------------------------------*/
/*
The Tiva C allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
#define CHECKSUM_BY_HARDWARE
#ifdef CHECKSUM_BY_HARDWARE
	/* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
	#define CHECKSUM_GEN_IP			0
	/* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
	#define CHECKSUM_GEN_UDP		0
	/* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
	#define CHECKSUM_GEN_TCP		0
	/* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
	#define CHECKSUM_CHECK_IP		0
	/* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
	#define CHECKSUM_CHECK_UDP		0
	/* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
	#define CHECKSUM_CHECK_TCP		0
	/* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
	#define CHECKSUM_GEN_ICMP		0
#else
	/* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
	#define CHECKSUM_GEN_IP			1
	/* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
	#define CHECKSUM_GEN_UDP		1
	/* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
	#define CHECKSUM_GEN_TCP		1
	/* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
	#define CHECKSUM_CHECK_IP		1
	/* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
	#define CHECKSUM_CHECK_UDP		1
	/* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
	#define CHECKSUM_CHECK_TCP		1
	/* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/
	#define CHECKSUM_GEN_ICMP		1
#endif

/* Sequential Layer Options ----------------------------------------------------------------*/
/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN				0

/* Socket Options --------------------------------------------------------------------------*/
/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET					0
/**
 * LWIP_TCP_KEEPALIVE==1: Enable TCP_KEEPIDLE, TCP_KEEPINTVL and TCP_KEEPCNT
 * options processing. Note that TCP_KEEPIDLE and TCP_KEEPINTVL have to be set
 * in seconds. (does not require sockets.c, and will affect tcp.c)
 */
#define LWIP_TCP_KEEPALIVE			1

/* LwIP Debug Options ----------------------------------------------------------------------*/
//#define LWIP_DEBUG				1


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LWIPOPTS_H__ */

