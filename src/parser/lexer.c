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

void	ft_lexer(char *input, t_token **token_list)
{
	int		i;
	int		type;
	t_token	*current_token;

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
	current_token = *token_list;
	while (current_token)
	{
		printf("data: %s\n", current_token->data);
		printf("type: %i\n\n", current_token->type);
		current_token = current_token->next;
	}
	return ;
}

// Funcion para liberar la lista de tokens
void	ft_free_tokenlist(t_token **token_list)
{
	t_token	*tmp;

	while (*token_list)
	{
		tmp = (*token_list)->next;
		free((*token_list)->data);
		free(*token_list);
		*token_list = tmp;
	}
	*token_list = NULL;
}
