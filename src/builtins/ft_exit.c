#include "minishell.h"

// verifica que el argumento sea un numero
static int	check_exit_args(t_shell *shell)
{
	int	i;

	if (shell->cmd_args[1])
	{
		i = 0;
		while (shell->cmd_args[1][i])
		{
			if (!ft_isdigit(shell->cmd_args[1][i]))
			{
				perror("exit: numeric argument required: ");
				ft_putendl_fd(shell->cmd_args[1], 2);
				return (-1);
			}
			i++;
		}
		return (ft_atoi(shell->cmd_args[1]));
	}
	return (i);
}

void	ft_exit(t_shell *shell)
{
	int	shell_exit;

	if (shell->cmd_args[2]) // si hay dos argumentos despues de exit
	{
		perror("exit: too many arguments: "); // hay que mejorar esto
		return ;
	}
	shell_exit = check_exit_args(shell);
	if (shell_exit != -1)
	{
		// hay que liberar memoria antes
		//	free global
		//	free ...
		exit(shell_exit);
	}
}
