#include	<server.h>

int			parse_args(t_opts *opts, int ac, char **av)
{
	opts->port = 8080;
	if (ac > 1)
		opts->port = atoi(av[1]);
	if (ac > 2)
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	t_opts	opts;

	if (parse_args(&opts, ac, av))
		return (usage_error(USAGE, av));
}
