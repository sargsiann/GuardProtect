#ifndef GP_H
# define GP_H
# define TABLE_SIZE 1021 //the max size of hash table the prime number to reduce num of collisions

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

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
	float		cpu_usage; //cpu usage in percent of process
	int			children_size; // childs vector_size
	struct		s_proc_info **children; //pointer to an child process of each process FOR TREE
	struct		s_proc_info *next; //next to an next member in hash table in case of chaining FOR LINKED LIST
}	t_proc_info;

void		exit_error(const char *msg, bool exit);
bool		check_pid(char	*pid) ;
char		*proc_path(char *pid);
void		free_proc_exit(char *path, t_proc_info *info, char *msg) ;
t_proc_info	*parse_proc(char *pid) ;
void		print_proc_info(t_proc_info *info) ;
bool		is_num(char c);
void		free_proc_info(t_proc_info *info) ;
void		delete_from_table(t_proc_info **table,int pid) ;
t_proc_info	*get_from_table(int pid, t_proc_info **table) ;
void		insert_to_table(t_proc_info **table,t_proc_info *process) ;
int			hash_function(pid_t pid); // the function returns the index by PID
bool		is_strnumeric(char *str) ;
void		print_hash_table(t_proc_info **table) ;
t_proc_info	**process_table();
void		free_hash_table(t_proc_info **table) ;
float		get_cpu_usage(char *buff, char *name) ;
void		push_child(t_proc_info *parent,t_proc_info *child) ;
void		print_tree(t_proc_info **hash_table, int depth, int size) ;
void		make_tree(t_proc_info **hash_table) ;
#endif
