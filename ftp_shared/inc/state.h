#ifndef			STATES_H
# define		STATES_H

typedef enum	e_state
{
	NIL,
	START,
	USER,
	LISTEN,
	COMMAND,
	RESPONSE,
	DATA,
	ERROR,
	FAILURE,
	SUCCESS,
	EXIT,
	NSTATES
}				t_state;

typedef t_state	(*t_transition_fn)(t_state current, void *ctx);

typedef struct	s_transition
{
	t_state			from;
	t_transition_fn	action;
}				t_transition;

typedef struct	s_data_transition
{
	int				cmd_code;
	t_transition_fn	action;
}				t_data_transition;

void			run_state_machine(t_transition *transition_table, t_state state, void *ctx);

#endif
