#include	<server.h>
#include	<string.h>
#include	<stdio.h>

/*
**	(a1,a2,a3,a4,p1,p2) -> 6 * 3 + 2 + 5
*/
int	format_addr(char *buf, struct sockaddr_in *addr)
{
	size_t	i;
	size_t	bi;
	char	*ip;
	unsigned char	port[2];

	if ((ip = inet_ntoa(addr->sin_addr)) == NULL)
		return (1);
	i = 0;
	bi = 0;
	buf[bi++] = '(';
	while (ip[i] && bi < 16)
	{
		if (ip[i] == '.' && ++i)
			buf[bi++] = ',';
		else
			buf[bi++] = ip[i++];
	}
	uint16_t p = htons((uint16_t)addr->sin_port);
	port[0] = (unsigned char)(p / 256);
	port[1] = (unsigned char)(p % 256);
	snprintf(buf + bi, 10, ",%d,%d)", port[0], port[1]);
	buf[26] = '\0';
	return (0);
}

/*
int main(int ac, char **av)
{
	(void)ac;
	struct sockaddr_in addr;
	char	buf[26];

	addr.sin_port = atoi(av[2]);
	inet_aton(av[1], &addr.sin_addr);
	int status = format_addr(buf, &addr);
	printf("%d - %s\n", status, buf);
}
*/
