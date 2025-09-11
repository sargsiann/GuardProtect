#include "gp.h"

void	push_child(t_proc_info *parent,t_proc_info *child) 
{
	if (!parent || !child) //checking
		return ;
	parent->children_size+=1;
	t_proc_info **new_children = malloc(sizeof(t_proc_info *) * (parent->children_size)); // getting new array of children
	if (!new_children) { // checking malloc res
		exit_error("Malloc error",0);
		return ;
	}
	if (parent->children_size == 1)
	{
		new_children[0] = child; 		
		parent->children = new_children; // giving new address 
		return ;
	}
	int i;	
	for (i = 0; i < parent->children_size - 1; i++) { // giving each child address to new vectors
		new_children[i] = parent->children[i];
	}
	new_children[i] = child; // the last new child
	free(parent->children); // free ing last allocated vector address
	parent->children = new_children; // giving new address 
}