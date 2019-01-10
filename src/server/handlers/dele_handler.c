#include	<server.h>
#include	<protocol.h>
#include	<errno.h>
#include	<unistd.h>
#include	<string.h>

int			dele_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	char		*tmp;
	t_client	*c;

	c = (t_client*)ctx;
	(void)dcon;

	if (strncmp(req->args[1], "/", 1) == 0 || strcmp(req->args[1], ".") == 0 || strncmp(req->args[1], "..", 2) == 0)
		return (send_response(553, ccon));
	if (path_join(&tmp, c->pwd, req->args[1]))
		return (send_response(553, ccon));
	free(tmp);
	if (unlink(req->args[1]))
	{
		if (errno == ENOENT || errno == EPERM)
			return (send_response(553, ccon));
		return (send_response(451, ccon));
	}
	return (send_response(250, ccon));
}
