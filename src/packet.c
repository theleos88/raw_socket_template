#include "packet.h"

int create_socket_connection()
{
    int rawsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (rawsock < 0) {
        fprintf(stderr, "error: cannot creat socket\n");
        return -1;
    }
    
    return rawsock;
}

void send_single_packet()
{
	printf("Pippo\n");
}

void dump_packets(uint8_t *data, uint32_t size)
{
    int i;    
    for(i=0;i<size;i++)
    {
        fprintf(stderr, "%02x ", data[i]);
        if((i+1)%32==0 ){
            fprintf(stderr, "\n");
        }
    }
    
    fprintf(stderr, "\n");
}
