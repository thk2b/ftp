#include			<protocol.h>
#include			<libft.h>
#include			<string.h>

t_protocol_entry	g_protocol[] = {
	{"QUIT",	{0, 0}},
	{"LIST",	{0, 1}},
	{"CWD",		{0, 1}},
	{"PWD",		{0, 0}},
	{"RETR",	{1, 2}},
	{"STOR",	{1, 2}},
	{"QUIT",	{0, 0}},
	{NULL,		{0, 0}}
};

int					validate_arguments(size_t i, char **cmd)
{
	size_t	n;

	if (cmd == NULL || cmd[0] == NULL)
		return (1);
	n = ft_strv_len(cmd);
	if (n < g_protocol[i].arg_num[0] || n > g_protocol[i].arg_num[1])
		return (1);
	return (0);
}
