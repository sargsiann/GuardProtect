#include "gp.h"

/* WHAT IS JIFFIES 
	JIFFIES ARE TIME IS TIME METRIC USING BY LINUX TO CALCULATE CPU TACTS
	ONE JIFFIE = 1/HZ HZ TACTS PER SEC SETTED BY KERNEL COMPILATION TIME ABOUT 0.01 SECS OR 0.001 SECS
*/

// ALL TIMES ARE IN JIFFIES
// user time jiffies spend on user time actions for cpu
// kernel time jiffies spend on kernel operations like syscalls for cpu
// all started with c is that process child processes

void	get_cpu_section(int *user_time, int *kernel_time, int *cus_time, int *cuk_time, char *buff, int *start_time) 
{
	int	section_num = 0; // started from sec 14 - 17 are our parametres

	// Going to 14 section
	while (section_num != 14)
	{
		buff = strchr(buff,' ') + 1;
		section_num+=1;
	}
	*user_time = atoi(buff);
	buff = strchr(buff,' ') + 1;
	*kernel_time = atoi(buff);
	buff = strchr(buff,' ') + 1;
	*cus_time = atoi(buff);
	buff = strchr(buff,' ') + 1;
	*cuk_time = atoi(buff);
	section_num+=4; // now at section 18
	while (section_num != 22)
	{
		buff = strchr(buff,' ') + 1;
		section_num+=1;
	}
	*start_time = atoi(buff);
}

float	get_time_from_boot() 
{
	FILE	*file = fopen("/proc/uptime","r"); // opening for reading
	if (!file) 
	{
		exit_error("Error : Opening File",0);
		return 0;
	}
	char	buff[64] = {0};
	if (fgets(buff,64,file) == NULL)  // reading the first line
	{
		exit_error("Error : Reading File",0); 
		fclose(file);
		return 0;
	}
	fclose(file);
	return atof(buff); // returning the time from boot in seconds
}

float	get_cpu_usage(char *buff, char *name) 
{	
	int ticks_per_sec = sysconf(_SC_CLK_TCK); // getting the number of jiffies per sec from system configuration

	int user_time = 0;
	int kernel_time = 0;
	int cus_time = 0;
	int cuk_time = 0;
	int start_time = 0;

	get_cpu_section(&user_time,&kernel_time,&cus_time,&cuk_time,buff, &start_time);
	
	float	total_time = get_time_from_boot() - start_time/ticks_per_sec; // total time in jiffies that process is active
	if (total_time == 0)
		return 0;
	float	cpu_usage = 100.00 * ((user_time/ticks_per_sec + kernel_time/ticks_per_sec + cus_time/ticks_per_sec + cuk_time/ticks_per_sec) / total_time);

	// get_cpu_section(&user_time,&kernel_time,&cus_time,&cuk_time,buff);
	return cpu_usage;
}