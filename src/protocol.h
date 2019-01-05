#ifndef	PROTOCOL_H
#define	PROTOCOL_H

#include <stdlib.h>

/*
**	verb and argument requirement of a request
*/
typedef struct	s_protocol_entry
{
	char	*name;
	size_t	arg_num[2];
}				t_protocol_entry;

/*
**	instance of a protocol entry
*/
typedef struct	s_request
{
	char		**args;
	size_t		code;
}				t_request;

#endif
