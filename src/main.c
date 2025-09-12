#include "gp.h"

void	executor(char *pid, char *tree_flag) 
{
	if (strcmp(pid,"all") != 0) {
		t_proc_info *proc_info = parse_proc(pid);
		if (proc_info != NULL)
			print_proc_info(proc_info);
		free_proc_info(proc_info);
		return ;
	}
	t_proc_info **table = process_table();
	if (tree_flag != NULL) {
 		make_tree(table);
		print_tree(table,0,TABLE_SIZE);
	}
	else
		print_hash_table(table);
	free_hash_table(table);
}

int main(int ac, char **av) 
{
	if (ac < 2) 
		exit_error("Usage Error : usage ./gp [pid] or <all> -t (for tree printing optional)\n",1); //ac size
	if (av[2] != NULL && strcmp(av[2],"-t") != 0)
		exit_error("Usage Error : last option -t (for tree printing optional)\n",1); //ac size
	executor(av[1],av[2]);	
	return 0;
}