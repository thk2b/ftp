#include		<client.h>
#include		<protocol.h>
#include		<io.h>

#include		<unistd.h>

int				list_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		res_status;
	
	(void)ctx;
	if (send_request(ccon, req))
		return (1);
	if ((res_status = get_response(ccon, NULL)) <= 0)
		return (res_status);
	if (res_status >= 400)
		return (0);
	if (res_status == 150 && init_data_connection(ccon, dcon))
		return (1);
	read_file(*dcon, 1);
	if (res_status == 227 || (res_status < 200 && (res_status = get_response(ccon, NULL)) == 227))
	{
		close(*dcon);
		*dcon = -1;
	}
	return (res_status >= 0);
}
