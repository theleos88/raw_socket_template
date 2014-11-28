#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define BUF 1024

typedef struct iphdr *ip_ptr;
typedef struct udphdr *udp_ptr;

int create_socket_connection();
void send_single_packet();

/*Dump & test functions */
void dump_packets(uint8_t *data, uint32_t size);