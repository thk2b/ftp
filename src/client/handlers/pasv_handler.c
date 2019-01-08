#include	<client.h>
#include	<unistd.h>

int			pasv_handler(int ccon, int *dcon, t_request_ctx *req)
{
	int	status;

	if (*dcon == -1)
		close(*dcon);
	if (send_request(ccon, req))
		return (1);
	if ((status = init_data_connection(ccon, dcon)) != 0)
		return (status);
	return (0);
}
