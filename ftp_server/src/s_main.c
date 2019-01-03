#include	<server.h>

int			main(int ac, char **av)
{
	extern t_transition	g_sl_transitions[];

	run_state_machine(g_sl_transitions, START, av);
}
