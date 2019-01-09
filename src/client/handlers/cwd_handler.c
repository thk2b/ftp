#include		<client.h>
#include		<protocol.h>

int				cwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	(void)dcon;
	(void)req;
	(void)ctx;
	if (send_request(ccon, req))
		return (1);
	get_response(ccon, NULL);
	return (0);

}
