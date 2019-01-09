#include		<client.h>
#include		<protocol.h>

int				pwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		res_status;
	int		status;

	(void)dcon;
	(void)ctx;
	if ((status = send_request(ccon, req)))
		return (status);
	if ((res_status = get_response(ccon, NULL)) == -1)
		return (-1);
	return (0);
}
