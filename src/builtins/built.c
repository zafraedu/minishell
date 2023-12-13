#include "minishell.h"

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

void	ft_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->cmd_args[0], "echo", 4))
		ft_echo(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "cd", 2))
		ft_cd(msh); // old_path
	else if (!ft_strncmp(msh->cmd_args[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(msh->cmd_args[0], "export", 6))
		ft_export(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "unset", 5))
		ft_unset(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "env", 3))
		ft_env(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "exit", 4))
		ft_exit(msh); // exit_status
}
