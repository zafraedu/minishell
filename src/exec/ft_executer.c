#include "minishell.h"

void	exec_cmd(t_shell *msh)
{
	char	**paths;
	char	*cmd_path;

	if (msh->parser->redir_in != 0)
		dup2(msh->parser->redir_in, STDIN_FILENO);
	if (msh->parser->redir_out != 1)
		dup2(msh->parser->redir_out, STDOUT_FILENO);
	paths = get_paths(msh->envp);
	cmd_path = get_cmd(paths, msh->cmd_args[0]);
	execve(cmd_path, msh->cmd_args, msh->envp);
	exit(127);
}

void	ft_executer(t_shell *msh)
{
	pid_t	pid;

	t_parser *tmp; // temporal, necesario para el free
	while (msh->parser)
	{
		msh->cmd_args = ft_split_shell(msh->parser->cmd, ' ');
		ft_memfree(msh->parser->cmd);
		if (is_builtin(msh) && msh->parser->next == NULL)
			ft_builtin(msh);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (is_builtin(msh))
					ft_builtin(msh);
				else
					exec_cmd(msh);
			}
			else
				waitpid(-1, NULL, 0);
			//err msg
		}
		ft_memfree_all(msh->cmd_args);
		if (msh->parser->redir_in != 0)
			close(msh->parser->redir_in);
		if (msh->parser->redir_out != 1)
			close(msh->parser->redir_out);
		tmp = msh->parser;
		msh->parser = msh->parser->next;
		ft_memfree(tmp);
	}
	// ft_memfree_all(msh->paths); //? ns si es nececsario
}
