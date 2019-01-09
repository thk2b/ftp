// #include	<server.h>
#include	<libft.h>

#include	<string.h>

static void	replace(char **a, char *b)
{
	free(*a);
	*a = b;
}

static int	path_append(char **d, char **l, char **r)
{
	size_t	di;
	size_t	li;
	size_t	ri;

	di = 0;
	li = 0;
	while (l[li])
		d[di++] = l[li++];
	ri = 0;
	while (r[ri])
	{
		if (strcmp(r[ri], "..") == 0)
		{
			if (di-- == 0)
				return (-1);
		}
		else
			d[di++] = r[ri];
		ri++;
	}
	d[di] = NULL;
	return (0);
}

static int	path_join_no_dot(char **dst, char *left, char *right)
{
	if (*right == '/')
		return ((*dst = strdup(right)) == NULL);
	if (*left == '/' && left[1] == '\0')
		return ((*dst = ft_strjoin(left, right)) == NULL);
	return ((*dst = ft_strcjoin(left, '/', right)) == NULL);
}
/*
**	joins left and right into a new path, taking care of '..'.
**		return 1 on error, -1 if the path is impossible, 0 on success.
**		left must be an absolute path
*/
int			path_join(char **dst, char *left, char *right)
{
	char	**l;
	char	**r;
	char	**n;
	size_t	c;
	int		ret;

	if (strchr(right, '.') == NULL)
		return (path_join_no_dot(dst, left, right));
	if (!((l = ft_strsplit(left, '/')) && (r = ft_strsplit(right, '/'))))
		return (1);
	c = ft_strv_len(l) + ft_strv_len(r);
	if ((n = malloc(sizeof(char**) * (c + 2))) == NULL)
		return (1);
	if ((n[0] = "") == NULL)
		return (1);
	ret = path_append(n + 1, l, r);
	if (ret == 0)
		*dst = ft_strvjoin((const char **)n, "/");
	ft_strvdel(l);
	ft_strvdel(r);
	free(n);
	if (ret != -1 && **dst == '\0')
		replace(dst, strdup("/"));
	return (ret);
}

/*
#include <printf.h>
int main(int ac, char **av)
{
	char *d = strdup("/a");

	(void)ac;
	int ret = path_join(&d, av[1], av[2]);
	printf("%d - '%s'\n", ret, d);
	printf("%d - '%s'\n", ret, d);
	system("leaks a.out");
}
*/
