#include "minishell.h"

static char	**env_to_array(t_shell *info)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 0;
	tmp = info->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = info->env;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->var_name, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value_var);
		free(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

static void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**envp;

	envp = env_to_array(msh);
	cmd_path = get_cmd_path(msh->cmd_args[0], msh->env);
	if (ft_isalnum(msh->cmd_args[0][0]) && !access(msh->cmd_args[0], X_OK))
		cmd_path = msh->cmd_args[0];
	if (execve(cmd_path, msh->cmd_args, envp) == -1)
	{
		printf("test: execve\n"); // ejecucion de un comando mal
	}
	exit(127);
}

void	ft_executer(t_shell *msh)
{
	pid_t		pid;
	t_parser	*tmp;

	while (msh->parser)
	{
		msh->cmd_args = ft_split_shell(msh, msh->parser->cmd, ' ');
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
				waitpid(-1, &msh->exit_status, 0);
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
}
