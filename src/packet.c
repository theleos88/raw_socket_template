#include "packet.h"

int create_socket_connection()
{
    int rawsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    setsockopt(rawsock , SOL_SOCKET , SO_BINDTODEVICE , "lo" , strlen("lo")+ 1 );
    if (rawsock < 0) {
        fprintf(stderr, "error: cannot creat socket\n");
        //return -1;
        exit(-1);
    }
    
    return rawsock;
}

void send_single_packet()
{
	printf("Pippo\n");
}

int read_answer(int *sock)
{
    uint8_t buff[BUF];
    struct iphdr *ip;
    struct udphdr *udp;
    ip = (struct iphdr *)buff;
    udp = (struct udphdr *) (buff + sizeof(struct iphdr));
    if(read(*sock, buff, sizeof(buff)) > 0) {
        //if(icmp->type == 0 && icmp->code == 0) return 1;
        //else return -1;
        dump_packets(buff, ip->tot_len);
    }
    return 0;
}

void dump_packets(uint8_t *data, uint32_t size)
{
    int i;
    struct iphdr *ip;


    ip= (struct iphdr *)data;
    /*if(ip->protocol != 0x90)
    {
        printf("Protocol was: %02x - Version %02x, Length %02x\n", ip->protocol, ip->version, ip->ihl);
        return;
    }*/
    
    fprintf(stderr, "\n");

    for(i=0;i<size;i++)
    {
        fprintf(stderr, "%02x ", data[i]);
        if((i+1)%16==0 ){
            fprintf(stderr, "\n");
        }
    }
    
    fprintf(stderr, "\n");
}
