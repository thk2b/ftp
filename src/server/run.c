#include	<server.h>

#include	<errno.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>

int			run(int lcon)
{
	int					conn;
	struct sockaddr_in	addr;
	socklen_t			len;

	len = sizeof(struct sockaddr_in);
	while ((conn = accept(lcon, (struct sockaddr*)&addr, &len)) > 0)
	{
		info("accepted connection from %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
		close(conn);
	}
	if (conn < 0)
		return (error(errno, "accept"));
	return (0);
}
