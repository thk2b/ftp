#ifndef		SERVER_H
# define	SERVER_H
# include	<shared.h>

/*
**	server listener
*/

t_state		sl_init(t_state state, void **ctx);
t_state		sl_listen(t_state state, void **ctx);
t_state		sl_error(t_state state, void **ctx);
t_state		sl_exit(t_state state, void **ctx);


/*
**	server controller
*/

t_state		sc_init(t_state state, void **ctx);
t_state		sc_receive_command(t_state state, void **ctx);
t_state		sc_send_response(t_state state, void **ctx);
t_state		sc_process_data(t_state state, void **ctx);
t_state		sc_error(t_state state, void **ctx);
t_state		sc_failure(t_state state, void **ctx);
t_state		sc_success(t_state state, void **ctx);
t_state		sc_exit(t_state state, void **ctx);

#endif
