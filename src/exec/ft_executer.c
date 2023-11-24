#include "minishell.h"

// ns pq se me sale del programa

// void	ft_exec_cmd(t_shell *msh, t_parser *parser)
// {
// 	pid_t	pid;

// 	if (is_builting(msh)) // pipe_config ?
// 	{
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid < 0)
// 		exit(0);       //err_msh;
// 	else if (pid == 0) // children
// 	{
// 		msh->cmd = get_cmd(msh->paths, msh->cmd_args[0]);
// 		if (!msh->cmd)
// 		{
// 			//err_msh();
// 			return ;
// 		}
// 		if (parser->redir_in > 2) //mejorar esto
// 		{
// 			dup2(parser->redir_in, STDIN_FILENO);
// 			close(parser->redir_in);
// 		}
// 		if (parser->redir_out > 2) //junto a este
// 		{
// 			dup2(parser->redir_out, STDOUT_FILENO);
// 			close(parser->redir_out);
// 		}
// 		if (execve(msh->cmd, msh->cmd_args, msh->envp) < 0)
// 		{
// 			perror("execve");
// 			ft_memfree_all(msh->paths);
// 			ft_memfree_all(msh->cmd_args);
// 			ft_memfree(msh->cmd);
// 			ft_memfree(msh);
// 		}
// 		exit(127); //el exit si es necesario; el 127 sera exit_status
// 	}
// 	else // &msh->exit_status (donde va NULL);
// 		waitpid(pid, NULL, 0);
// }

void	ft_executer(t_shell *msh, char **envp)
{
	t_parser	*parser;

	parser = msh->parser;
	msh->stdincpy = dup(STDIN_FILENO);
	msh->stdoutcpy = dup(STDOUT_FILENO);
	dup2(parser->redir_in, STDIN_FILENO);
	msh->envp = ft_arraydup(envp);
	msh->paths = get_paths(envp); //ns si va aqui o dentro del bucle
	while (parser)
	{
		// extend quotes " $ " (parser->cmd)
		// if (error) break ;
		// ignorequotes parser->cmd
		msh->cmd_args = ft_split(parser->cmd, ' ');
		// if no hay parser->cmd ?
		// me quita espacios "hola                adios"
		run_node(msh, parser);
		// ft_exec_cmd(msh, parser);
		// ft_memfree_all(msh->cmd_args);
		parser = parser->next;
	}
	restore_std(msh->stdincpy, msh->stdoutcpy);
	ft_memfree_all(msh->envp);
	ft_memfree_all(msh->paths);
}

// char	**get_cmd_args(t_lexer *lex) // no funciona :) es solo una idea
// {
// 	char	**new_array;
// 	t_lexer	*tmp;
// 	int		i;

// 	if (!lex)
// 		return (NULL);
// 	tmp = lex;
// 	i = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == T_CMD)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	new_array = ft_calloc(sizeof(char *), i + 1);
// 	tmp = lex;
// 	i = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == T_CMD)
// 			new_array[i++] = tmp->data;
// 		tmp = tmp->next;
// 	}
// 	return (new_array);
// }
