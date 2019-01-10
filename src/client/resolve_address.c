#include	<client.h>

#include	<sys/socket.h>
#include	<netdb.h>

int			resolve_address(char *s, struct in_addr *addr)
{
	struct addrinfo	hints = {0,0,0,0,0,0,0,0};
	struct addrinfo	*h;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(s, NULL, &hints, &h))
	{
		error(0, "getaddrinfo");
		return (1);
	}
	if (h == NULL)
		return (1);
	addr->s_addr = ((struct sockaddr_in *)h->ai_addr)->sin_addr.s_addr;
	info("%d", addr->s_addr);
	info(s);
	return (0);
}
