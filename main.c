#include "hdr/packet.h"
#include "hdr/algorithm.h"

#include <string.h>

int main( int argc, char** argv){
    printf("Ciao! I am the Main\n");
    send_single_packet();
    custom_send();

    int sockfd, test = 1;
    int data_size=128;
    uint8_t *packet;
    size_t packet_size;
    
    ip_ptr ip;
    udp_ptr udp;
    struct sockaddr_in server;
    
    uint8_t buffer[128];
    memset(buffer, 0, 128);
    char *tests = "hello";
    memcpy(buffer, tests, 5);
    
    if(argc != 3) {
        printf("usage: pong [sourceip] [destip]\n");
        return -1;
    }

    if(argc == 1) {
        printf("using standard settings...\n\n");
    }

    
    ip = (struct iphdr *) malloc(sizeof(struct iphdr));
    udp = (struct udphdr *) malloc(sizeof(struct udphdr));
    
    packet = (uint8_t *) malloc(sizeof(struct iphdr) + sizeof(struct udphdr)+data_size+1);
    packet_size = sizeof(struct iphdr) + sizeof(struct udphdr)+data_size+1;
    
    memset(packet, '\0',sizeof(packet));
        
    ip = (struct iphdr *)packet;
    udp = (struct udphdr *) (packet + sizeof(struct iphdr));
    
    //strcpy(packet+sizeof(struct iphdr)+sizeof(struct udphdr),tests);

    ip->ihl = 5;
    ip->version = 4;
    ip->tos = 0;
    ip->tot_len = packet_size;    
    ip->id = htons(getuid());
    ip->ttl = 255;    
    ip->protocol = IPPROTO_UDP;
    ip->saddr = inet_addr(argv[1]);
    ip->daddr = inet_addr(argv[2]);
    
    udp->source=0x2222;
    udp->dest=0x6666;
    
    
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
   
    if( (setsockopt(sockfd, IPPROTO_IP,IP_HDRINCL,&test,sizeof(test))) < 0) {
      printf("couldnt set IP_HDRINCL\n");
      return -1;
    }
    
    /*icmp->checksum = 0;
    icmp->checksum = in_cksum((unsigned short *)icmp,sizeof(struct icmphdr)+sizeof(tests)+1);
    ip->check = in_cksum((unsigned short *)ip, sizeof(struct iphdr));*/
    
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);  /* doesnt matter */
    server.sin_addr.s_addr = inet_addr(argv[2]);
    
    if( (sendto(sockfd,packet,ip->tot_len,0,(struct sockaddr *)&server,
                    sizeof(struct sockaddr))) < ip->tot_len) {
      printf("cannot send the packet\n");
      return -1;
    }
    printf("Sent packet size: %d!\n", ip->tot_len);
    
    //if(read_answer(&sockfd) == 1) printf("received answer- host is up\n");
    //else printf("didnt receive answer\n");
    //return 0;



        
	return 1;
}
