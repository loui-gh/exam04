#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
/* PARSING CMDS: 
\0 or ";" define a cmd. Save in a malloc'd dbl ptr, then printf and free 

NEXT find "|"*/
void	ft_puterr(char *msg, char *cmd);

char **ft_find_cmd(char **argv, int placeholder, int i)
{
	char	**cmd;
	int		size;

	size = i - placeholder;
	cmd = (char **)malloc(sizeof(char *) * size + 1);

	if (!cmd)
		ft_puterr("error: fatal", NULL);
	//printf("size of cmd = %d\n", size);
	
	int j = 0;
	while (placeholder < i)
	{
		cmd[j] = argv[placeholder];
		j++;
		placeholder++;
	}
	return (cmd);
}

int	execute_cmd(char **argv_1cmd, char **envp)
{
	// pid_t	process_id;

	// if (process_id = fork < 0)
	// {
	// }
	ft_puterr("error: cannot execute ", argv_1cmd[0]);
	free (argv_1cmd);
	envp++;
	return (0);


}

int	main (int argc, char **argv, char **envp)
{
	int		i;
	int		placeholder;
	char	**cmd;

	i = 1;
	placeholder = 1;
	cmd = NULL;
	while (i < argc)
	{
		if (strcmp(argv[i], ";") == 0)
		{
			cmd = ft_find_cmd(argv, placeholder, i);
			write(1, "1\n", 2);
			if (cmd)
				execute_cmd(cmd, envp);
			placeholder = i + 1;
		}
		i++;
	}
	cmd = ft_find_cmd(argv, placeholder, i);
	if (cmd)
		execute_cmd(cmd, envp);
	return (0);
}

void	ft_puterr(char *msg, char *cmd)
{
	int	i;

	i = 0;
	while(msg[i] != '\0')
	{
		write(STDERR_FILENO, &msg[i], 1);
		i++;
	}
	i = 0;
	while(cmd[i] != '\0')
	{
		write(STDERR_FILENO, &cmd[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);

}