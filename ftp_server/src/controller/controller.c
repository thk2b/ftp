#include	<server.h>

int			controller(void *ctx)
{
	extern t_transition	g_sc_transitions[];

	run_state_machine(g_sc_transitions, START, ctx);
}
