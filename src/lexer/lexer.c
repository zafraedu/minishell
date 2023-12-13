#include "minishell.h"

static int	check_syntaxis(t_lexer *node, int *exit_status);
static void	lexer_cmd(t_lexer *node);

void	ft_lexer(char *input, t_lexer **lexer, int *exit_status)
{
	int	i;
	int	type;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		type = get_type(input, i);
		if (type != T_GENERAL)
			treat_special(input, lexer, &i, type);
		else if (input[i] == 34 || input[i] == 39)
		{
			if (!treat_quotes(input, lexer, &i, exit_status))
				break ;
		}
		else
			treat_general(input, lexer, &i);
	}
	if (!check_syntaxis(*lexer, exit_status))
	{
		ft_free_tokenlist(lexer);
		return ;
	}
	lexer_cmd(*lexer);
}

// checkear que el prompt no haya errores de syntaxis
static int	check_syntaxis(t_lexer *node, int *exit_status)
{
	if (!node)
		return (0);
	if (node->type == T_PIPE)
	{
		printf("minishell: syntax error\n");
		*exit_status = 2;
		return (0);
	}
	while (node->next)
	{
		if (node->type == T_REDIR_OUT || node->type == T_APPEND || node->type == T_REDIR_IN || node->type == T_HEREDOC)
		{
			if (node->next->type != T_GENERAL)
			{
				printf("minishell: syntax error near unexpected token %s\n", node->next->data);
				*exit_status = 2;
				return (0);
			}
		}
		node = node->next;
	}
	return (1);
}

static void	lexer_cmd(t_lexer *node)
{
	if (node->type == T_GENERAL)
		node->type = T_CMD;
	while (node->next)
	{
		if (node->type == T_REDIR_IN && node->next->type == T_GENERAL)
			node->next->type = T_INFILE;
		else if (node->type == T_HEREDOC && node->next->type == T_GENERAL)
			node->next->type = T_LIMITER;
		else if (node->type == T_LIMITER && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		else if (node->type == T_INFILE && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		else if (node->type == T_CMD && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		else if (node->type == T_PIPE && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		else if ((node->type == T_REDIR_OUT || node->type == T_APPEND) \
				&& node->next->type == T_GENERAL)
			node->next->type = T_OUTFILE;
		else if (node->type == T_OUTFILE && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		node = node->next;
	}
}
