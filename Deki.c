#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int ft_print_error(const char *str)
{	
	int i = 0;
	while(str[i])
	{
		i++;
	}
	write(STDERR_FILENO, str, i);
	return 1;
}

int ft_fatal_error(char **pointer)
{
	if(pointer)
	{
		free(pointer);
	}
	exit(ft_print_error("error: fatal\n"));
}

#include <stdio.h>
int ft_command_size(char **argv, const char *s)
{
	int i;
	if(!argv)
	{
		return 0;
	}
	i = 0;
	while(argv[i])
	{
		if(!strcmp(argv[i], s))
		{
			return i;
		}
		i++;
	}
	printf("cmd size == %d\n", i);
	return i;
}

char **ft_add_command(char **argv, int *i)
{
	int j;
	int size;
	char **temp;
	size = ft_command_size(argv + *i, ";");
	if(!size)
	{
		return NULL;
	}
	if(!(temp = (char **)malloc(sizeof(char *) * (size + 1))))
	{
		ft_fatal_error(NULL);
	}
	j = 0;
	while(j < size)
	{
		temp[j] = argv[j + *i];
		printf("j + *i = %d\n", j + *i);
		j++;
	}
	temp[j] = NULL;
	*i += size;
	return temp;
}

int ft_execute_cd(char **command)
{
	int i;

	i = 0;

	while(command[i])
	{
		i++;
	}
	if(i != 2)
	{
		return (ft_print_error("error: cd: bad arguments\n"));
	}
	if(chdir(command[1]) < 0)
	{
		ft_print_error("error: cd: cannot change directory to ");
		ft_print_error(command[1]);
		ft_print_error("\n");
	}
	return 0;
}

char **ft_next_pipe(char **command)
{
	int i = 0;

	if(!command)
	{
		return NULL;
	}
	while(command[i])
	{
		if(!strcmp(command[i], "|"))
		{
			return (command + i + 1);
		}
		i++;
	}

	return NULL;
}

int ft_execute_command(char **command, char **envp, char **pointer)
{
	pid_t pid;

	if((pid = fork()) < 0)
	{
		ft_fatal_error(pointer);
	}
	if(pid == 0)
	{
		if(execve(command[0], command, envp) < 0)
		{
			ft_print_error("error: cannot execute ");
			ft_print_error(command[0]);
			free(pointer);
			exit(ft_print_error("\n"));
		}
	}
	waitpid(0, NULL, 0);
	return 0;
}

int ft_execute_child(char **command, char **envp, char **temp, int in, int pipe_fd[2])
{
	if(dup2(in, STDIN_FILENO) < 0)
	{
		ft_fatal_error(command);
	}
	if(ft_next_pipe(temp) && dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		ft_fatal_error(command);
	}
	close(in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	temp[ft_command_size(temp, "|")] = NULL;
	ft_execute_command(temp, envp, command);
	free(command);
	exit(0);
}



int ft_execute(char **command, char **envp)
{
	int in;
	int pipe_fd[2];
	int nb_wait;
	pid_t pid;
	char **temp = command;

	if(!ft_next_pipe(command))
	{
		return (ft_execute_command(command, envp, command));
	}
	if((in = dup(STDIN_FILENO)) < 0)
	{
		return (ft_fatal_error(command));
	}
	nb_wait = 0;

	while(temp)
	{
		if(pipe(pipe_fd) < 0 || (pid = fork()) < 0)
		{
			ft_fatal_error(command);
		}
		if(pid == 0)
		{
			ft_execute_child(command, envp, temp, in, pipe_fd);
		}
		else
		{
			if(dup2(pipe_fd[0], in) < 0)
			{
				ft_fatal_error(command);
			
			}
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			temp = ft_next_pipe(temp);
			nb_wait++;
		}

	}
	close(in);
	while(nb_wait-- >= 0)
	{
		waitpid(0, NULL, 0);
	}
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	int i = 1;
	char **command;

	command = NULL;

	while(i < argc)
	{
		command = ft_add_command(argv, &i);
		if(command && !strcmp(command[0], "cd"))
		{
			ft_execute_cd(command);
		}
		else if(command)
		{
			ft_execute(command, envp);
		}
		if(command)
		{
			free(command);
		}
		i++;
	}
	return 0;
}