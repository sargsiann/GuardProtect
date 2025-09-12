#include "gp.h"

void	print_proc_info(t_proc_info *info) 
{
	printf("%20s	",info->name);
	printf("%5d	",info->pid);
	printf("%5d	",info->ppid);
	switch (info->state) 
	{
		case RUNNING:
			printf("%20s","RUNNING ");
			break;
		case SLEEPING:
			printf("%20s","SLEEPING ");
			break;
		case UNINTSLEEP:
			printf("%20s","UNINTERRUPTIBLE SLEEP ");
			break;
		case ZOMBIE:
			printf("%20s","ZOMBIE ");
			break;
		case STOPPED:
			printf("%20s","STOPPED ");
			break;
		default:
			printf("%20s","UNKNOWN ");
			break;
	}
	printf("%10.2f%%",info->cpu_usage);
	printf("%10.2f%%\n",info->mem_usage);
}