#include	<server.h>

t_response	g_responses[] = {
	{ 0		, 9		, "Undefined"				},
	{ 220	, 13	, "Service ready"			},
	{ 500	, 15	, "Invalid command"			},
	{ 501	, 18	, "Invalid parameters"		},
	{ -1	, 0		, NULL						}
};

t_response	*find_response(int code)
{
	t_response	*response;

	response = g_responses;
	while (response->code != -1)
	{
		if (response->code == code)
			return (response);
		response++;
	}
	return (g_responses);
}
