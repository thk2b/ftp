#include		<client.h>
#include		<protocol.h>

int				quit_handler(int ccon, int *dcon, t_request_ctx *req)
{
	(void)ccon;
	(void)dcon;
	(void)req;
	return (1);
}
