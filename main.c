#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// int main(void)
// {
//     int     fd;
//     char    *line;

//     fd = open("test.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     line = get_next_line(fd);
//     printf("%s", line);

//     line = get_next_line(fd);
//     printf("%s", line);

//     line = get_next_line(fd);
//     printf("%s", line);
//     return (0);
// }

int main(void)
{
    int fd;
    char buffer[6];
    fd = open("test.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("Error open the file");
        return 1;
    }
    ssize_t n;
    n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("%s", buffer);


    n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("%s", buffer);
    return 0;
}