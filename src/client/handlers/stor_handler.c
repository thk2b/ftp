#include		<client.h>
#include		<protocol.h>

int				stor_handler(int ccon, int *dcon, t_request_ctx *req)
{
	(void)req;
	if (*dcon == -1 && init_data_connection(ccon, dcon))
		return (1);
	return (1);
}
