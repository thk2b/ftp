#include	<server.h>

#include	<stdio.h>
#include	<errno.h>
#include	<string.h>

t_state		sl_error(t_state state, void *vctx)
{
	t_sl_ctx	*ctx;

	ctx = (t_sl_ctx*)vctx;
	dprintf(2, "ERROR:\t[%.3d] %s\n", errno, strerror(errno));
	return (EXIT);
}
