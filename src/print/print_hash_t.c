#include "gp.h"

void	print_hash_table(t_proc_info **table) // table printer
{
	if (!table)
		return ;
	for (int i = 0; i < TABLE_SIZE; i++) 
	{
		if (table[i] == NULL)
			continue;
		t_proc_info *tmp = table[i];
		while (tmp) 
		{
			print_proc_info(tmp); // in case of collisions printing all in LL
			tmp = tmp->next;
		}
	}
}