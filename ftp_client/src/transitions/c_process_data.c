#include <shared.h>
#include <client.h>

extern	t_data_transition	g_client_data_transitions[] = {
	{ 1,		receive_list },
	{ 4,		receive_file },
	{ 5,		send_file },
	NULL
};
