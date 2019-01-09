#ifndef IO_H
# define IO_H

#include		<sys/stat.h>
#define			BUF_SIZE 4096

int		read_file(int from, int to);
int		write_file(int to, int fd, struct stat *sb);

#endif
