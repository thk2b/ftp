#include		<server.h>
#include		<protocol.h>

int				quit_handler(int ccon, int *dcon, t_request_ctx *req)
{
	(void)dcon;
	(void)req;
	return (send_response(221, ccon));
}
