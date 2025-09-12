#include "gp.h"

static float	total_size = 0;

int		get_total_mem() 
{
	char	buff[128];
	int	fd = open("/proc/meminfo",O_RDONLY);
	if (fd == -1) {
		exit_error("open error",0);
		return -1;
	}
	if (read(fd,buff,128) == -1)  {
		exit_error("Read error",0);
		close(fd);
		return -1;
	}	
	return atoi(strchr(buff,':') + 1);
}

int		get_vmrrs(int pid) 
{
	char	buff[128] = {0};
	char	path[64] = {0};

	sprintf(path,"/proc/%d/statm",pid);
	int		mem_fd = open(path,O_RDONLY);
	if (mem_fd == -1) {
		exit_error("No such file",0);
		return -1;
	}
	if (read(mem_fd,buff,128) == -1)  {
		exit_error("No such file",0);
		close(mem_fd);
		return -1;
	}
	return (atoi(strchr(buff,' ')));
}

float	get_mem_usage(int pid) 
{
	float	page_kb = sysconf(_SC_PAGESIZE) / 1024;
	if (total_size == 0)
		total_size = get_total_mem();
	float vrrs = get_vmrrs(pid);
	if (vrrs == -1)
		return -1;
	if (total_size == -1)
		return -1;
	return ((vrrs * page_kb)/total_size) * 100;
}