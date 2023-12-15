#include "minishell.h"

void	ft_pwd(t_shell *msh)
{
	char	*pwd;

	msh->exit_status = 0;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
