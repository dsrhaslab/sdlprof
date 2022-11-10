#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int main(){
    int pos = 0;
    int buffsize = 256;
    bool cont = true;

    int fd = open("/usr/local/lib/python3.8/dist-packages/tensorflow/python/keras/engine/data_adapter.py", O_RDONLY, S_IRWXU);
    int fd_1 = open("copy.py", O_CREAT | O_RDWR, S_IRWXU);
    //FILE* fp = fopen ("copy.txt", "w+");

    if(fd>0){ //&& fp>0){//fd_1>0){
        unsigned char* buffer = (unsigned char*) malloc(buffsize);

        cont=true;

        if(cont){//while(cont){
            memset(buffer, 0, buffsize);
            //int pos2 = (int) pread(fd, buffer, buffsize, pos);
            int pos3 = (int) read(fd, buffer, buffsize);
            write(fd_1,buffer,pos3);
            //pwrite(fd_1,buffer,pos2,3);
            if(pos3<=0) cont=false;
            else pos+=pos3;
        }

        close(fd);//dpi.close(fd);
        close(fd_1);//dpi.close(fd_1);
        //fclose(fp);

        free(buffer);
    }

    int N=5;
    void *ptr = mmap ( NULL, N*sizeof(int),PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if(ptr == MAP_FAILED){ 
        printf("Mapping Failed\n");
        return 1;
    }

    int err = munmap(ptr, 10*sizeof(int));
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    
    return 0;
}
