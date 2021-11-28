#ifndef EVGENII_H
# define EVGENII_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct r_envp
{
	char	*name;
	char	*value;
	char	*allstr;
	struct r_envp	*next;
}	t_envp;

void	ft_echo(int argc, char **argv);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_export(int argc, char **argv, char **envp);
void	ft_lstadd_back(t_envp **lst, t_envp *new);
t_envp	*ft_lstnew_envp(char *envp);
char	*ft_take_name(char *str);
char	*ft_take_value(char *str);

/*libft's functions*/
size_t	ft_strlen(char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

#endif
