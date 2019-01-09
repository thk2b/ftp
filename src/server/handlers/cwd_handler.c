#include		<server.h>
#include		<protocol.h>
#include		<libft.h>

#include		<unistd.h>
#include		<errno.h>

static int		validate_path_format(char *path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

int				cwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	t_client	*client;
	int			status;
	char		*path;
	char		*new_pwd;

	(void)dcon;
	path = req->args[1] ? req->args[1] : "";
	client = (t_client*)ctx;
	if (validate_path_format(path))
		return (send_response(553, ccon));
	if ((status = path_join(&new_pwd, client->pwd, path)) == 1)
		return (error_conn(ccon, 451, 1, "path_join"));
	else if (status == -1)
		return (send_response(553, ccon));
	if (chdir(path))
	{
		if (errno == EACCES || errno == ENOENT)
			return (send_response(550, ccon));
		return (send_response(451, ccon));
	}
	free(client->pwd);
	client->pwd = new_pwd;
	info("pwd is %s", client->pwd);
	return (send_response(250, ccon));
}
