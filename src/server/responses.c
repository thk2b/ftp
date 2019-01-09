#include	<server.h>

t_response	g_responses[] = {
	{ 0		, 9		, "Undefined"							},
	{ 150	, 32	, "File OK, opening data connection"	},
	{ 125	, 29	, "File OK, data connection open"		},
	{ 220	, 13	, "Service ready"						},
	{ 221	, 34	, "Service closing control connection"	},
	{ 225	, 23	, "Closing data connection"				},
	{ 226	, 36	, "Closing data connection, transfer OK"},
	{ 227	, 21	, "Entering passive mode"				},
	{ 250	, 26	, "Requested action completed"			},
	{ 257	, 12	, "Path created"						},
	{ 425	, 26	, "Can't open data connection"			},
	{ 451	, 21	, "Internal server error"				},
	{ 500	, 15	, "Invalid command"						},
	{ 501	, 18	, "Invalid parameters"					},
	{ 550	, 16	, "Action not taken"					},
	{ 553	, 21	, "File name not allowed"				},
	{ -1	, 0		, NULL									}
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
