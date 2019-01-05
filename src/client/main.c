#include <client.h>

#include <errno.h>
#include <unistd.h>

static int	parse_args(t_opts *opts, int ac, char **av)
{
	opts->ip = NULL;
	opts->port = 8080;
	if (ac < 2 || ac > 3)
		return (1);
	if (ac >= 2)
		opts->ip = av[1];
	if (ac == 3)
		opts->port = atoi(av[2]);
	return (0);
}

int				main(int ac, char **av)
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
	close(ccon);
	return (status);
}
