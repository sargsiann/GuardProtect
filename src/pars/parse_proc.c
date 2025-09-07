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

char	*get_end_time() 
{
	char buff[64] = {0}; // buffer for time string
	time_t now = time(NULL); // getting the current time
	struct tm *t = localtime(&now); // converting to local time structure
	strftime(buff, sizeof(buff)-1, "%Y-%m-%d %H:%M", t); // formatting the time into a readable string
	return strdup(buff);
}

bool	get_proc_info(char *path, t_proc_info *proc_info)
{
	int	fd = open(path,O_RDONLY); // opening for reading
	if (fd == -1) {
		exit_error("Error : Opening File",0);
		return false;
	}

	char	buff[1024] = {0};
	int	bytes_readen = read(fd,buff,1024);

	if (bytes_readen == -1) {
		exit_error("Read error",0);
		return false;
	}

	//1. getting the pid of process
	proc_info->pid = atoi(buff);
	
	//2. moving through the second indicator
	char	*start = strchr(buff,' ') + 2; // skipping first '('
	char	*name_end = strchr(start,' ') - 1; // the second space skipping the last ')'
	*name_end = 0; // temporary put 0 on it
	proc_info->name = strdup(start); // duping that section of memory
	*name_end = ' '; // restoreing the value

	//3. moving through the third indicator
	proc_info->state = get_state(*(name_end + 1));
	name_end += 2;

	//4. moving through the fourth indicator
	proc_info->ppid = atoi(name_end);
	close(fd);
	if (access(path,R_OK) != 0) { // if in time of process info getting process ended we get approximate time of end
		proc_info->end_time = get_end_time();
	}
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