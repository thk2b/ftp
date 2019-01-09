#include	<client.h>
#include	<protocol.h>

int			mkd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int	res_status;

	(void)dcon;
	(void)ctx;
	if (send_request(ccon, req))
		return (1);
	res_status = get_response(ccon, NULL);
	return (0);
}
