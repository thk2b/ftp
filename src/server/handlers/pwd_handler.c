#include		<server.h>
#include		<protocol.h>

#include		<unistd.h>

int				pwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	char	*buf;
	int		status;

	(void)dcon;
	(void)req;
	(void)ctx;
	status = 0;
	if ((buf = getcwd(NULL, 0)) == NULL)
		return (error_conn(ccon, 451, 1, "pwd"));
	status = send_response_data(257, ccon, buf);
	free(buf);
	return (status);
}
