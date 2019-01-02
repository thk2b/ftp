#include <shared.h>

extern t_cmd	g_cmd[] = {
	{ 0, { "QUIT",	"EXIT",	NULL }},
	{ 1, { "LIST",	"LS",	NULL }},
	{ 2, { "CWD",	"CD",	NULL }},
	{ 3, { "PWD",			NULL }},
	{ 4, { "RETR",	"GET",	NULL }},
	{ 5, { "STORE",	"PUT",	NULL }},
	NULL
}
