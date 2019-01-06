#include	<server.h>
#include	<unistd.h>

int			controller(int ccon)
{
	// int		dcon;
	int		go;

	send_response(220, ccon);
	go = 1;
	while (go)
	{
		// go = 0;
	}
	return (1);
}
