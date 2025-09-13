#include "gp.h"

/* WHAT IS JIFFIES 
	JIFFIES ARE TIME IS TIME METRIC USING BY LINUX TO CALCULATE CPU TACTS
	ONE JIFFIE = 1/HZ HZ TACTS PER SEC SETTED BY KERNEL COMPILATION TIME ABOUT 0.01 SECS OR 0.001 SECS
*/

// ALL TIMES ARE IN JIFFIES
// user time jiffies spend on user time actions for cpu
// kernel time jiffies spend on kernel operations like syscalls for cpu
// all started with c is that process child processes

void	get_cpu_section(float *user_time, float *kernel_time, float *cus_time, float *cuk_time, char *buff, float *start_time) 
{
	int	section_num = 0; // started from sec 14 - 17 are our parametres

	// Going to 14 section
	while (section_num != 14)
	{
		buff = strchr(buff,' ') + 1;
		section_num+=1;
	}
	*user_time = atof(buff);
	buff = strchr(buff,' ') + 1;
	*kernel_time = atof(buff);
	buff = strchr(buff,' ') + 1;
	*cus_time = atof(buff);
	buff = strchr(buff,' ') + 1;
	*cuk_time = atof(buff);
	section_num+=4; // now at section 18
	while (section_num != 22)
	{
		buff = strchr(buff,' ') + 1;
		section_num+=1;
	}
	*start_time = atof(buff);
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

void	get_cpu_usage(char *buff, char *name, t_proc_info *proc) 
{	
	float	time_from_boot = 0.0;
	int		ticks_per_sec = sysconf(_SC_CLK_TCK); // getting the number of jiffies per sec from system configuration
	int		proc_num = sysconf(_SC_NPROCESSORS_CONF);

	float user_time = 0;
	float kernel_time = 0;
	float cus_time = 0;
	float cuk_time = 0;
	float start_time = 0;

		
	get_cpu_section(&user_time,&kernel_time,&cus_time,&cuk_time,buff, &start_time);
	
	time_from_boot = get_time_from_boot();
	// + cus_time/ticks_per_sec + cuk_time/ticks_per_sec
	float	total_time = (time_from_boot * ticks_per_sec) - start_time; // total time in jiffies that process is active
	if (total_time == 0)
		return;
	if (strcmp(proc->name,"gp") == 0)
	{
		printf("%f %f %f %f %f\n",user_time,kernel_time, cus_time,cuk_time, total_time);
	}
	proc->cpu_usage = 100.00 *  ((user_time + kernel_time + cus_time + cuk_time)) / (total_time * proc_num) ;

}