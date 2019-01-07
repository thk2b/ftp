#include	<server.h>
#include	<libft.h>
#include	<get_next_line.h>
#include	<errno.h>
#include	<string.h>

static int	init_request(t_request_ctx *req)
{
	ssize_t		i;
	t_request	*req_ref;

	i = -1;
	if (req->args == NULL || req->args[0] == NULL)
		return (500);
	if ((req_ref = find_request_by_name(req->args[0])) == NULL)
		return (500);
	req->rid = req_ref->rid;
	if (validate_arguments(req->args + 1, req_ref))
		return (501);
	return (0);
}

int			get_request(t_request_ctx *req, int fd)
{
	int		status;
	char	*line;
	char	**cmd;
	char	*cr;

	if ((status = get_next_line(fd, &line)) != 1)
	{
		if (errno && errno != ECONNRESET)
			return (error(errno, "get_next_line"));
		info("connection closed");
		return (-1);
	}
	if ((cr = ft_strchr(line, '\r')))
		*cr = ' ';
	info("recieved \"%s\"", line);
	cmd = ft_strsplit(line, ' ');
	free(line);
	req->args = cmd;
	if (cmd == NULL)
		return (error(errno, "strsplit"));
	if ((status = init_request(req)) == 0)
		return (0);
	ft_strvdel(cmd);
	return (status);
}
