#include	<client.h>

#include	<unistd.h>
#include	<errno.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<stdio.h>
#include	<string.h>

/*
**	establish the control connection
*/
int			init(int *cconp, t_opts *opts)
{
	int					sock;
	struct sockaddr_in	addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(errno, "socket"));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((uint32_t)opts->port);
	if (inet_aton(opts->ip, &addr.sin_addr) != 1)
		return (error(errno, "inet_aton"));
	info("attempting connection to %s:%d", inet_ntoa(addr.sin_addr), opts->port);
	if (connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (error(errno, "connect"));
	info("connected to %s:%d", inet_ntoa(addr.sin_addr), opts->port);
	*cconp = sock;
	return (0);
}

/*
**	establish the data connection
*/
int			init_data_connection(int ccon, int *dcon)
{
	int					status;
	char				*data;
	struct sockaddr_in	addr;
	int					fd;

	*dcon = -1;
	if (write(ccon, "PASV \r\n", 7) != 7)
		return (error(errno, "write"));
	if ((status = get_response(ccon, &data)) != 227)
		return (info("failed to open data connection"));
	status = parse_addr(&addr, &data);
	free(data);
	if (status)
		return (info("invalid address"));
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(errno, "socket"));
	info("attempting to connect to %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
	if (connect(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
		return (error(errno, "connect"));
	*dcon = fd;
	return (0);
}
