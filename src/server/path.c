// #include	<server.h>
#include	<libft.h>

#include	<string.h>

static int	path_append(char **d, char **l, char **r)
{
	size_t	di;
	size_t	li;
	size_t	ri;

	di = 0;
	li = 0;
	while (l[li])
		if ((d[di++] = strdup(l[li++])) == NULL)
			return (1);
	ri = 0;
	while (r[ri])
	{
		if (strcmp(r[ri], "..") == 0)
		{
			if (di-- == 0)
				return (-1);
		}
		else if ((d[di++] = strdup(r[ri])) == NULL)
			return (1);
		ri++;
	}
	d[di] = NULL;
	return (0);
}

/*
**	joins left and right into a new path, taking care of '..'.
**		return 1 on error, -1 if the path is impossible, 0 on success.
*/
int			path_join(char **dst, char *left, char *right)
{
	char	**l;
	char	**r;
	char	**n;
	size_t	c;
	int		ret;

	if (strchr(right, '.') == NULL)
	{
		if (*left == '/' && left[1] == '\0')
			return ((*dst = ft_strjoin(left, right)) == NULL);
		if (*right == '/')
			return ((*dst = strdup(right)) == NULL);
		return ((*dst = ft_strcjoin(left, '/', right)) == NULL);
	}
	l = ft_strsplit(left, '/');
	r = ft_strsplit(right, '/');
	c = ft_strv_len(l) + ft_strv_len(r);
	if ((n = malloc(sizeof(char**) * (c + 1))) == NULL)
		return (1);
	if (!((l = ft_strsplit(left, '/')) && (r = ft_strsplit(right, '/'))))
		return (1);
	ret = path_append(n, l, r);
	ft_strvdel(l);
	ft_strvdel(r);
	if (ret == 0)
		*dst = ft_strvjoin((const char **)n, "/");
	if (**dst == '\0')
		*dst = strdup("/");
	return (ret);
}

#include <printf.h>
int main(int ac, char **av)
{
	char *d;

	(void)ac;
	int ret = path_join(&d, av[1], av[2]);
	printf("%d - '%s'\n", ret, d);
}
