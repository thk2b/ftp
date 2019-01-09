#include		<server.h>
#include		<protocol.h>

#include		<unistd.h>

int				quit_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	(void)req;
	(void)ctx;
	if (*dcon)
	{
		close(*dcon);
		*dcon = -1;
	}
	return (send_response(221, ccon));
}
