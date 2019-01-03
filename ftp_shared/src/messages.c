#include	<shared.h>

extern t_status_message	g_error_messages[] = {
	{},
	NULL
};

extern t_status_message	g_failure_messages[] = {
	{ 504,	"Command not implemented for that parameter"	},
	{ 550,	"Requested action not taken"					},
	{ 555,	"Fatal internal error"							},
	NULL
};

extern t_status_message	g_data_messages[] = {
	{ 150,	"File status ok, transfer starting"	},
	NULL
};

extern t_status_message	g_success_messages[] = {
	{ 250,	"Requested file action completed"	},
	NULL
};
