#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp)
		return ;
	while (shell->envp[i])
		ft_putendl_fd(shell->envp[i++], 1);
}
