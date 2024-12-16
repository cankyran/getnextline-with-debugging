#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char *line;
    int fd;

    fd = open("test.txt", O_RDONLY);

    while (line = get_next_line(fd))
        printf("IN MAIN turning line\n                                %s", line);
    
    // line = get_next_line(fd);
    // printf("%s", line);

    // line = get_next_line(fd);
    // printf("%s", line);
    close(fd);
    return 0;

}