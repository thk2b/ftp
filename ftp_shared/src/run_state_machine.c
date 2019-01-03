#include	<shared.h>

void		run_state_machine(t_transition *transition_table, t_state state, void *ctx)
{
	t_transition		*transition;
	void				*next_ctx;

	transition = transition_table;
	next_ctx = ctx;
	while (transition->from != NIL)
	{
		if (transition->from == state)
			transition->action(state, &next_ctx);
		transition++;
	}
}
