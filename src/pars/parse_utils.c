#include "gp.h"

bool	check_pid(char	*pid) 
{
	while (*pid)
	{
		if (is_num(*pid) == false)
			return false;
		pid++;
	}
	return true;
}

char	*proc_path(char *pid)  // func for formatting pid path
{
	int		path_len = strlen(pid) + strlen("/proc//stat"); // getting the len of path of the process
	char	*path = malloc(sizeof(char) * (path_len + 1)); // allocating memory
	if (!path) { // exiting programm if allocation error occurs
		exit_error("Memory Allocation error\n",false);
		return NULL;
	}
	sprintf(path,"/proc/%s/stat",pid); // formatting process path
	return path;
}

void	free_proc_info(t_proc_info *info) 
{
	if (!info)
		return ;
	if (info->name)
		free(info->name);
	if (info->end_time)
		free(info->end_time);
	free(info);
}

void	free_proc_exit(char *path, t_proc_info *info, char *msg) 
{	
	free(path);
	free_proc_info(info);
	exit_error(msg,false);
}