#include <client.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


t_cmd	g_commands[] = {
	{"quit", "close the connection and exit", NULL},
	{"ls", "list files on the server", "[ path = ./]"},
	{"cd", "change remote current working directory", "[ path = /]"},
	{"pwd", "print the current working directory", NULL},
	{"get", "retreive a remote file and save it locally", "remote_path [ local_path ]"},
	{"put", "transmit a local file and save it remotely", "local_path [ remote_path ]"},
	{NULL, NULL, NULL}
};

/*
**	display an error message when the command does not match the specification
*/
int		unknown_cmd_error(char **cmd)
{
	error(500, "syntax: %s is not a command", cmd[0]);
	return (1);
}

int		bad_usage_error(char **cmd, size_t i)
{
	error(501, "syntax: invalid arguments\n");
	usage_error(g_commands[i].arg_help, cmd);
	return (1);
}

ssize_t	find_command(char *name)
{
	ssize_t	i;

	i = 0;
	while (g_commands[i].name)
		if (strcmp(g_commands[i].name, name) == 0)
			return (i);
		else
			i++;
	return (-1);
}
