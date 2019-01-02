#include <shared.h>
#include <server.h>

extern	t_transition		g_controller_transitions[] = {
	{ START,	sc_init				},
	{ COMMAND,	sc_receive_command	},
	{ RESPONSE,	sc_send_response	},
	{ DATA,		sc_process_data		},
	{ ERROR,	sc_error			},
	{ FAILURE,	sc_failure			},
	{ SUCCESS,	sc_success			},
	NULL
};

extern	t_data_transition	g_controller_data_transitions[] = {
	{ 1,		send_list			},
	{ 4,		send_file			},
	{ 5,		receive_file		},
	NULL
};
