#include	<client.h>
#include	<unistd.h>

int			pasv_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int	status;

	(void)ctx;
	if (*dcon == -1)
		close(*dcon);
	if ((status = send_request(ccon, req)))
		return (status);
	if ((status = init_data_connection(ccon, dcon)) != 0)
		return (status);
	return (0);
}
