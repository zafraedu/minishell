#include "minishell.h"

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
