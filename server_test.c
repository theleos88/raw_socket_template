#include "hdr/packet.h"
#include "hdr/algorithm.h"

int main( int argc, char** argv){
 
    /*Buffers and communication*/
    char buffer[BUF];
    char *dats;
    size_t bytes;
    int sock_d;
    
    /*Network*/
    ip_ptr ip;
    udp_ptr udp;
    
    printf("This is the server!\n");
    send_single_packet();
    custom_send();
    
    if(argc == 1) {
        printf("using standard settings...\n");
    }
    
    
    ip = (struct iphdr *)buffer;
    udp = (struct udphdr *) (buffer + sizeof(struct iphdr));
    dats = buffer+(sizeof(struct iphdr)+sizeof(struct udphdr));

    sock_d = create_socket_connection();
    
    while( (bytes = read(sockfd, buffer, BUFFSIZE)) > 0) {
        //printf("tcp:  dport=%d, sport=%d, from=%s", ntohs(udp->dest),ntohs(udp->source),inet_ntoa(ip->saddr));
        dump_packets(buffer, bytes);
        memset(buffer, '\0', BUF);
    }
   
    return 1;
}
