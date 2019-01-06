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
	pid_t				pid;

	len = sizeof(struct sockaddr_in);
	while ((conn = accept(lcon, (struct sockaddr*)&addr, &len)) > 0)
	{
		info("accepted connection from %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
		if ((pid = fork()) == -1)
			error(errno, "fork");
		else if (pid == 0)
		{
			close(lcon);
			_exit(controller(conn));
		}
		close(conn);
	}
	if (conn < 0)
		return (error(errno, "accept"));
	return (0);
}
