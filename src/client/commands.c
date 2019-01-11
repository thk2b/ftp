#include <client.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_cmd	g_commands[] = {
	{ RID_QUIT	, "quit"	, "close the connection and exit"				, NULL								},
	{ RID_LIST	, "ls"		, "list files on the server"					, "[ path = ./]"					},
	{ RID_CWD	, "cd"		, "change remote current working directory"		, "[ path = /]"						},
	{ RID_PWD	, "pwd"		, "print the current working directory"			, NULL								},
	{ RID_RETR	, "get"		, "retreive a remote file and save it locally"	, "remote_path [ local_path ]"		},
	{ RID_STOR	, "put"		, "transmit a local file and save it remotely"	, "local_path [ remote_path ]"		},
	{ RID_PASV	, "pasv"	, "enter passive mode"							, NULL								},
	{ RID_MKD	, "mkdir"	, "create a directory"							, "path"							},
	{ RID_DELE	, "rm"		, "remove a file"								, "path"							},
	{ RID_RMD	, "rmdir"	, "remove a directory"							, "path"							},
	{ MAX_RID	, NULL		, NULL											, NULL								}
};

/*
**	display an error message when the command does not match the specification
*/
int		unknown_cmd_error(char **cmd)
{
	usage_error("%s is not a command", cmd);
	return (1);
}

int		bad_usage_error(char **cmd, t_cmd *cmd_ref)
{
	dprintf(2, "USAGE: %s %s\n", cmd[0], cmd_ref->arg_help);
	return (1);
}

t_cmd	*find_command(char *name, ssize_t *p)
{
	ssize_t	i;

	i = 0;
	while (g_commands[i].name && strcmp(g_commands[i].name, name))
		i++;
	if (g_commands[i].name)
	{
		*p = i;
		return (g_commands + i);
	}
	*p = -1;
	return (NULL);
}

int		program_usage(void)
{
	t_cmd	*cmd;

	dprintf(2, "ftp client\navailable commands:\n");
	cmd = g_commands;
	while (cmd->rid != MAX_RID)
	{
		dprintf(2, "\t%s %s\n\t\t%s\n", cmd->name, cmd->arg_help ? cmd->arg_help : "", cmd->help);
		cmd++;
	}
	return (0);
}

int		handle_help(t_request_ctx *req)
{
	t_cmd	*cmd;

	if (strcmp(req->args[0], "help") == 0)
		return (program_usage() == 0);
	else if (req->args[1] && strcmp(req->args[1], "--help") == 0)
	{
		if (req->rid >= MAX_RID)
			return (0);
		cmd = g_commands + req->rid;
		dprintf(2, "USAGE: %s %s\n\t%s\n", cmd->name, cmd->arg_help, cmd->help);
		return (1);
	}
	return (0);
}
