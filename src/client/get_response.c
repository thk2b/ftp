#include	<client.h>
#include	<get_next_line.h>
#include	<stdio.h>
#include	<errno.h>
#include	<string.h>

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

int			get_response(int ccon, char **data)
{
	char	*line;
	int		status;
	char	*cr;

	if ((status = get_next_line(ccon, &line)) != 1)
	{
		if (errno && errno != ECONNRESET)
			return (error(1, "get_next_line"));
		return (error(0 , "connection closed"));
	}
	if ((status = get_status(line)) == -1)
		error(0, "invalid response");
	if ((cr = strchr(line, '\r')) != NULL)
		*cr = '\0';
	printf(REV_PROMPT "%s\n", line);
	if (data)
		*data = line;
	else
		free(line);
	return (status);
}
