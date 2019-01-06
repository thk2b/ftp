#include			<protocol.h>
#include			<libft.h>
#include			<string.h>

t_protocol_entry	g_protocol[] = {
	{ "QUIT"	, {0, 0}	},
	{ "LIST"	, {0, 1}	},
	{ "CWD"		, {0, 1}	},
	{ "PWD"		, {0, 0}	},
	{ "RETR"	, {1, 2}	},
	{ "STOR"	, {1, 2}	},
	{ "QUIT"	, {0, 0}	},
	{ NULL		, {0, 0}	}
};

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

int					validate_arguments(size_t i, char **cmd)
{
	size_t	n;

	if (cmd == NULL)
		n = 0;
	else
		n = ft_strv_len(cmd);
	if (n < g_protocol[i].arg_num[0] || n > g_protocol[i].arg_num[1])
		return (1);
	return (0);
}
