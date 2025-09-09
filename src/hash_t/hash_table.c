#include "gp.h"

void		free_list(t_proc_info *head) 
{
	t_proc_info *tmp;
	while (head) 
	{
		tmp = head;
		head = head->next;
		free_proc_info(tmp);
	}
}

void		free_hash_table(t_proc_info **table) 
{
	if (!table)
		return ;
	for (int i = 0; i < TABLE_SIZE; i++) 
	{
		if (table[i] == NULL)
			continue ;
		t_proc_info *tmp = table[i];
		free_list(tmp);
	}
	free(table);
}

t_proc_info	**process_table() // function for hash table of all processes
{
	t_proc_info **table = malloc(sizeof(t_proc_info *) * TABLE_SIZE);
	if (!table)
		exit_error("Malloc error:",1); //exiting the programm
	memset(table,0,TABLE_SIZE); //putting all 0s;
	DIR *processes_dir = opendir("/proc");
	if (!processes_dir) {
 		exit_error("Cant open the /proc dir",0); //no exit
		return table;
	}
	struct dirent	*one_proc; // struct for each dir entry
	t_proc_info		*single_proc; // struct for each process info
	while ((one_proc = readdir(processes_dir)) != NULL) {
		if (is_strnumeric(one_proc->d_name) == false)  // skipping non numeric dirs
			continue;
		single_proc = parse_proc(one_proc->d_name); //parsing the process info
		insert_to_table(table,single_proc); // inserting to hash table
	}
	closedir(processes_dir);
	return table;
}