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
	char		*tmp;
	t_client	*client;
	int			status;

	(void)dcon;
	client = (t_client*)ctx;
	tmp = client->pwd;
	if (validate_path_format(req->args[1]))
		return (send_response(553, ccon));	
	if ((status = path_join(&client->pwd, tmp, req->args[1])) == 1)
		return (error_conn(ccon, 451, 1, "path_join"));
	else if (status == 1)
		return (send_response(553, ccon));
	info("pwd is %s", client->pwd);
	free(tmp);
	if (chdir(req->args[1]))
	{
		if (errno == EACCES || errno == ENOENT)
			return (send_response(550, ccon));
		return (send_response(451, ccon)); // NON STANDARD
	}
	if (client->pwd == NULL)
		return (error_conn(ccon, 451, 1, "strjoin"));
	return (send_response(250, ccon));
}
