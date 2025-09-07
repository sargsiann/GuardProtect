#include "gp.h"

int main(int ac, char **av) 
{
	if (ac != 2) 
		exit_error("Usage Error : usage ./gp [pid]\n",1); //ac size
	t_proc_info *proc_info = parse_proc(av[1]);
	if (proc_info != NULL)
		print_proc_info(proc_info);
	return 0;
}