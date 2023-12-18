#include "minishell.h"

/**
 * @brief Simula el comando `echo` de shell.
 *
 * Esta función maneja el comando "echo", que imprime mensajes en la salida
 * estándar o la redirige según sea necesario. Puede incluir opciones como "-n"
 * para evitar el salto de línea al final del mensaje.
 *
 * @param msh Un puntero al contexto del shell.
 */
void	ft_echo(t_shell *msh)
{
	int	i;

	i = 1;
	msh->exit_status = 0;
	if (msh->cmd_args[1] && !ft_strncmp(msh->cmd_args[1], "-n", 2))
		i++;
	while (msh->cmd_args[i])
	{
		ft_putstr_fd(msh->cmd_args[i++], msh->parser->redir_out);
		if (msh->cmd_args[i])
			ft_putchar_fd(32, msh->parser->redir_out);
	}
	if (!(msh->cmd_args[1] && !ft_strncmp(msh->cmd_args[1], "-n", 2)))
		ft_putchar_fd(10, msh->parser->redir_out);
}
