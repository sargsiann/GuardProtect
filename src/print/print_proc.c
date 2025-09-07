#include "gp.h"

void	print_proc_info(t_proc_info *info) 
{
	printf("Process Name : %s\n",info->name);
	printf("Process ID : %d\n",info->pid);
	printf("Parent Process ID : %d\n",info->ppid);
	printf("Process State : ");
	switch (info->state) 
	{
		case RUNNING:
			printf("RUNNING\n");
			break;
		case SLEEPING:
			printf("SLEEPING\n");
			break;
		case UNINTSLEEP:
			printf("UNINTERRUPTIBLE SLEEP\n");
			break;
		case ZOMBIE:
			printf("ZOMBIE\n");
			break;
		case STOPPED:
			printf("STOPPED\n");
			break;
		default:
			printf("UNKNOWN\n");
			break;
	}
	if (info->end_time)
		printf("Process ended during GP call: %s\n",info->end_time);
}