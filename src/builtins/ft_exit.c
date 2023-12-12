#include "minishell.h"

// verifica que el argumento sea un numero
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
	int	shell_exit;

	ft_putendl_fd("exit", 2);
	shell_exit = check_exit_args(msh);
	if (shell_exit != -1)
	{
		// ft_memfree_all(msh->cmd_args);
		// hay que liberar memoria antes
		//	free global
		//	free ...
		exit(shell_exit);
	}
	ft_putendl_fd("exit: too many arguments", 2);
}
