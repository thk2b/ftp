#include	<server.h>
#include	<protocol.h>
#include	<errno.h>
#include	<unistd.h>
#include	<string.h>
#include	<libft.h>
#include	<limits.h>

static int	secure_absolute_path(char *filename, char **dst)
{
	char		*tmp;
	char		real_pwd[PATH_MAX];

	if (getcwd(real_pwd, PATH_MAX) == NULL)
		return (1);
	if ((tmp = ft_strjoin(real_pwd, filename)) == NULL)
		return (1);
	free(*dst);
	*dst = tmp;
	return (0);
}

int			rmd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	char		*tmp;
	int			status;
	t_client	*c;

	c = (t_client*)ctx;
	(void)dcon;
	if ((status = path_join(&tmp, c->pwd, req->args[1])) == 1)
		return (error_conn(ccon, 451, 1, "path_join"));
	else if (status == -1)
		return (send_response(553, ccon));
	if (secure_absolute_path(tmp, &tmp))
		return (error_conn(ccon, 451, 1, "secure absolute path"));
	free(req->args[1]);
	req->args[1] = tmp;
	info("rmdir %s", tmp);
	status = rmdir(tmp);
	if (status)
	{
		if (errno == ENOENT || errno == EPERM)
			return (send_response(553, ccon));
		return (error_conn(ccon, 451, 1, "rmdir"));
	}
	return (send_response(250, ccon));
}
