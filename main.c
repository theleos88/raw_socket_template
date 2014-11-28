#include "hdr/packet.h"
#include "hdr/algorithm.h"

int main( int argc, char** argv){
    printf("Ciao!\n");
    send_single_packet();
    custom_send();

    if(argc == 1) {
        printf("using standard settings...\n\n");
    }


        
	return 1;
}
