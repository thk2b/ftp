#include	<client.h>

#include	<errno.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>

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
