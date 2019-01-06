#include	<client.h>
#include	<libft.h>
#include	<get_next_line.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>

static int	init_request(t_request_ctx *req, char **cmd)
{
	ssize_t		i;
	t_cmd		*cmd_ref;
	t_request	*req_ref;

	i = -1;
	if (cmd == NULL || cmd[0] == NULL)
		return (1);
	req->args = cmd;
	if ((cmd_ref = find_command(cmd[0], &i)) == NULL)
		return (unknown_cmd_error(cmd));
	req->rid = i;
	if ((req_ref = find_request(i)) == NULL)
		return (1);
	if (validate_arguments(cmd + 1, req_ref))
		return (bad_usage_error(cmd, cmd_ref));
	free(cmd[0]);
	cmd[0] = strdup(req_ref->name);
	return (0);
}

int			get_request(t_request_ctx *req, int fd)
{
	int		status;
	char	*line;
	char	**cmd;

	write(1, PROMPT, PROMPT_LEN);
	if ((status = get_next_line(fd, &line)) == -1)
		return (error(errno, "get_next_line"));
	if (status == 0)
		line = ft_strdup("exit");
	cmd = ft_strsplit(line, ' ');
	free(line);
	req->args = cmd;
	if (cmd == NULL)
		return (error(errno, "strsplit"));
	if (init_request(req, cmd) == 0)
		return (0);
	ft_strvdel(cmd);
	return (1);
}
