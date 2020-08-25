#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        exit(-1);
    }
    
    char* file_name = argv[1];
    int fd = open(file_name, O_RDONLY);
    struct stat sb;
    
    if (fd == -1 || fstat(fd, &sb) == -1) {
        perror("Error! ");
        exit(-2);
    }
    
    char* mapped_file_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    int found;
    for (int i = 0; i < sb.st_size; i++) {
        if (mapped_file_ptr[i] == 'X') {
            found = 1;
            break;
        }
    }
    
    printf("'X' WAS%sfound!\n", (found) ? " " : " NOT ");
    munmap(mapped_file_ptr, sb.st_size);
    close(fd);
    
    exit(0);
}
