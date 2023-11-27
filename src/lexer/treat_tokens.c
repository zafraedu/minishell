#include "minishell.h"

void	treat_special(char *input, t_lexer **lexer, int *i, int type)
{
	if (type == T_APPEND || type == T_HEREDOC)
	{
		ft_add_token(lexer, input, *i, 2);
		lexer_add_type(lexer, type);
		(*i)++;
	}
	else
	{
		ft_add_token(lexer, input, *i, 1);
		lexer_add_type(lexer, type);
	}
	(*i)++;
}

int	treat_quotes(char *input, t_lexer **lexer, int *i)
{
	char	quote_char;
	int		j;

	quote_char = input[*i];
	j = (*i) + 1;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
	{
		ft_add_token(lexer, input, (*i), j - (*i) + 1);
		lexer_add_type(lexer, T_GENERAL);
		(*i) = j + 1;
		return (1);
	}
	else // Esto sería un error de sintaxis (falta cerrar comillas)
	{
		ft_add_token(lexer, input, (*i), j - (*i) + 1);
		lexer_add_type(lexer, T_GENERAL);
		printf("error comillas\n"); //test
		return (0);
	}
}

void	treat_general(char *input, t_lexer **lexer, int *i)
{
	int	j;
	int quote_char;

	j = (*i);
	while (input[j] && !ft_isspace(input[j]) && get_type(input, j) == T_GENERAL)
	{
		if (input[j] == 34 || input[j] == 39)
		{
			quote_char = input[j];
			j++;
			while (input[j] && input[j] != quote_char)
				j++;
		}
		j++;
	}
	ft_add_token(lexer, input, (*i), j - (*i));
	lexer_add_type(lexer, T_GENERAL);
	(*i) = j;
}
