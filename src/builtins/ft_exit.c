#include "minishell.h"

static int	check_exit_args(t_shell *msh)
{
	int	i;

	if (msh->count_cmd_args > 2)
		return (-1);
	if (msh->cmd_args[1])
	{
		i = -1;
		while (msh->cmd_args[1][++i])
		{
			if (!ft_isdigit(msh->cmd_args[1][i]))
			{
				printf("exit: %s: numeric argument required\n",
						msh->cmd_args[1]);
				return (2);
			}
		}
		return (ft_atoi(msh->cmd_args[1]));
	}
	return (0);
}

void	ft_exit(t_shell *msh)
{
	ft_putendl_fd("exit", 2);
	msh->exit_status = check_exit_args(msh);
	if (msh->exit_status != -1)
		exit(msh->exit_status);
	ft_putendl_fd("exit: too many arguments", 2);
}
