#include "minishell.h"

void	ft_add_nodes(t_parser **cmd_node, t_lexer *lex)
{
	int	start;
	int	num_pipes;
	int	i;
	int	end;

	start = 0;
	num_pipes = ft_count_pipes(lex);
	i = 0;
	while (i <= num_pipes)
	{
		end = get_last(lex, start);
		ft_fill_node(lex, cmd_node, start, end);
		if (i < num_pipes)
		{
			(*cmd_node)->next = ft_calloc(1, sizeof(t_parser));
			*cmd_node = (*cmd_node)->next;
		}
		start = end + 2;
		i++;
	}
}

void	ft_parser(t_parser **parser, t_lexer *lex)
{
	t_parser	*cmd_node;

	// t_parser	*tmp2;
	if (lex == NULL)
		return ;
	ft_index(lex);
	if (*parser == NULL)
	{
		*parser = ft_calloc(1, sizeof(t_parser));
		cmd_node = *parser;
	}
	else
		cmd_node = *parser;
	if (cmd_node)
		ft_add_nodes(&cmd_node, lex);
	//Imprimir lista de comandos (test)
	// tmp2 = *parser;
	// while (tmp2)
	// {
	// printf("\n");
	// printf("command: %s\n", tmp2->cmd);
	// if (tmp2->redir_in)
	// printf("file_input: %i\n", tmp2->redir_in);
	// if (tmp2->redir_out)
	// printf("file_output: %i\n", tmp2->redir_out);
	// if (tmp2->heredoc)
	// 	printf("heredoc, limiter: %s\n", tmp2->heredoc);
	// tmp2 = tmp2->next;
	// }
}
