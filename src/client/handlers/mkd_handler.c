#include	<client.h>
#include	<protocol.h>

int			mkd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	(void)dcon;
	(void)ctx;
	if (send_request(ccon, req))
		return (1);
	return (get_response(ccon, NULL));
}
