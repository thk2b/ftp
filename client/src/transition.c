#include <shared.h>
#include <client.h>

extern	t_transition		g_client_transitions[] = {
	{ START,	c_init },
	{ USER,		c_get_command },
	{ COMMAND,	c_send_command },
	{ RESPONSE,	c_recieve_response },
	{ DATA,		c_process_data },
	{ ERROR,	c_error },
	{ FAILURE,	c_failure },
	{ SUCCESS,	c_success },
	NULL
}

extern	t_data_transition	g_client_data_transitions[] = {
	{ 4,	receive_file },
	{ 5,	send_file },
	NULL
}
