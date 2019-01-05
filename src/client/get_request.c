#include	<client.h>
#include	<libft.h>
#include	<get_next_line.h>
#include	<errno.h>
#include	<string.h>

static int	init_req(t_request *req, char **cmd)
{
	ssize_t					cmd_index;
	extern t_protocol_entry	g_protocol[];

	if (cmd == NULL || cmd[0] == NULL)
		return (1);
	if ((cmd_index = find_command(cmd[0])) == -1)
		return (unknown_cmd_error(cmd));
	req->code = (size_t)cmd_index;
	if (validate_arguments(req->code, cmd + 1))
		return (bad_usage_error(cmd, cmd_index));
	req->args = cmd;
	return (0);
}

static int	new_exit_request(t_request *req)
{
	extern t_protocol_entry	g_protocol[];
	char					*args[2];

	req->code = 0;
	args[0] = strdup(g_protocol[req->code].name);
	args[1] = NULL;
	if ((req->args = ft_strv_dup((char**)args)) == NULL)
		return (1);
	return (0);
}

int			get_request(t_request *req, int fd)
{
	int		status;
	char	*line;
	char	**cmd;

	if ((status = get_next_line(fd, &line)) == -1)
		return (error(errno, "get_next_line"));
	if (status == 0)
		return (new_exit_request(req));
	if ((cmd = ft_strsplit(line, ' ')) == NULL)
	{
		free(line);
		return (error(errno, "strsplit"));
	}
	free(line);
	if (init_req(req, cmd))
	{
		ft_strvdel(cmd);
		return (1);
	}
	return (0);
}
