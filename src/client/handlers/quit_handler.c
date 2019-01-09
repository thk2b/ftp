#include		<client.h>
#include		<protocol.h>

int				quit_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		status;

	(void)dcon;
	(void)ctx;
	if ((status = send_request(ccon, req)))
		return (status);
	if (status == 0 && (status = get_response(ccon, NULL)) == 221)
		return (-1);
	return (status);
}
