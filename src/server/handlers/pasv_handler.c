#include	<server.h>

int			pasv_handler(int ccon, int *dcon, t_request_ctx *req)
{
	(void)ccon;
	(void)dcon;
	(void)req;
	info ("attempting to open data connection");
	return (1);
}
