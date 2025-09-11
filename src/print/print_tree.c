#include "gp.h"

void	print_formatter(t_proc_info *proc, int depth) 
{
	int tmp_d = depth;
	while (depth && depth--)
		printf("   ");
	if (tmp_d > 0)
		printf("  \\_");
	printf("%s %d\n",proc->name,proc->pid);
}

void	print_tree(t_proc_info **hash_table, int depth, int size) 
{
	int i = 0;
	while (i < size)
	{
		if (hash_table[i] == NULL) { 
			i++;
			continue;
		}
		if (depth == 0 && hash_table[i]->ppid == 0) {
			t_proc_info *tmp = hash_table[i];
			while (tmp)
			{
				print_formatter(tmp,depth);
				if (tmp->children != NULL) {
					print_tree(tmp->children,depth + 1,tmp->children_size);
				}
				tmp = tmp->next;
			}
			i++;
		}
		else if (depth > 0) {
			print_formatter(hash_table[i],depth);
			if (hash_table[i]->children != NULL) {
					print_tree(hash_table[i]->children,depth + 1,hash_table[i]->children_size);
			}
		}
		i++;
	}
}