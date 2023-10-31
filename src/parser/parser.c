#include "minishell.h"

// static void	parser_lstadd_back(t_parser **parser, t_parser *new)
// {
// 	t_parser	*current;

// 	if (*parser == NULL)
// 		*parser = new;
// 	else
// 	{
// 		current = *parser;
// 		while (current != NULL)
// 			current = (current)->next;
// 		(current)->next = new;
// 	}
// }

void	parser_new_cmd(t_parser **parser, t_lexer *lex)
{
	t_parser	*new;
	int			i;

	(void)parser;
	i = 0;
	new = ft_calloc(1, sizeof(t_parser));
	while (lex && lex->type != T_PIPE)
	{
		if (lex->type == T_CMD)
			new->cmd = ft_calloc((ft_strlen(lex->data) + 1), sizeof(char));
		if (lex->type == T_ARG)
		{
			while (lex && lex->type == T_ARG)
			{
				lex = lex->next;
				i++;
			}
			break ;
		}
		lex = lex->next;
	}
	new->args = ft_calloc((i + 1), sizeof(char *));
	new->args[i] = NULL;
	new->next = NULL;
	// parser_lstadd_back(parser, new);
}

// int	parser_open(t_lexer *lex)
// {
// 	int	fd;

// 	fd = -1;
// 	if (lex->next && lex->type == T_REDIR_IN)
// 		fd = open(lex->next->data, 0777);
// 	else if (lex->next && lex->type == T_REDIR_OUT)
// 		fd = open(lex->next->data, 0777, O_TRUNC);
// 	else if (lex->next && lex->type == T_APPEND)
// 		fd = open(lex->next->data, 0777, O_APPEND);
// 	return (fd);
// }

// char	**get_args(t_lexer *lex)
// {
// 	int		i;
// 	char	**args;

// 	i = 0;
// 	args = NULL;
// 	while (lex && lex->type == T_ARG)
// 	{
// 		args[i] = ft_calloc((ft_strlen(lex->data) + 1), sizeof(char));
// 		args[i] = lex->data;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

// t_lexer	*p_fill_arg(t_lexer *lex, t_parser **par)
// {
// 	int	i;

// 	i = -1;
// 	while (lex && lex->type == T_ARG)
// 	{
// 		(*par)->args[++i] = malloc(sizeof(char) * (ft_strlen(lex->data) + 1));
// 		(*par)->args[i] = lex->data;
// 		lex = lex->next;
// 	}
// 	(*par)->args[++i] = NULL;
// 	return (lex);
// }

void	ft_parser(t_parser **parser, t_lexer *lex)
{
	// int	fd[2];
	// parser_new_cmd(parser, lex);
	// while (lex)
	// {
	// 	if (lex->type == T_REDIR_IN)
	// 		(*parser)->redir_in = parser_open(lex);
	// 	else if (lex->type == T_REDIR_OUT || lex->type == T_APPEND)
	// 		(*parser)->redir_out = parser_open(lex);
	// 	else if (lex->type == T_CMD)
	// 		(*parser)->cmd = lex->data;
	// 	// break ; //test
	// 	// else if (lex->type == T_ARG)
	// 	// lex = p_fill_arg(lex, parser);
	// 	// (*parser)->args = get_args(lex);
	// 	if (lex && lex->type == T_PIPE)
	// 	{
	// 		lex = lex->next;
	// 		pipe(fd);
	// 		(*parser)->redir_out = fd[STDOUT_FILENO];
	// 		parser_new_cmd(parser, lex);
	// 		(*parser)->redir_in = fd[STDIN_FILENO];
	// 	}
	// 	lex = lex->next;
	// }
	(void)parser;
	(void)lex;
	return ;
}
