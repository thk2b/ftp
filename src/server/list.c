#include		<server.h>

#include		<dirent.h>
#include		<errno.h>
#include		<string.h>
#include		<sys/stat.h>
#include		<fcntl.h>
#include		<stdio.h>
#include		<pwd.h>
#include		<grp.h>
#include		<time.h>
#include		<stdlib.h>

static int		print_perms(struct stat *sb, int fd)
{
	mode_t	m;

	m = sb->st_mode;
	return (dprintf(fd, "%c%c%c%c%c%c%c%c%c%c\t",
		S_ISDIR(m) ? 'd' : '-',
		m & S_IRUSR ? 'r' : '-',
		m & S_IWUSR ? 'w' : '-',
		m & S_IXUSR ? 'x' : '-',
		m & S_IRGRP ? 'r' : '-',
		m & S_IWGRP ? 'w' : '-',
		m & S_IXGRP ? 'x' : '-',
		m & S_IROTH ? 'r' : '-',
		m & S_IWOTH ? 'w' : '-',
		m & S_IXOTH ? 'x' : '-'
	) != 11);
}
static int		print_nlinks(struct stat *sb, int fd)
{
	return (dprintf(fd, "%2ld\t", sb->st_nlink) == -1);
}
static int		print_owner(struct stat *sb, int fd)
{
	struct passwd	*p;
	struct group	*g;

	if ((p = getpwuid(sb->st_uid)) == NULL)
		return (1);
	if ((g = getgrgid(sb->st_gid)) == NULL)
		return (1);
	return (dprintf(fd, "%s\t%s\t", p->pw_name, g->gr_name)
		!= (int)(2 + strlen(p->pw_name) + strlen(g->gr_name)));
}
static int		print_size(struct stat *sb, int fd)
{
	return (dprintf(fd, "%ld\t", sb->st_size) == -1);
}
static int		print_time(struct stat *sb, int fd)
{
	char	*s;
	size_t	len;

	if ((s = ctime(&sb->st_mtim.tv_sec)) == NULL)
		return (1);
	len = strlen(s);
	s[len - 1] = '\0';
	return (dprintf(fd, "%s\t", s) != (int)strlen(s) + 1);
}
static int		print_name(char *name, int fd)
{
	char	*filename;

	if ((filename = strrchr(name, '/')) == NULL)
		filename = name;
	else
		filename++;
	return (dprintf(fd, "%s\n", filename) == (int)strlen(filename));
}

static int		list_file(char *path, int fd)
{
	struct stat	sb;

	if (stat(path, &sb))
		return (error(1, "stat"));
	if (print_perms(&sb, fd)
	|| print_nlinks(&sb, fd)
	|| print_owner(&sb, fd)
	|| print_size(&sb, fd)
	|| print_time(&sb, fd)
	|| print_name(path, fd))
		return (1);
	return (0);
}

static int		list_dir(char *path, int out_fd)
{
	struct dirent	*de;
	int				status;
	DIR				*dir;

	if ((dir = opendir(path)) == NULL)
		return (1);
	while ((de = readdir(dir)))
		if (*de->d_name != '.' && (status = list_file(de->d_name, out_fd)))
			break ;
	closedir(dir);
	return (0);
}

int				list(char *path, int out_fd)
{
	struct stat	sb;
	int			status;

	if (stat(path, &sb) == -1)
	{
		if (errno == ENOENT || errno == EPERM)
			return (-1);
		return (error(1, "stat"));
	}
	if (S_ISREG(sb.st_mode))
		return (list_file(path, out_fd));
	status = list_dir(path, out_fd);
	return (status);
}

// int main(int ac, char **av)
// {
// 	(void)ac;

// 	printf("\n%d\n", list(av[1], 1));
// 	system("leaks a.out");
// }
