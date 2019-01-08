#include		<client.h>
#include		<protocol.h>

int				pwd_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int		res_status;
	(void)dcon;

	if (send_request(ccon, req))
		return (1);
	if ((res_status = get_response(ccon, NULL)))
		return (1);
	return (0);
}
