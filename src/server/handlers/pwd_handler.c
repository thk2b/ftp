#include		<server.h>
#include		<protocol.h>

int				pwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int			status;
	t_client	*c;

	(void)dcon;
	(void)req;
	c = (t_client*)ctx;
	status = 0;
	status = send_response_data(257, ccon, c->pwd);
	return (status);
}
