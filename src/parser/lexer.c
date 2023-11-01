#include "minishell.h"

static int	check_syntaxis(t_lexer *node);
static void	lexer_cmd(t_lexer *node);

void	ft_lexer(char *input, t_lexer **lexer)
{
	int	i;
	int	type;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i])) // Tratar espacios
			i++;
		type = get_type(input, i);
		if (type != T_GENERAL) // Tratar caracteres especiales
			treat_special(input, lexer, &i, type);
		else if (input[i] == 34 || input[i] == 39) // Tratar comillas
		{
			if (!treat_quotes(input, lexer, &i))
				break ;
		}
		else // Tratar otros caracteres
			treat_general(input, lexer, &i);
	}
	if (!check_syntaxis(*lexer))
		return ;
	lexer_cmd(*lexer);
}

// checkear que el prompt no haya errores de syntaxis
static int	check_syntaxis(t_lexer *node)
{
	if (!node)
		return (1);
	if (node->type == T_PIPE)
		return (printf("error syntex\n"), 0);
	while (node->next)
	{
		if (node->type == T_REDIR_OUT && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		if (node->type == T_REDIR_IN && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		if (node->type == T_APPEND && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		if (node->type == T_HEREDOC && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		node = node->next;
	}
	return (1);
}

// separar comando y argumentos
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
		else if (node->type == T_INFILE && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		else if ((node->type == T_CMD || node->type == T_ARG)
				&& node->next->type == T_GENERAL)
			node->next->type = T_ARG;
		else if (node->type == T_PIPE && node->next->type == T_GENERAL)
			node->next->type = T_CMD;
		else if ((node->type == T_REDIR_OUT || node->type == T_APPEND)
				&& node->next->type == T_GENERAL)
			node->next->type = T_OUTFILE;
		node = node->next;
	}
}

// Funcion para liberar la lista de tokens
void	ft_free_tokenlist(t_lexer **lexer) //no va aqui
{
	t_lexer *tmp;

	while (*lexer)
	{
		tmp = (*lexer)->next;
		free((*lexer)->data);
		free(*lexer);
		*lexer = tmp;
	}
	*lexer = NULL;
}
