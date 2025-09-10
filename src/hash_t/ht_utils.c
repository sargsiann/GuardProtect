#include "gp.h"

int		hash_function(pid_t pid) // the function returns the index by PID
{
	if (pid < 0)
		return -1;
	return pid % TABLE_SIZE; //getting the index
}

void	insert_to_table(t_proc_info **table,t_proc_info *process) 
{
	if (!table || !process)
		return ;
	int	index = hash_function(process->pid);
	if (index == -1 || index < 0 || index >= TABLE_SIZE) {
		exit_error("Error: No such PID in Process table",0);
	}
	// else using chaining method to handle colisions
	t_proc_info *tmp = table[index];
	if (!tmp)
	{
		table[index] = process;
		process->next = NULL;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = process;// adding process to end of LL
}

t_proc_info	*get_from_table(int	pid, t_proc_info **table) 
{
	if (!table)
		return NULL;
	int index = hash_function(pid);
	if (index == -1 || table[index] == NULL || index < 0 || index >= TABLE_SIZE) {
		exit_error("Error: No such PID in Process table",0);
	}
	t_proc_info *search = table[index];
	while (search) {
		if (pid == search->pid) // found the matching in LL
			return search;
		search = search->next;
	}
	exit_error("Error: No such PID in Process table",0);
	return NULL;
}


void	delete_from_table(t_proc_info **table, int	pid) 
{
	if (!table)
		return ;
	int index = hash_function(pid);
	if (index == -1 || table[index] == NULL || index < 0 || index >= TABLE_SIZE) {
		exit_error("Error: No such PID in Process table",0);
	}
	t_proc_info *search = table[index];
	while (search) 
	{
		if (pid == search->pid) // found the matching in LL
		{
			free_proc_info(search); // freeing it 
			table[index] = NULL; //putting the NULL
			return ;
		}
		search = search->next;
	}
	exit_error("Error: No such PID in Process table",0);
}
