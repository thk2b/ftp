#include	<server.h>

static t_sl_ctx	*init_ctx(char **av)
{
	t_sl_ctx			*ctx;
	t_s_opts			opts;

	if (init_opts(av, &opts))
		return (NULL);
	if ((ctx = malloc(sizeof(t_sl_ctx))) == NULL)
		return (NULL);
	ctx->opts = opts;
	ctx->sock = -1;
	return (ctx);
}

int				main(int ac, char **av)
{
	extern t_transition	g_sl_transitions[];
	t_sl_ctx			*ctx;

	(void)ac;
	if ((ctx = init_ctx(av)) == NULL)
		return (EXIT);
	run_state_machine(g_sl_transitions, START, (void*)ctx);
	return (1);
}
