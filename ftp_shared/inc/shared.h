#ifndef		SHARED_H
# define	SHARED_H
# include	<stdlib.h>

# include	<cmd.h>
# include	<state.h>
# include	<status.h>

t_state		send_list(t_state, void **ctx);
t_state		send_file(t_state, void **ctx);
t_state		receive_file(t_state, void **ctx);

#endif
