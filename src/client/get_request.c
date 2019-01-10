#include	<client.h>
#include	<libft.h>
#include	<get_next_line.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>
#include	<signal.h>

static int	init_request(t_request_ctx *req)
{
	ssize_t		i;
	t_cmd		*cmd_ref;
	t_request	*req_ref;

	i = -1;
	if (req->args == NULL || req->args[0] == NULL)
		return (1);
	cmd_ref = find_command(req->args[0], &i);
	req->rid = i;
	if (handle_help(req))
		return (1);
	else if (cmd_ref == NULL)
		return (unknown_cmd_error(req->args));
	if ((req_ref = find_request(i)) == NULL)
		return (1);
	if (validate_arguments(req->args + 1, req_ref))
		return (bad_usage_error(req->args, cmd_ref));
	free(req->args[0]);
	req->args[0] = strdup(req_ref->name);
	return (0);
}

static void	sig_int(int s)
{
	(void)s;
	write(1,"\n" PROMPT, PROMPT_LEN + 1);
}

int			get_request(t_request_ctx *req, int fd)
{
	int		status;
	char	*line;
	char	**cmd;

	write(1, PROMPT, PROMPT_LEN);
	signal(SIGINT, sig_int);
	if ((status = get_next_line(fd, &line)) == -1)
		return (error(-1, "get_next_line"));
	if (status == 0)
	{
		printf("\n");
		line = ft_strdup("quit");
	}
	cmd = ft_strsplit(line, ' ');
	free(line);
	req->args = cmd;
	signal(SIGINT, SIG_DFL);
	if (cmd == NULL)
		return (error(1, "strsplit"));
	return (init_request(req));
}
