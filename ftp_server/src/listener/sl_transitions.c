#include <shared.h>
#include <server.h>

t_transition	g_server_main_transitions[] = {
	{ START,	sl_init		},
	{ LISTEN,	sl_listen	},
	{ ERROR,	sl_error	},
	{ EXIT,		sl_exit		}
}
