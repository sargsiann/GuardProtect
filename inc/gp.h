#ifndef GP_H
# define GP_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef	enum {
	RUNNING, // process is on runing state on cpu or waiting to run on cpu
	SLEEPING, // process is on sleeping state waiting for some user actions, can be interupetd by signals
	UNINTSLEEP, // process is waiting for low level io operations such from disks etc .. cant be interupted in another way its criticial operation
	ZOMBIE, //finished process that is not checked status by its parent so it finished but in OS
	STOPPED, //process state that is stopped by signal but can be woken up CTRL + Z to stopp the process, fg after to work it again
}	proc_state;

typedef struct s_proc_info {
	char		*name; // name of process
	pid_t		pid; // process id
	pid_t		ppid; // process of parent id
	proc_state	state; //state of the process
	char		*end_time; // end time of the process in readable format
}	t_proc_info;

void		exit_error(const char *msg, bool exit);
bool		check_pid(char	*pid) ;
char		*proc_path(char *pid);
void		free_proc_exit(char *path, t_proc_info *info, char *msg) ;
t_proc_info	*parse_proc(char *pid) ;
void		print_proc_info(t_proc_info *info) ;
bool		is_num(char c);
void		free_proc_info(t_proc_info *info) ;

#endif