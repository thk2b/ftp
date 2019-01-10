#include	<server.h>

#include	<errno.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<netdb.h>



int			init(int *lconp, t_opts *opts)
{
	int					sock;
	struct sockaddr_in	addr;
	int					reuse_addr;
	extern t_opts		g_opts;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (error(1, "socket"));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((uint16_t)opts->port);
	addr.sin_addr.s_addr = g_opts.ip;
	info("attempting to bind to %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	reuse_addr = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int)) < 0)
		return (error(1, "setsockopt"));
	if ((bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) < 0)
		return (error(1, "bind"));
	if (listen(sock, BACKLOG) < 0)
		return (error(1, "listen"));
	info("listening for connections on %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	*lconp = sock;
	return (0);
}
