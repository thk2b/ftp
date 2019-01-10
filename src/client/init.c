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

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	opts->addr.sin_family = AF_INET;
	info("attempting connection to %s:%d", inet_ntoa(opts->addr.sin_addr), ntohs(opts->addr.sin_port));
	if (connect(sock, (struct sockaddr*)&opts->addr, sizeof(struct sockaddr_in)) < 0)
		return (error(1, "connect"));
	info("connected to %s:%d", inet_ntoa(opts->addr.sin_addr), ntohs(opts->addr.sin_port));
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
