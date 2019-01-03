#include	<server.h>

#include	<sys/socket.h>
#include	<arpa/inet.h>

t_state					sl_init(t_state state, void *vctx)
{
	int					sock;
	t_sl_ctx			*ctx;
	struct sockaddr_in	addr;

	(void)state;
	ctx = (t_sl_ctx*)vctx;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		return (ERROR);
	addr.sin_port = ctx->opts.port;
	addr.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (ERROR);
	if (listen(sock, 1024) < 0)
		return (ERROR);
	ctx->sock = sock;
	return (LISTEN);
}
