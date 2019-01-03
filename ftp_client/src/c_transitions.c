#include <shared.h>
#include <client.h>

t_transition		g_client_transitions[] = {
	{ START,	c_init },
	{ USER,		c_get_command },
	{ COMMAND,	c_send_command },
	{ RESPONSE,	c_receive_response },
	{ DATA,		c_process_data },
	{ ERROR,	c_error },
	{ FAILURE,	c_failure },
	{ SUCCESS,	c_success },
	{ NSTATES,	NULL }
};
