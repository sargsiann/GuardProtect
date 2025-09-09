#include "gp.h"

void	executor(char *pid) 
{
	if (strcmp(pid,"all") != 0) {
		t_proc_info *proc_info = parse_proc(pid);
		if (proc_info != NULL)
			print_proc_info(proc_info);
		free_proc_info(proc_info);
		return ;
	}
	t_proc_info **table = process_table();
	print_hash_table(table);
	free_hash_table(table);
}

int main(int ac, char **av) 
{
	if (ac != 2) 
		exit_error("Usage Error : usage ./gp [pid] or <all>\n",1); //ac size
	executor(av[1]);	
	return 0;
}