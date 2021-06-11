#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
void usage() {
    fprintf(stderr, "false command\n");
    exit(1);
}
int main(int argc, char **argv) {
    int fd;
    int c;
    int input_size;
    int read_size;
    struct stat tok;
    char input_file[64];
    char *buf;
    if (argc < 2) {
        usage();
    }
    strcpy(input_file, argv[1]);

    fd = open(input_file, O_RDWR);
    if(fd<0) {
        fprintf(stderr, "error trying to open or read file\nfd:\t%d\n", fd);
        exit(1);
    }
    fstat(fd, &tok);
    input_size = tok.st_size; //determinate size of input file
    buf = (char*)malloc(sizeof(input_size+1));
    if(buf==NULL) {
        fprintf(stderr, "error trying to allocate buf size\n");
        exit(1);
    }
    read_size = read(fd, buf, input_size);
    buf[input_size] = '\0';
    for(int i=0;i<input_size;i++) {
        c = *(buf+i);
        *(buf+i) = tolower(c);
    }
    lseek(fd, 0, SEEK_SET); //set the file's pointer to the start of the file || reposition the file offset to the file's start location
    write(fd, buf, read_size);
}