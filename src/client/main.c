#include	<client.h>

#include	<errno.h>
#include	<unistd.h>
#include	<string.h>

t_opts		g_opts;

static int	parse_args(t_opts *opts, int ac, char **av)
{
	int	i;

	i = 1;
	opts->verbose = 0;
	while (i < ac)
		if (strcmp(av[i], "--help") == 0)
			exit(program_usage() != 0);
		else if (strcmp(av[i++], "-v") == 0)
			opts->verbose = 1;
	opts->host = NULL;
	opts->port = 8080;
	if (ac < 2)
		return (1);
	if (ac >= 2)
		opts->host = av[1];
	if (ac == 3)
		opts->port = atoi(av[2]);
	return (0);
}

int			main(int ac, char **av)
{
	int		ccon;
	int		status;

	status = 0;
	if (parse_args(&g_opts, ac, av))
		return (usage_error(USAGE, av));
	if ((status = init(&ccon, &g_opts)))
		return (status);
	status = run(ccon);
	return (status);
}
