#include	<client.h>

int			init(int *cconp, t_opts *opts)
{
	info("attempting connection to %s:%d", opts->host, opts->port);
	(void)cconp;
	(void)opts;
	return (1);
}
