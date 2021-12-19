
#include <stdio.h>
#include <unistd.h>
//#include <dir.h>
void	ft_pwd(char **envp);
void	ft_cd(char *path);

int	main(int argc, char **argv, char **envp)
{
	char	dir[200];

	getcwd(dir, 200);
	printf("Current directory is %s\n", dir);
	ft_cd("..");
	getcwd(dir, 200);
	printf("Current directory is %s\n", dir);
	return (0);
}
