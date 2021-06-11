#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define max_buf 4098

void usage() {
    fprintf(stderr, "false command\n");
    exit(1);
}

int main(int argc, char **argv) {
    int fd_in, fd_out;
    int input_size;
    int output_size;
    int read_size;
    struct stat tok;
    char input_file[64];
    char output_file[64];
    char *buf;

    if (argc < 3) {
        usage();
    }
    strcpy(input_file, argv[1]);

    strcpy(output_file, argv[2]);

    fd_in = open(input_file, O_RDONLY);

    fd_out = open(output_file, O_CREAT|O_WRONLY, 600); //permission 600 linux: owner/admin can write, read file

    if(fd_in<0 || fd_out <0) {
        fprintf(stderr, "error trying to open, create or read file\nfd_in:\t%d\nfd_out:\t%d\n", fd_in,fd_out);
        exit(1);
    }

    fstat(fd_in, &tok);

    input_size = tok.st_size; //determinate size of input file

    buf = (char*)malloc(sizeof(input_size+1));
    if(buf==NULL) {
        fprintf(stderr, "error trying to allocate buf size\n");
        exit(1);
    }

    read_size = read(fd_in, buf, input_size); //*if the input_size is > 4096 then the file is not fully copy
    if(input_size > max_buf) {
        fprintf(stderr,"file size is exceed, leftover:%d to copy\n", input_size-max_buf);
    }
    buf[input_size] = '\0';
    
    write(fd_out, buf, read_size);
}