#include "minishell.h"

static void	child_proccess(t_shell *msh);
static void	exec_cmd(t_shell *msh);
static void	ft_next_cmd(t_shell *msh);
static void	handle_status(t_shell *msh);

void	ft_executer(t_shell *msh)
{
	pid_t	pid;

	while (msh->parser)
	{
		if (!ft_isascii(msh->parser->cmd[0]))
		{
			msh->exit_status = 1;
			break ;
		}
		msh->cmd_args = ft_split_shell(msh, msh->parser->cmd, 32);
		if (is_builtin(msh))
			ft_builtin(msh);
		else
		{
			g_signal = S_CMD;
			pid = fork();
			if (pid == 0)
				child_proccess(msh);
			else
				waitpid(-1, &msh->exit_status, 0);
			handle_status(msh);
		}
		ft_next_cmd(msh);
	}
}

static void	child_proccess(t_shell *msh)
{
	if (is_builtin(msh))
		ft_builtin(msh);
	else
		exec_cmd(msh);
}

static void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**envp;

	envp = env_to_array(msh);
	if (msh->parser->redir_in != 0)
		dup2(msh->parser->redir_in, STDIN_FILENO);
	if (msh->parser->redir_out != 1)
		dup2(msh->parser->redir_out, STDOUT_FILENO);
	cmd_path = get_cmd_path(msh->cmd_args[0], msh->env);
	if (!ft_isalnum(msh->cmd_args[0][0]))
	{
		ft_memfree(cmd_path);
		cmd_path = msh->cmd_args[0];
	}
	execve(cmd_path, msh->cmd_args, envp);
	exit(127);
}

static void	ft_next_cmd(t_shell *msh)
{
	t_parser	*tmp;

	ft_memfree(msh->parser->cmd);
	ft_memfree_all(msh->cmd_args);
	if (msh->parser->redir_in != 0)
		close(msh->parser->redir_in);
	if (msh->parser->redir_out != 1)
		close(msh->parser->redir_out);
	tmp = msh->parser;
	msh->parser = msh->parser->next;
	ft_memfree(tmp);
}
static void	handle_status(t_shell *msh)
{
	if (WIFEXITED(msh->exit_status))
		msh->exit_status = WEXITSTATUS(msh->exit_status);
	if (msh && msh->exit_status == 127)
		printf("%s: command not found\n", msh->cmd_args[0]);
	if (g_signal == S_SIGINT_CMD)
		msh->exit_status = 130;
	g_signal = S_BASE;
}
