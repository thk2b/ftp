#include <shared.h>
#include <server.h>

t_transition		g_controller_transitions[] = {
	{ START,	sc_init				},
	{ COMMAND,	sc_receive_command	},
	{ RESPONSE,	sc_send_response	},
	{ DATA,		sc_process_data		},
	{ ERROR,	sc_error			},
	{ FAILURE,	sc_failure			},
	{ SUCCESS,	sc_success			},
	{ EXIT,		sc_exit				},
	{ NIL,		NULL				}
};
