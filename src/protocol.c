#include				<protocol.h>
#include				<libft.h>
#include				<string.h>

t_request				g_protocol[] = {
	{ RID_QUIT	, "QUIT"	, {0, 0}	, quit_handler	},
	{ RID_LIST	, "LIST"	, {0, 1}	, list_handler	},
	{ RID_CWD	, "CWD"		, {0, 1}	, cwd_handler	},
	{ RID_PWD	, "PWD"		, {0, 0}	, pwd_handler	},
	{ RID_RETR	, "RETR"	, {1, 2}	, retr_handler	},
	{ RID_STOR	, "STOR"	, {1, 2}	, stor_handler	},
	{ RID_PASV	, "PASV"	, {0, 0}	, pasv_handler	},
	{ RID_MKD	, "MKD"		, {1, 1}	, mkd_handler	},
	{ RID_DELE	, "DELE"	, {1, 1}	, dele_handler	},
	{ RID_RMD	, "RMD"		, {1, 1}	, rmd_handler	},
	{ MAX_RID	, NULL		, {0, 0}	, NULL			}
};

t_request				*find_request(enum e_request_id i)
{
	if (i >= MAX_RID)
		return (NULL);
	return (g_protocol + i);
}

t_request				*find_request_by_name(char *name)
{
	t_request	*req;

	req = g_protocol;
	while (req->name)
	{
		if (strcmp(req->name, name) == 0)
			return (req);
		req++;
	}
	return (NULL);
}

int						call_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx)
{
	t_request	*req_ref;

	if ((req_ref = find_request(req->rid)))
		return (req_ref->fn(ccon, dcon, req, ctx));
	return (-1);
}

int						validate_arguments(char **cmd, t_request *req_ref)
{
	size_t	n;

	if (cmd == NULL)
		n = 0;
	else
		n = ft_strv_len(cmd);
	if (n < req_ref->arg_num[0] || n > req_ref->arg_num[1])
		return (1);
	return (0);
}
