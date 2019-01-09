#include	<server.h>

#include	<errno.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<signal.h>
#include	<string.h>

static void		sigchld(int sig)
{
	int	status;

	(void)sig;
	while (waitpid(-1, &status, WNOHANG) > 0)
	{
		info("child process terminated with status %d", status);
	}
}

static t_client	*init_client(struct sockaddr_in *addr)
{
	t_client *c;

	if ((c = malloc(sizeof(t_client))) == NULL)
		return (NULL);
	c->pwd = strdup("/");
	memcpy(&c->addr, addr, sizeof(struct sockaddr_in));
	return (c);
}

int				run(int lcon)
{
	int					conn;
	struct sockaddr_in	addr;
	socklen_t			len;
	pid_t				pid;
	t_client			*client;

	signal(SIGCHLD, sigchld);
	len = sizeof(struct sockaddr_in);
	while ((conn = accept(lcon, (struct sockaddr*)&addr, &len)) > 0)
	{
		if ((client = init_client(&addr)) == NULL)
		{
			close(conn);
			return (error(1, "init_client"));
		}
		info("accepted connection from %s:%d", inet_ntoa(addr.sin_addr), addr.sin_port);
		if ((pid = fork()) == -1)
			error(1, "fork");
		else if (pid == 0)
		{
			close(lcon);
			_exit(controller(conn, client));
		}
		free(client->pwd);
		free(client);
		close(conn);
	}
	if (conn < 0)
		return (error(1, "accept"));
	return (0);
}
