#include		<client.h>
#include		<protocol.h>
#include		<io.h>

#include		<unistd.h>

int				list_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	int		status;
	int		res_status;
	
	(void)ctx;
	if ((status = send_request(ccon, req)))
		return (status);
	if ((res_status = get_response(ccon, NULL)) <= 0)
		return (res_status);
	if (res_status >= 400)
		return (0);
	if (res_status == 150 && (status = init_data_connection(ccon, dcon)))
		return (status);
	read_file(*dcon, 1);
	if (res_status == 227 || (res_status < 200 && (status = get_response(ccon, NULL)) == 227))
	{
		close(*dcon);
		*dcon = -1;
	}
	return (status);
}
