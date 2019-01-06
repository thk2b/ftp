#include <client.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_cmd	g_commands[] = {
	{ "quit"	, "close the connection and exit"				, NULL								},
	{ "ls"		, "list files on the server"					, "%s [ path = ./]"					},
	{ "cd"		, "change remote current working directory"		, "%s [ path = /]"					},
	{ "pwd"		, "print the current working directory"			, NULL								},
	{ "get"		, "retreive a remote file and save it locally"	, "%s remote_path [ local_path ]"	},
	{ "put"		, "transmit a local file and save it remotely"	, "%s local_path [ remote_path ]"	},
	{ NULL		, NULL											, NULL								}
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
	usage_error(cmd_ref->arg_help, cmd);
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
