#include "minishell.h"

void	add_type(t_token **token_list, int type)
{
	t_token	*current;

	current = *token_list;
	while (current->next != NULL)
		current = current->next;
	current->type = type;
}

void	ft_add_token(t_token **token_list, char *input, int i, int size)
{
	t_token	*new;
	t_token	*current;

	new = ft_calloc(1, sizeof(t_token));
	new->data = ft_substr(input, i, size);
	new->next = NULL;
	if (*token_list == NULL)
		*token_list = new;
	else
	{
		current = *token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	treat_special(char *input, t_token **token_list, int *i, int type)
{
	if (type == T_GREAT_GREAT || type == T_LESS_LESS)
	{
		ft_add_token(token_list, input, *i, 2);
		add_type(token_list, type);
		(*i)++;
	}
	else
	{
		ft_add_token(token_list, input, *i, 1);
		add_type(token_list, type);
	}
	(*i)++;
}

int	treat_quotes(char *input, t_token **token_list, int *i)
{
	char	quote_char;
	int		j;

	quote_char = input[*i];
	j = (*i) + 1;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
	{
		ft_add_token(token_list, input, (*i), j - (*i) + 1);
		add_type(token_list, T_GENERAL);
		(*i) = j + 1;
		return (1);
	}
	else // Esto sería un error de sintaxis (falta cerrar comillas)
	{
		ft_add_token(token_list, input, (*i), j - (*i) + 1);
		add_type(token_list, T_GENERAL);
		printf("error comillas\n"); //test
		return (0);
	}
}

void	treat_general(char *input, t_token **token_list, int *i)
{
	int	j;

	j = (*i);
	while (input[j] && !ft_isspace(input[j]) && is_special(input,
			j) == T_GENERAL)
		j++;
	ft_add_token(token_list, input, (*i), j - (*i));
	add_type(token_list, T_GENERAL);
	(*i) = j;
}
