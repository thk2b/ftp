#include		<client.h>
#include		<protocol.h>

int				pwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		res_status;

	(void)dcon;
	(void)ctx;
	if (send_request(ccon, req))
		return (1);
	if ((res_status = get_response(ccon, NULL)) == -1)
		return (-1);
	return (0);
}
