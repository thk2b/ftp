#include <server.h>

extern	t_data_transition	g_controller_data_transitions[] = {
	{ 1,		send_list			},
	{ 4,		send_file			},
	{ 5,		receive_file		},
	NULL
};
