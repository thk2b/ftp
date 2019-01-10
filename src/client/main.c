#include	<client.h>

#include	<errno.h>
#include	<unistd.h>

static int	parse_args(t_opts *opts, int ac, char **av)
{
	opts->addr.sin_addr.s_addr = 0;
	opts->addr.sin_port = 8080;
	if (ac < 2 || ac > 3)
		return (1);
	if (ac >= 2 && resolve_address(av[1], &opts->addr.sin_addr))
		return (1);
	if (ac == 3)
		opts->addr.sin_port = htons(atoi(av[2]));
	return (0);
}

int			main(int ac, char **av)
{
	t_opts	opts;
	int		ccon;
	int		status;

	status = 0;
	if (parse_args(&opts, ac, av))
		return (usage_error(USAGE, av));
	if ((status = init(&ccon, &opts)))
		return (status);
	status = run(ccon);
	return (status);
}
