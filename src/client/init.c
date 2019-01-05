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

	info("attempting connection to %s:%d", opts->ip, opts->port);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(errno, "socket"));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(opts->port);
	if (inet_aton(opts->ip, &addr.sin_addr) != 1)
		return (error(errno, "inet_aton"));
	if (connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (error(errno, "connect"));
	info("connected to %s:%d", opts->ip, opts->port);
	*cconp = sock;
	return (0);
}
