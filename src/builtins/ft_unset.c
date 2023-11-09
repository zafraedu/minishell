#include "minishell.h"

void	ft_unset(t_shell *msh)
{
	int	pos;
	int	i;

	i = 1;
	if (!msh->cmd_args[i])
		return ;
	while (msh->cmd_args[i])
	{
		pos = ft_foundenv(msh->cmd_args[i], msh->envp);
		if (pos >= 0)
			msh->envp = ft_arraydelete(pos, msh->envp);
		i++;
	}
}
