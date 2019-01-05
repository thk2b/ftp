#include			<protocol.h>

t_protocol_entry	g_protocol[] = {
	{"QUIT",	{0, 0}},
	{"LIST",	{0, 1}},
	{"CWD",		{0, 1}},
	{"PWD",		{0, 0}},
	{"RETR",	{0, 1}},
	{"STOR",	{0, 1}},
	{"QUIT",	{0, 0}},
	{NULL,		{0, 0}}
}
