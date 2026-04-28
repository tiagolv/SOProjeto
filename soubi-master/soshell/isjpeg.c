#include"shell.h"
#include <unistd.h>
#include <fcntl.h>

int isjpeg(int fileDescriptor) {
    // O arquivo deve estar aberto
    unsigned char b[4];
    int n = read(fileDescriptor, b, 4);

    if (n){
        lseek(fileDescriptor, 0, SEEK_SET);
    }

    if (b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0){
        return 1;
    }
    
    return 0;
}