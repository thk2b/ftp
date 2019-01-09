#include	<server.h>
#include	<protocol.h>
#include	<sys/stat.h>

int			mkd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	(void)dcon;
	(void)ctx;

	if (mkdir(req->args[1], 0775) == -1)
		return (error_conn(ccon, 550, 1, "mkdir"));
	return (send_response(257, ccon));
}
