#include	<client.h>

#include	<unistd.h>
#include	<errno.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<stdio.h>
#include	<string.h>


int			resolve_host(char *s, struct addrinfo **addr_infop)
{
	struct addrinfo	hints = {0,0,0,0,0,0,0,0};

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(s, NULL, &hints, addr_infop))
		return (error(1, "getaddrinfo: couldn't resolve '%s'", s));
	return (0);
}

/*
**	establish the control connection
*/
int			init(int *cconp, t_opts *opts)
{
	int					sock;
	struct addrinfo		*addr_info;
	struct sockaddr_in	addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	if (resolve_host(opts->host, &addr_info))
		return (1);
	while (addr_info)
	{
		addr = *(struct sockaddr_in*)addr_info->ai_addr;
		addr.sin_port = htons((uint32_t)opts->port);
		info("attempting connection to %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		if (connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) >= 0)
			break ;
		info("connection failed");
		addr_info = addr_info->ai_next;
	}
	if (addr_info == NULL)
		return (error(1, "could not connect to host"));
	info("connected to %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	*cconp = sock;
	return (0);
}

/*
**	establish the data connection
**		return 0 is successful, -1 failure, errno if error
*/
int			init_data_connection(int ccon, int *dcon)
{
	int					status;
	char				*data;
	struct sockaddr_in	addr;
	int					fd;

	*dcon = -1;
	if ((status = get_response(ccon, &data)) != 227)
		return (status);
	status = parse_addr(&addr, &data);
	free(data);
	if (status)
		return (error(-1, "invalid address"));
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(-1, "socket"));
	addr.sin_family = AF_INET;
	info("attempting to connect to %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	if (connect(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
		return (error(-1, "connect"));
	info("established data connection with %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	*dcon = fd;
	return (0);
}
