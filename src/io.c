#include		<io.h>
#include		<sys/mman.h>
#include		<unistd.h>
#include		<stdlib.h>

int		read_file(int from, int to)
{
	char	buf[BUF_SIZE];
	ssize_t	nr;

	nr = BUF_SIZE;
	while (nr > 0)
	{
		if ((nr = read(from, buf, BUF_SIZE)) == -1)
			return (1);
		if (write(to, buf, nr) != nr)
			return (1);
	}
	return (0);
}

int		write_file(int to, int fd, struct stat *sb)
{
	void	*file;

	if (sb->st_size == 0)
		return (0);
	if ((file = mmap(NULL, sb->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (1);
	if (write(to, file, sb->st_size) != sb->st_size)
		return (1);
	if (munmap(file, sb->st_size) == -1)
		return (1);
	return (0);
}
