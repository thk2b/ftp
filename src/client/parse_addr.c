#include	<client.h>
#include	<arpa/inet.h>
#include	<string.h>
#include	<ctype.h>

static int	parse_ip(struct in_addr *addr, char **data)
{
	char	*s;
	char	*t;
	int		count;

	s = *data;
	t = s;
	count = 0;
	while (*s && count < 4)
	{
		if (*s == ',' && ++count)
			*s = '.';
		s++;
	}
	if (*s == 0 || *(s -1) != '.')
	return (1);
	*(s - 1) = '\0';
	if (inet_aton(t, addr) != 1)
		return (1);
	*data = s;
	return (0);
}

#include <printf.h>
static int	parse_port(in_port_t *portp, char **data)
{
	char			*s;
	unsigned char	port[2];

	s = *data;
	if (!isnumber(*s))
		return (1);
	port[0] = (unsigned char)atoi(s);
	if ((s = strchr(s, ',')) == NULL)
		return (1);
	if (!isnumber(*++s))
		return (1);
	port[1] = (unsigned char)atoi(s);
	// *portp = port[0] * 256 + port[1];
	*portp = htons(port[0] * 256 + port[1]);
	return (0);
}

int			parse_addr(struct sockaddr_in *addr, char **data)
{
	char	*s;

	if ((s = strchr(*data, '(')) == NULL)
		return (1);
	s++;
	if (parse_ip(&addr->sin_addr, &s))
		return (1);
	if (parse_port(&addr->sin_port, &s))
		return (1);
	return (0);
}

/*
#include <printf.h>
int main(int ac, char **av)
{
	struct sockaddr_in addr;

	(void)ac;
	int ret = parse_addr(&addr, av + 1);
	printf("%d - %s:%d\n", ret, inet_ntoa(addr.sin_addr), addr.sin_port);
}
*/
