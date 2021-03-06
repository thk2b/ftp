#include	<unistd.h>
#include	<netdb.h>
#include	<sys/socket.h>
#include	<string.h>

#include	<server.h>

t_opts		g_opts;

static int	resolve_host(char *s, in_addr_t *ip)
{
	struct in_addr		addr;
	struct addrinfo		hints = {0,0,0,0,0,0,0,0};
	struct addrinfo		*addr_info;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(s, NULL, &hints, &addr_info))
		return (error(1, "getaddrinfo: couldn't resolve '%s'", s));
	addr = ((struct sockaddr_in*)addr_info->ai_addr)->sin_addr;
	freeaddrinfo(addr_info);
	*ip = addr.s_addr;
	return (0);
}

int			parse_args(t_opts *opts, int ac, char **av)
{
	int		i;

	i = 1;
	opts->verbose = 0;
	while (i < ac)
		if (strcmp(av[i++], "-v") == 0)
			opts->verbose = 1;
	opts->ip = (in_addr_t)DEFAULT_PUBLIC_IP;
	opts->port = 8080;
	if (ac == 2)
		opts->port = (uint32_t)atoi(av[1]);
	else if (ac == 3)
	{
		if (resolve_host(av[1], &opts->ip))
			return (-1);
		opts->port = (uint32_t)atoi(av[2]);
	}
	return (0);
}

int			main(int ac, char **av)
{
	int		lcon;
	int		status;

	status = 0;
	if ((status = parse_args(&g_opts, ac, av)) == 1)
		return (usage_error(USAGE, av));
	else if (status)
		return (1);
	if ((status = init(&lcon, &g_opts)))
		return (status);
	status = run(lcon);
	close(lcon);
	return (status);
}
