#include			<client.h>

t_cmd_handler		g_handlers[] = {
	{ "QUIT"	, quit_handler	},
	{ "LIST"	, list_handler	},
	{ "CWD"		, cwd_handler	},
	{ "PWD"		, pwd_handler	},
	{ "RETR"	, retr_handler	},
	{ "STOR"	, stor_handler	},
	{ "QUIT"	, quit_handler	},
	{ NULL		, NULL			}
};

t_cmd_handler_fn	find_handler(t_request *req)
{
	return (g_handlers[req->code].fn);
}
