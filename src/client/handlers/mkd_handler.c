#include	<client.h>
#include	<protocol.h>

int			mkd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int	status;

	(void)dcon;
	(void)ctx;
	if ((status = send_request(ccon, req)))
		return (status);
	return (get_response(ccon, NULL));
}
