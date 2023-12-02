#include "minishell.h"

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->cmd_args[1] && !ft_strncmp(shell->cmd_args[1], "-n", 2))
		i++;
	while (shell->cmd_args[i])
	{
		ft_putstr_fd(shell->cmd_args[i++], shell->parser->redir_out);
		if (shell->cmd_args[i])
			ft_putchar_fd(32, shell->parser->redir_out);
	}
	if (!(shell->cmd_args[1] && !ft_strncmp(shell->cmd_args[1], "-n", 2)))
		ft_putchar_fd(10, shell->parser->redir_out);
}
