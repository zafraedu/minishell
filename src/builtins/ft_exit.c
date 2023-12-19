#include "minishell.h"

static int	check_exit_args(t_shell *msh);

/**
 * @brief Termina la ejecución del shell con un código de salida específico.
 *
 * Esta función maneja el comando "exit", que termina la ejecución del shell
 * con un código de salida específico. Puede recibir argumentos adicionales para
 * establecer el código de salida, y si se proporcionan demasiados, imprime un
 * mensaje de error y termina con un código de salida correspondiente.
 *
 * @param msh Un puntero al contexto del shell.
 */
void	ft_exit(t_shell *msh)
{
	ft_putendl_fd("exit", 2);
	msh->exit_status = check_exit_args(msh);
	if (msh->exit_status != 1)
		exit(msh->exit_status);
	ft_putendl_fd("exit: too many arguments", 2);
}

/**
 * @brief Verifica y procesa los argumentos para el comando "exit" del shell.
 *
 * Esta función valida los argumentos proporcionados al comando "exit" y
 * devuelve el código de salida correspondiente. Si hay errores en los
 * argumentos, imprime un mensaje de error y devuelve un código de salida
 * específico.
 *
 * @param msh Un puntero al contexto del shell.
 * @return El código de salida para el comando "exit"
 * o un código de error (-1 en caso de error).
 */
static int	check_exit_args(t_shell *msh)
{
	int	i;

	if (msh->count_cmd_args > 2)
		return (1);
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
