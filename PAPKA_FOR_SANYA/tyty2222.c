
#include "minishell_2.h"

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	//printf("s1: %s\n", s1);
	//printf("s2: %s\n", s2);
//	if (s1 == NULL)
//		return (1);
	while (count < n && *(s1 + count) && *(s2 + count))
	{
		if (*(s1 + count) != *(s2 + count))
			return ((unsigned char)*(s1 + count)
					- (unsigned char)*(s2 + count));
		count++;
	}
	if (count < n)
	{
		if (*(s1 + count) != *(s2 + count))
			return ((unsigned char)*(s1 + count)
					- (unsigned char)*(s2 + count));
	}
	return ((unsigned char)0);
}

void	ft_heredoc(char *stop, char **envp)
{
	int		pip[2];
	int		pid;
	char	*args_str;

	pipe(pip);
	pid = fork();
	if (!pid)
	{
		args_str = readline("> ");
		while (ft_strncmp2(args_str, stop, ft_strlen(stop)))
		{
			while (ft_strchr(args_str, '\"') && ft_closed_quote(ft_strchr(args_str, '\"')) && ft_strchr(args_str, '$'))
				ft_replace_by_envp(&args_str, envp);
			while (!(ft_strchr(args_str, '\'') && ft_closed_quote(ft_strchr(args_str, '\''))) && ft_strchr(args_str, '$'))
				ft_replace_by_envp(&args_str, envp);
			write(pip[1], args_str, ft_strlen(args_str));
			write(pip[1], "\n", 1);
			args_str = readline("> ");
		}
		close(pip[1]);
		close(pip[0]);
		exit (0);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		waitpid(0, NULL, 0);
	}
}

//void	ft_return(char *path, char **argc, char **envp)
//{
//	int		pid;
//	int		pip[2];
//
//	pipe(pip);
//	pid = fork();
//	if (pid == 0)
//		execve(path, argc, envp);
//	else
//		waitpid(pid, NULL, 0);
//}

t_arg	*ft_find_heredoc(t_arg *lst)
{
	t_arg	*heredoc;

	heredoc = lst;
	while (heredoc && ft_strncmp2(heredoc->content, "<<", 3))
	{
		heredoc = heredoc->next;
	}
	return (heredoc);
}

t_arg	*ft_find_output(t_arg *lst)
{
	t_arg	*output;

	output = lst;
	while (output && ft_strncmp2(output->content, ">>", 3) && ft_strncmp2(output->content, ">", 2))
	{
		output = output->next;
	}
	return (output);
}

t_arg	*ft_find_pipe(t_arg *lst)
{
	t_arg	*pipe;

	pipe = lst;
	while (pipe && ft_strncmp2(pipe->content, "|", 2))
	{
		pipe = pipe->next;
	}
	return (pipe);
}

int	ft_lstcmp(t_arg *lst)
{
	int		n_pipe;
	int		n_output;
	t_arg	*pipe;
	t_arg	*output;

	n_pipe = -1;
	n_output = -1;
//	printf("ft_lstcmp: %s\n", lst->content);
//	if (lst->next)
//		printf("ft_lstcmp->next: %s\n", lst->next->content);
	pipe = lst;
	output = lst;
	if (output && !ft_strncmp2(output->content, ">>", 3) && ft_strncmp2(output->content, ">", 2))
		n_output++;
	while (output && ft_strncmp2(output->content, ">>", 3) && ft_strncmp2(output->content, ">", 2))
	{
		output = output->next;
		n_output++;
	}
	if (pipe && !ft_strncmp2(pipe->content, "|", 2))
		n_pipe++;
	while (pipe && ft_strncmp2(pipe->content, "|", 2))
	{
		pipe = pipe->next;
		n_pipe++;
	}
//	printf("n_pipe:%d\n", n_pipe);
//	printf("n_output:%d\n", n_output);
	if (n_pipe == n_output)
		return (-1);
	if (n_pipe >= 0 && n_output >= 0)
	{
		if (n_pipe > n_output)
			return (0);
		else
			return (1);
	}
	else
	{
		if (n_pipe < 0)
			return (0);
		else
			return (1);
	}
}

void	ft_pipe(char *path, char **argc, char ***envp)
{
	int		pid;
	int		pip[2];
	void	(*buildin)(char **argc, char ***envp);

	errno = 0;
	buildin = ft_find_buildin(argc, *envp);
	pipe(pip);
	pid = fork();
	if (!pid)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		if (buildin)
			buildin(argc, envp);
		else
			execve(path, argc, *envp);
		write(2, "bash: ", 6);
		perror(argc[0]);
		exit(0);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
	}
}

void	ft_return(char *path, char **argc, char ***envp)
{
	int		pid;
	int		pip[2];
	void	(*buildin)(char **argc, char ***envp);

	buildin = ft_find_buildin(argc, *envp);
	pipe(pip);
	pid = fork();
	if (!pid)
	{
		if (buildin)
			buildin(argc, envp);
		else
			execve(path, argc, *envp);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	ft_full_return(char **envp)
{
	int		pid;
	char	*cat[2];

	cat[0] = "/bin/cat";
	cat[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		//		dup2(pip[0], 0);
		//		close(pip[0]);
		//		close(pip[1]);
		execve(cat[0], cat, envp);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_full_return_2(char **envp)
{
	int		pid;
	char	*cat[2];
	int i;
	char ch;

	cat[0] = "/bin/cat";
	cat[1] = 0;
	pid = fork();
	if (pid == 0)
	{
		i = 1;
		while (i == 1)
		{
			i = read(0, &ch, 1);
			write (1, &ch, 1);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_add(char *file_name)
{
	int		pip[2];
	int		fd;
	int		pid;

	//write(2, "+++\n", 4);
	//pipe(pip);
	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
	{
		write(2, "Error with open\n", 16);
		exit(1);
	}
	//	pid = fork();
	//	if (!pid)
	//	{
	//		dup2(fd, 1);
	//	}
	dup2(fd, 1);
	//close(fd);
	//	else
	//		//waitpid(pid, NULL, 0);
}

void	ft_rewrite(char *file_name)
{
	//int		pip[2];
	int		fd;
	int		pid;

	//write(2, "---\n", 4);
	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		write(2, "Error with open\n", 16);
		exit(1);
	}
	//	pid = fork();
	//	if (!pid)
	//	{
	//		dup2(fd, 1);
	//	}
	dup2(fd, 1);
	//close(fd);
	//	else
	//		//waitpid(pid, NULL, 0);
	//	else
	//		//waitpid(pid, NULL, 0);
}

void	ft_return_one_command(char *path, char **argv, char ***envp)
{
	int		pid;
	void	(*buildin)(char **argc, char ***envp);
	int status;

	errno = 0;
	buildin = ft_find_buildin(argv, *envp);
	if (buildin)
		buildin(argv, envp);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execve(path, argv, *envp);
			printf("---\n");
			printf("errno:%d\n", errno);
			write(2, "bash: ", 6);
			perror(argv[0]);
			//ft_puterror_all(argv[0]);
			printf("---\n");
			exit (1);
		}
		else
		{
			waitpid(0, &status, 0);
			ft_putnbr_fd(status, 2);
			if (WIFEXITED(status))
				printf("%d", WEXITSTATUS(status));
			if (status != 0)
				ft_call_export(argv, envp);
		}

	}
}

void	ft_exec(t_arg *lst, char ***envp)
{
	int		in_out[2];
	t_arg	*needful;
	t_arg	*needful_next;
	t_arg	*lst_saver;
	int		logic_flag;

	in_out[0] = dup(0);
	in_out[1] = dup(1);
	lst_saver = lst;
	needful = ft_find_heredoc(lst);
	if (needful)
		ft_heredoc(needful->next->content, *envp);
	if (lst->next == NULL)
	{
		ft_return_one_command(lst->path, lst->args, envp);
	}
	else
	{
		ft_pipe(lst->path, lst->args, envp);
		logic_flag = ft_lstcmp(lst);
		//printf("                                  logic_flag: %d\n", logic_flag);
		needful = lst;
		while (logic_flag >= 0)
		{
			if (logic_flag == 0)
			{
				needful = ft_find_output(needful);
				if (needful)
				{
					if (ft_strlen(needful->content) == 1)
						ft_rewrite(needful->next->content);
					if (ft_strlen(needful->content) == 2)
						ft_add(needful->next->content);
					ft_full_return_2(*envp);
					dup2(in_out[1], 1);
				}
			}
			if (logic_flag == 1)
			{
				needful = ft_find_pipe(needful);
				needful_next = ft_find_pipe(needful->next);
				if (!needful_next)
					needful_next = ft_find_output(needful);
				if (needful_next)
				{
					//printf("pipe!\n");
					ft_pipe(needful->next->path, needful->next->args, envp);
				}
				else
				{
					//printf("return!\n");
					//printf("++++\n");
					ft_return(needful->next->path, needful->next->args, envp);
					//printf("++++\n");
				}
			}
			needful = needful->next;
			logic_flag = ft_lstcmp(needful);
			//printf("                                  logic_flag: %d\n", logic_flag);
		}
		//printf("---\n");
		ft_full_return(*envp);
		//printf("---\n");
	}
	dup2(in_out[0], 0);
	dup2(in_out[1], 1);
}

//void	ft_exec(t_arg *lst, char **envp)
//{
//	int		pid;
//	int		pip[2];
//	int		input;
//	char	*args_str;
//	int		status;
//
//	input = dup(0);
//
//	//	pipe(pip);
//	//	pid = fork();
//	//	if (!pid)
//	//	{
//	//		close(pip[0]);
//	//		args_str = readline("> ");
//	//		while (ft_strncmp2(args_str, lst->next->next->content, ft_strlen(lst->next->next->content)))
//	//		{
//	//			write(pip[1], args_str, ft_strlen(args_str));
//	//			write(pip[1], "\n", 1);
//	//			args_str = readline("> ");
//	//		}
//	//		close(pip[1]);
//	//		exit (0);
//	//	}
//	//	else
//	//	{
//	//		close(pip[1]);
//	//		dup2(pip[0], 0);
//	//		close(pip[0]);
//	//		waitpid(pid, &status, 0);
//	//	}
//	//	pid = fork();
//	//	if (pid == 0)
//	//	{
//	////		dup2(pip[0], 0);
//	////		close(pip[0]);
//	////		close(pip[1]);
//	//		execve(lst->path, lst->args, envp);
//	//	}
//	//	close(pip[0]);
//	//	close(pip[1]);
//	//	waitpid(0, &status, 0);
//	printf("----\n");
//	ft_heredoc(lst->next->next->content, envp);
//	ft_return(lst->path, lst->args, envp);
//	printf("----\n");
//	dup2(input, 0);
//}

//void	ft_exec(t_arg *lst, char **envp)
//{
//	int		pid;
//	int		pip[2];
//	char	*args_str;
//	int		status;
//
//	pipe(pip);
//	if (pid < 0)
//	{
//		printf("fork error in ft_exec\n");
//		exit(1);
//	}
//	pid = fork();
//	if (!pid)
//	{
//		args_str = readline("> ");
//		while (ft_strncmp2(args_str, lst->next->next->content, ft_strlen(lst->next->next->content)))
//		{
//			write(pip[1], args_str, ft_strlen(args_str));
//			write(pip[1], "\n", 1);
//			args_str = readline("> ");
//		}
//		close(pip[1]);
//	}
//	else
//	{
//		close(pip[1]);
//		waitpid(0, &status, 0);
//	}
//	pid = fork();
//	if (pid == 0)
//	{
//		dup2(pip[0], 0);
//		close(pip[0]);
//		close(pip[1]);
//		execve(lst->path, lst->args, envp);
//	}
//	close(pip[0]);
//	waitpid(0, &status, 0);
//}
