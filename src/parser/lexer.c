#include "minishell.h"

int	is_special(char *str, int i)
{
	if (str[i] == '|')
		return (T_PIPE);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (T_GREAT_GREAT);
		return (T_GREAT);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (T_LESS_LESS);
		return (T_LESS);
	}
	return (T_GENERAL);
}

void	ft_lexer(char *input, t_lexer **token_list)
{
	int	i;
	int	type;

	t_lexer *current_lexer; //solo sirve para inprimir
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i])) // Tratar espacios
			i++;
		else
		{
			type = is_special(input, i);
			if (type != T_GENERAL) // Tratar caracteres especiales
				treat_special(input, token_list, &i, type);
			else if (input[i] == '\'' || input[i] == '\"') // Tratar comillas
			{
				if (!treat_quotes(input, token_list, &i))
					break ;
			}
			else // Tratar otros caracteres
				treat_general(input, token_list, &i);
		}
	}
	// Imprimir tokens (test)
	current_lexer = *token_list;
	i = 0;
	while (current_lexer)
	{
		printf("data: %s\n", current_lexer->data);
		printf("type: %i\n", current_lexer->type);
		printf("node: %i\n\n", i++);
		current_lexer = current_lexer->next;
	}
	return ;
}

int	check_syntaxis(t_lexer *node) //error de sintaxis visual ;)
{
	if (node->type == T_PIPE)
		return (printf("error syntax\n"), 0);
	while (node->next)
	{
		if (node->type == T_GREAT && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		if (node->type == T_LESS && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		if (node->type == T_GREAT_GREAT && node->next->type != T_GENERAL)
			return (printf("error syntax\n"), 0);
		if (node->type == T_LESS_LESS && node->next->type != T_GENERAL)
			if (node->type == T_PIPE && node->next->type != T_GENERAL)
				return (printf("error syntax\n"), 0);
		node = node->next;
	}
	return (1);
}

// Funcion para liberar la lista de tokens
void	ft_free_tokenlist(t_lexer **token_list)
{
	t_lexer	*tmp;

	while (*token_list)
	{
		tmp = (*token_list)->next;
		free((*token_list)->data);
		free(*token_list);
		*token_list = tmp;
	}
	*token_list = NULL;
}
