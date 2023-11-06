#include "minishell.h"

/**
 * realmente no va la estructura t_shell pero lo dejo asi por ahora
 * para probar
 * no confundir los comandos del parser y los comandos ejecutables ;)
*/
int	is_builting(t_shell *msh)
{
	if (!ft_strncmp(msh->cmd_args[0], "echo", 4))
		ft_echo(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "cd", 2))
		ft_cd(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "pwd", 3))
		ft_pwd();
	// else if (!ft_strncmp(parser->cmd, "export", 6))
	// 	ft_export(parser); //no existe
	// else if (!ft_strncmp(parser->cmd, "unset", 5))
	// 	ft_unset(parser); //no existe
	else if (!ft_strncmp(msh->cmd_args[0], "env", 3))
		ft_env(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "exit", 4))
		ft_exit(msh); // incompleto
	else
		return (0);
	return (1);
}
