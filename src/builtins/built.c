#include "minishell.h"

/**
 * realmente no va la estructura t_shell pero lo dejo asi por ahora
 * para probar
 * no confundir los comandos del parser y los comandos ejecutables ;)
*/
int	is_builting(t_shell *msh, t_parser *p, int stdoutcpy)
{
	dup2(p->redir_out, STDOUT_FILENO);
	if (!ft_strncmp(msh->cmd_args[0], "echo", 4))
		ft_echo(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "cd", 2))
		ft_cd(msh); // old_path
	else if (!ft_strncmp(msh->cmd_args[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(msh->cmd_args[0], "export", 6))
		ft_export(msh); // sort ?
	else if (!ft_strncmp(msh->cmd_args[0], "unset", 5))
		ft_unset(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "env", 3))
		ft_env(msh);
	else if (!ft_strncmp(msh->cmd_args[0], "exit", 4))
		ft_exit(msh); // exit_status
	else
		return (0);
	dup2(stdoutcpy, STDOUT_FILENO);
	dup2((p->redir_out - 1), STDIN_FILENO);
	close(p->redir_out);
	close(p->redir_out - 1);
	return (1);
}
