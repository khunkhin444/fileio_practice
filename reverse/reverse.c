#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void usage() {
    fprintf(stderr, "false command\n");
    exit(1);
}
int main(int argc, char **argv) {
    int fd;
    int c;
    int input_size;
    struct stat tok;
    char input_file[64];
    char *buf;
    char *buf2;
    // char *buf2;
    char tmp;
    if (argc != 2) {
        usage();
    }
    strcpy(input_file, argv[1]);
    fd = open(input_file, O_RDONLY, 0600);
    if(fd<0) {
        fprintf(stderr, "error trying to open or read file\nfd:\t%d\n", fd);
        exit(1);
    }
    fstat(fd, &tok);
    input_size = tok.st_size; //determinate size of input file
    buf = (char *)malloc(input_size+1);
    buf2 = (char *)malloc(input_size+1);
    read(fd, buf, input_size);
    if(buf==NULL) {
        fprintf(stderr, "error trying to allocate buf size\n");
        exit(1);
    }
    close(fd);
    // buf[input_size] = '\0';
    int len = strlen(buf);
    char *ptr = buf;
    char *qtr = buf2;
    ptr+=(len-1);
    for(int i=(len-1);i>=0;i--) {
        *qtr++=*ptr--;
    }
    // qtr++;
    *qtr = '\0';
    fd = open(input_file, O_WRONLY, 0600);
    write(fd, buf2, input_size);
    close(fd);
}