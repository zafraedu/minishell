#include "minishell.h"

/**
 * @brief Verifica si el comando actual es un(builtin) en el shell.
 *
 * Esta función compara el comando actual con una lista predefinida de comandos
 * integrados y devuelve 1 si el comando es un builtin, o 0 si no lo es.
 *
 * @param msh Un puntero al contexto del shell.
 * @return 1 si el comando es un builtin, 0 en caso contrario.
 */
int	is_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->cmd_args[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(msh->cmd_args[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(msh->cmd_args[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(msh->cmd_args[0], "export", 6))
		return (1);
	else if (!ft_strncmp(msh->cmd_args[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(msh->cmd_args[0], "env", 3))
		return (1);
	else if (!ft_strncmp(msh->cmd_args[0], "exit", 4))
		return (1);
	else
		return (0);
}

/**
 * @file built.c
 * @brief Ejecuta el (builtin) correspondiente según el comando actual.
 *
 * Esta función determina el comando integrado actual y llama a la función
 * correspondiente para ejecutarlo.
 *
 * @param msh Un puntero al contexto del shell.
 */
void	ft_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->cmd_args[0], "echo", 4))
		ft_echo(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "cd", 2))
		ft_cd(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "pwd", 3))
		ft_pwd(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "export", 6))
		ft_export(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "unset", 5))
		ft_unset(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "env", 3))
		ft_env(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "exit", 4))
		ft_exit(msh);
}
