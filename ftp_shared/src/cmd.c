#include <shared.h>

extern t_cmd	g_cmd[] = {
/*	code	names				min_nargs	args_usage					description									*/
	{ 0, { "QUIT",	"EXIT",	NULL },	0,	NULL,				"Exit the program"										},
	{ 1, { "LIST",	"LS",	NULL },	0,	"[ <pathname> ]",	"List files on server"									},
	{ 2, { "CWD",	"CD",	NULL },	1,	"<pathname>",		"Change server's current working directory"				},
	{ 3, { "PWD",			NULL },	0,	NULL,				"Print server's current working directory"				},
	{ 4, { "RETR",	"GET",	NULL },	1,	"<filename>",		"Retreive a file from the server and save it locally"	},
	{ 5, { "STORE",	"PUT",	NULL },	1,	"<filename>",		"Retreive a local file and send save it on the server"	},
	NULL
}
