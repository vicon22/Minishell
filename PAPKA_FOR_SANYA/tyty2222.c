
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
		ft_sig_child();
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
		ft_sig_par_ignore();
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
	if (output && (!ft_strncmp2(output->content, ">>", 3) || !ft_strncmp2(output->content, ">", 2)))
	{
		//output = output->next;
		n_output++;
		//printf("out1\n");
	}
	while (output && ft_strncmp2(output->content, ">>", 3) && ft_strncmp2(output->content, ">", 2))
	{
		output = output->next;
		n_output++;
		//printf("out2\n");
	}
	if (pipe && !ft_strncmp2(pipe->content, "|", 2))
	{
		//pipe = pipe->next;
		n_pipe++;
		//printf("1\n");
	}
	while (pipe && ft_strncmp2(pipe->content, "|", 2))
	{
		pipe = pipe->next;
		n_pipe++;
		//printf("2\n");
	}
	//printf("n_pipe:%d\n", n_pipe);
	//printf("n_output:%d\n", n_output);
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
	// write(2, path, ft_strlen(path));
	buildin = ft_find_buildin(argc, *envp);
	pipe(pip);
	pid = fork();
	if (!pid)
	{
		ft_sig_child();
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		if (buildin)
			buildin(argc, envp);
		else if (path)
			execve(path, argc, *envp);
		else
			ft_call_export(argc, envp, 127);
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		//waitpid(0, NULL, 0);
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
		ft_sig_child();
		if (buildin)
			buildin(argc, envp);
		else
			execve(path, argc, *envp);
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
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
		ft_sig_child();
		//		dup2(pip[0], 0);
		//		close(pip[0]);
		//		close(pip[1]);
		execve(cat[0], cat, envp);
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		waitpid(pid, NULL, 0);
	}
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
		ft_sig_child();
		i = read(0, &ch, 1);
		while (i)
		{
			write (1, &ch, 1);
			i = read(0, &ch, 1);
		}
		exit(0);
	}
	else
	{
		ft_sig_par_ignore();
		waitpid(pid, NULL, 0);
	}
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
		return ;
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
		return ;
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
			ft_sig_child();
			//if (!path)
			//	exit(127);
			execve(path, argv, *envp);
			exit (1);
		}
		else
		{
			ft_sig_par_ignore();
			//write(2, "@end@\n", 6);
			waitpid(0, &status, 0);
			//waitpid(0, &status, 0);
			//write(2, "-----\n", 6);
//			printf("status:%d\n", status);
			WIFEXITED(status);
			if (WIFSIGNALED(status))
			{
					if (WTERMSIG(status) == SIGINT)
						ft_call_export(argv, envp, 130);;
					if (WTERMSIG(status) == SIGQUIT)
						ft_call_export(argv, envp, 131);
			}
			else
			{
				if (status != 0)
					ft_call_export(argv, envp, 1);
				else
					ft_call_export(argv, envp, 0);
			}
		}
	}
}

int ft_wait_all_child_processes(t_arg *lst)
{
	int number_of_pipes;
	int i;
	t_arg *lst_saver;
	int status;

	lst_saver = lst;
	number_of_pipes = 0;
	i = 0;
	status = 0;
	while (lst_saver)
	{
		if (!ft_strncmp(lst_saver->content, "|", 2))
			number_of_pipes++;
		lst_saver = lst_saver->next;
	}
	while (i < number_of_pipes)
	{
		waitpid(0, &status, 0);
		i++;
	}
	return (status);
}


//void	ft_exec(t_arg *lst, char ***envp)
//{
//	int		in_out[2];
//	t_arg	*needful;
//	t_arg	*needful_next;
//	t_arg	*lst_saver;
//	int		logic_flag;
//	int 	status;
//
//	in_out[0] = dup(0);
//	in_out[1] = dup(1);
//	lst_saver = lst;
//	needful = ft_find_heredoc(lst);
//	if (needful)
//		ft_heredoc(needful->next->content, *envp);
//	if (lst->next == NULL)
//	{
//		ft_return_one_command(lst->path, lst->args, envp);
//	}
//	else
//	{
//		logic_flag = ft_lstcmp(lst);
//		while (logic_flag == 0)
//		{
//			needful = ft_find_output(needful);
//			if (ft_strlen(needful->content) == 1)
//				ft_rewrite(needful->next->content);
//			if (ft_strlen(needful->content) == 2)
//				ft_add(needful->next->content);
//			logic_flag = ft_lstcmp(needful);
//		}
//
//
//		needful = ft_find_command(lst);
//	}
//		status = ft_wait_all_child_processes(lst);
//		WIFEXITED(status);
//		if (WIFSIGNALED(status)) {
//			if (WTERMSIG(status) == SIGINT)
//				ft_call_export(lst->args, envp, 130);;
//			if (WTERMSIG(status) == SIGQUIT)
//				ft_call_export(lst->args, envp, 131);
//		} else {
//			if (status != 0)
//				ft_call_export(lst->args, envp, 1);
//			else
//				ft_call_export(lst->args, envp, 0);
//		}
//	}
//	dup2(in_out[0], 0);
//	dup2(in_out[1], 1);
//}

void	ft_exec(t_arg *lst, char ***envp)
{
	int		in_out[2];
	t_arg	*needful;
	t_arg	*needful_next;
	t_arg	*lst_saver;
	int		logic_flag;
	int 	status;

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
	else {
		logic_flag = ft_lstcmp(lst);
		//printf("                                  logic_flag: %d\n", logic_flag);
		//printf("before\n");
		if (lst->path)
			ft_pipe(lst->path, lst->args, envp);
		//printf("after\n");
		needful = lst;
		while (logic_flag >= 0) {
			if (logic_flag == 0) {
				needful = ft_find_output(needful);
				if (needful) {
					if (ft_strlen(needful->content) == 1)
						ft_rewrite(needful->next->content);
					if (ft_strlen(needful->content) == 2)
						ft_add(needful->next->content);
					//write(2, "---\n", 4);
					if (!needful->next->next || !ft_strncmp2(needful->next->next->content, "|", 2)) {
						ft_full_return_2(*envp);
						//dup2(in_out[1], 1);
					}
				}
			}
			if (logic_flag == 1) {
				needful = ft_find_pipe(needful);
				needful_next = ft_find_pipe(needful->next);
				if (!needful_next)
					needful_next = ft_find_output(needful);
//				if (!needful_next && !needful)
//				{
//
//				}
				if (needful_next) {
					//printf("pipe!\n");
					ft_pipe(needful->next->path, needful->next->args, envp);
				} else {
					//printf("return!\n");
					ft_return(needful->next->path, needful->next->args, envp);
				}
			}
			needful = needful->next;
			logic_flag = ft_lstcmp(needful);
			//printf("                                  logic_flag: %d\n", logic_flag);
		}
		//printf("---\n");
		ft_full_return(*envp);
		//printf("---\n");

		waitpid(0, &status, 0);
		WIFEXITED(status);
		if (WIFSIGNALED(status)) {
			if (WTERMSIG(status) == SIGINT)
				ft_call_export(lst->args, envp, 130);;
			if (WTERMSIG(status) == SIGQUIT)
				ft_call_export(lst->args, envp, 131);
		} else {
			if (status != 0)
				ft_call_export(lst->args, envp, 1);
			else
				ft_call_export(lst->args, envp, 0);
		}
	}
	//waitpid(0, NULL, 0);
	ft_wait_all_child_processes(lst);
	dup2(in_out[0], 0);
	dup2(in_out[1], 1);
}
