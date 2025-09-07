#include "gp.h"

void	exit_error(const char *msg, bool to_exit) 
{
	if (errno == 0)
		fprintf(stderr,"%s",msg);
	else
		fprintf(stderr,"Error : %s\n",strerror(errno)); // string formatter by error number that is set by invalid operations
	if (to_exit)
		exit(1);
}

bool	is_num(char c)
{
	return c >= '0' && c <= '9';
}