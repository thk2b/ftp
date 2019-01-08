#include	<client.h>
#include	<libft.h>
#include	<get_next_line.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>

static int	init_request(t_request_ctx *req)
{
	ssize_t		i;
	t_cmd		*cmd_ref;
	t_request	*req_ref;

	i = -1;
	if (req->args == NULL || req->args[0] == NULL)
		return (1);
	if ((cmd_ref = find_command(req->args[0], &i)) == NULL)
		return (unknown_cmd_error(req->args));
	req->rid = i;
	if ((req_ref = find_request(i)) == NULL)
		return (1);
	if (validate_arguments(req->args + 1, req_ref))
		return (bad_usage_error(req->args, cmd_ref));
	free(req->args[0]);
	req->args[0] = strdup(req_ref->name);
	return (0);
}

int			get_request(t_request_ctx *req, int fd)
{
	int		status;
	char	*line;
	char	**cmd;

	write(1, PROMPT, PROMPT_LEN);
	if ((status = get_next_line(fd, &line)) == -1)
		return (error(1, "get_next_line"));
	if (status == 0)
	{
		printf("\n");
		line = ft_strdup("quit");
	}
	cmd = ft_strsplit(line, ' ');
	free(line);
	req->args = cmd;
	if (cmd == NULL)
		return (error(1, "strsplit"));
	if (init_request(req) == 0)
		return (0);
	ft_strvdel(cmd);
	return (1);
}
