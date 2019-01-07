#include		<client.h>
#include		<protocol.h>

int				quit_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int		status;

	(void)dcon;
	if ((status = send_request(ccon, req)))
		return (1);
	if (status == 0 && (status = get_response(ccon)) == 221)
		return (-1);
	return (status);
}
