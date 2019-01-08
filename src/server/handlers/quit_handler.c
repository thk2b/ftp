#include		<server.h>
#include		<protocol.h>

int				quit_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	(void)dcon;
	(void)req;
	(void)ctx;
	return (send_response(221, ccon));
}
