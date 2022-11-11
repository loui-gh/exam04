#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
/* STEP1: parse commands - first find ";", then determine size of cmds, then save each in a 
malloc'd cmd, which is then freed at the next one, then find "|"*/
//./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell


//int	main (int argc, char **argv, char **envp)
void	ft_print_stderr(void);

char **ft_find_cmd(char **argv, int placeholder, int i)
{
	char	**cmd;
	int		size;

	size = i - placeholder;
	cmd = (char **)malloc(sizeof(char *) * size + 1);

	if (!cmd)
		ft_print_stderr();
	printf("size of cmd = %d\n", size);
	
	while (placeholder < i)
	{
		printf("argv[%d] = %s\n", placeholder, argv[placeholder]);
		placeholder++;
	}
	return (cmd);

}

int	main (int argc, char **argv)
{
	int		i;
	int		placeholder;

	i = 1;
	placeholder = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], ";") == 0)
		{
			ft_find_cmd(argv, placeholder, i);
			placeholder = i + 1;
		}
		i++;
	}
	ft_find_cmd(argv, placeholder, i);
	printf("--END--\n");
	return (0);
}

void	ft_print_stderr(void)
{
	write(STDERR_FILENO, "error: fatal\n", 13);
}