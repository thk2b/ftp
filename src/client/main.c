#include <client.h>

#include <errno.h>

static int	parse_args(t_opts *opts, int ac, char **av)
{
	opts->host = "0.0.0.0";
	opts->port = 8080;
	if (ac == 1)
	{}
	else if (ac == 2)
		opts->port = atoi(av[1]);
	else if (ac == 3)
	{
		opts->port = atoi(av[2]);
		opts->host = av[1];
	}
	else
		return (1);
	return (0);
}

int				main(int ac, char **av)
{
	t_opts	opts;
	int		ccon;
	int		status;

	status = 0;
	if (parse_args(&opts, ac, av))
		return (usage_error(av));
	if ((status = init(&ccon, &opts)))
		return (status);
	// status = run(ccon);
	return (status);
}
