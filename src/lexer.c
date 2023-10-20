#include "../inc/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

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

void	ft_add_token(t_token **token_list, char *input, int i, int size, int type)
{
	t_token	*new;
	t_token	*current;

	new = ft_calloc(1, sizeof(t_token));

	new->type = type;
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

void treat_special(char *input, t_token **token_list, int *i, int type)
{
    if (type == T_GREAT_GREAT || type == T_LESS_LESS)
    {
        ft_add_token(token_list, input, *i, 2, type);
        (*i)++;
    }
    else
        ft_add_token(token_list, input, *i, 1, type);
    (*i)++;
}

int	treat_quotes(char *input, t_token **token_list, int *i, int *j)
{
    char quote_char = input[*i];
    (*j) = (*i) + 1;
    while (input[(*j)] && input[(*j)] != quote_char)
        (*j)++;
    if (input[(*j)] == quote_char)
    {
        ft_add_token(token_list, input, (*i), (*j) - (*i) + 1, T_GENERAL);
        (*i) = (*j) + 1;
		return (1);
    }
    else // Esto sería un error de sintaxis (falta cerrar comillas)
    {
        ft_add_token(token_list, input, (*i), (*j) - (*i) + 1, T_GENERAL);
		return (0);
    }
}

void treat_general(char *input, t_token **token_list, int *i, int *j)
{
    (*j) = (*i);
    while (input[(*j)] && !is_space(input[(*j)]) && is_special(input, (*j)) == T_GENERAL)
        (*j)++;
    ft_add_token(token_list, input, (*i), (*j) - (*i), T_GENERAL);
    (*i) = (*j);
}

void    ft_lexer(char *input, t_token **token_list)
{
	int		i;	
	int		j;
	int		type;

    if (!ft_strlen(input))
	{
        return ;
	}

	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))  //Tratar espacios
			i++;
		else
		{
			type = is_special(input, i);
			if (type != T_GENERAL) //Tratar caracteres especiales (pipe, redir, etc)
                treat_special(input, token_list, &i, type);
	  		else if (input[i] == '\'' || input[i] == '\"') // Tratar comillas
			{
                if (!treat_quotes(input, token_list, &i, &j))
					break ;
			}
            else  // Tratar otros caracteres
                treat_general(input, token_list, &i, &j);
		}
	}

	// Imprimir tokens (test)
    t_token *current_token = *token_list;

    while (current_token)
    {
        printf("%s\n", current_token->data);
        current_token = current_token->next;
    }
    return ;
}

//Funcion para liberar la lista de tokens, todavía sin implementar
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
}