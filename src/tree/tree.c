#include "gp.h"

void	add_children(t_proc_info *node, t_proc_info **hash_table) 
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) continue; // passing NULLs
		t_proc_info *tmp = hash_table[i]; // this is for colision cases
		if (!tmp)
			continue;
		while (tmp)
		{
			if (tmp->ppid == node->pid)
				push_child(node,tmp);
			tmp = tmp->next;
		}
	}	
}

void	make_tree(t_proc_info **hash_table) // getting hash table and working with it members 
{
	int i = 0;
	while (i < TABLE_SIZE)
	{		
		if (hash_table[i] == NULL)
		{
			i++;
			continue;
		}
		add_children(hash_table[i],hash_table);
		i++;
	}
}