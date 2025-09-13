#include "gp.h"

proc_state	get_state(char c) 
{
	if (c == 'S')
		return SLEEPING;
	else if (c == 'R')
		return RUNNING;
	else if (c == 'D')
		return UNINTSLEEP;
	else if (c == 'Z')
		return ZOMBIE;
	else if (c == 'T')
		return STOPPED;
	else
		return -1;
}

bool	get_proc_info(char *path, t_proc_info *proc_info)
{
	int	fd = open(path,O_RDONLY); // opening for reading
	if (fd == -1) {
		exit_error("Error : Opening File",0);
		return false;
	}

	char	buff[2048] = {0};
	int	bytes_readen = read(fd,buff,2048);

	if (bytes_readen == -1) {
		exit_error("Read error",0);
		return false;
	}

	//1. getting the pid of process
	proc_info->pid = atoi(buff);
	
	//2. moving through the second indicator
	char	*start = strchr(buff,' ') + 2; // skipping first '('
	char	*name_end = strrchr(start,')'); // the second space skipping the last ')'
	*name_end = 0; // temporary put 0 on it
	proc_info->name = strdup(start); // duping that section of memory
	*name_end = ')'; // restoreing the value

	//3. moving through the third indicator
	proc_info->state = get_state(*(name_end + 2)); // state is after the space
	name_end += 4;

	//4. moving through the fourth indicator
	proc_info->ppid = atoi(name_end);
	proc_info->next = NULL;

	get_cpu_usage(buff,NULL,proc_info);
	proc_info->mem_usage = get_mem_usage(proc_info->pid);
	proc_info->children = NULL; // by default 0
	proc_info->children_size = 0; // by default 0
	close(fd);
	return true;
}

t_proc_info	*parse_proc(char *pid) 
{
	if (check_pid(pid) == false) { // checking the pid to be numeric
		exit_error("Error : PID must be numeric\n",0);
		return NULL;
	}

	t_proc_info *proc_info = malloc(sizeof(t_proc_info)); // struct for process_info 
	if (!proc_info) {
		exit_error("Memory Allocation error\n",0);
		return NULL;
	}
	memset(proc_info,0,sizeof(*proc_info));

	char 	*path = proc_path(pid); // getting the simple path like /proc/[pid]/stat to know can we have acces to it

	if (access(path,R_OK) != 0) { // if we dont have acces to that process files
		free_proc_exit(path,proc_info,NULL); // freeing all alocted memory
		return NULL;
	}

	if (get_proc_info(path,proc_info) == false) {
		free_proc_exit(path,proc_info,NULL); // freeing all alocted memory
		return NULL;
	};
	free(path);
	return proc_info;
}