#include <shared.h>
#include <server.h>

t_transition	g_sl_transitions[] = {
	{ START,	sl_init		},
	{ LISTEN,	sl_listen	},
	{ ERROR,	sl_error	},
	{ EXIT,		sl_exit		},
	{ NIL,		NULL}
};
