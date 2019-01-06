#include			<protocol.h>
#include			<libft.h>
#include			<string.h>

t_request	g_protocol[] = {
	{ "QUIT"	, {0, 0}	, quit_handler	},
	{ "LIST"	, {0, 1}	, list_handler	},
	{ "CWD"		, {0, 1}	, cwd_handler	},
	{ "PWD"		, {0, 0}	, pwd_handler	},
	{ "RETR"	, {1, 2}	, retr_handler	},
	{ "STOR"	, {1, 2}	, stor_handler	},
	{ "QUIT"	, {0, 0}	, quit_handler	},
	{ NULL		, {0, 0}	, NULL			}
};

t_request_handler_fn	find_handler(t_request_ctx *req)
{
	return (g_protocol[req->code].fn);
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
