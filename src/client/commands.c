#include <command.h>
#include <stdlib.h>

t_command	g_commands[] = {
	{"quit", "close the connection and exit", NULL},
	{"ls", "list files on the server", "[ path = ./]"},
	{"cd", "change remote current working directory", "[ path = /]"},
	{"pwd", "print the current working directory", NULL},
	{"get", "retreive a remote file and save it locally", "remote_path [ local_path ]"},
	{"put", "transmit a local file and save it remotely", "local_path [ remote_path ]"},
	{NULL, NULL, NULL}
}
