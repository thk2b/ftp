#include	<client.h>
#include	<get_next_line.h>
#include	<stdio.h>
#include	<errno.h>

static int	get_status(char *s)
{
	char	*t;
	int		n;

	t = s;
	while (*t && *t <= ' ')
		t++;
	n = atoi(t);
	if (n == 0 && *t != '0')
		return (-1);
	return (n);
}

int			get_response(int ccon)
{
	char	*line;
	int		status;

	if ((status = get_next_line(ccon, &line)) != 1)
	{
		if (errno && errno != ECONNRESET)
			return (error(errno, "get_next_line"));
		info("connection closed");
		return (-1);
	}
	if ((status = get_status(line)) == -1)
	{
		info("invalid response");
		return (-1);
	}
	printf(REV_PROMPT "%s\n", line);
	free(line);
	return (status);
}
