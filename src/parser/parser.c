#include "minishell.h"

void ft_index(t_lexer *lex)
{
    t_lexer *tmp;
    int i;

    tmp = lex;
    i = 0;
    while (tmp)
    {
        tmp->index = i;
        tmp = tmp->next;
        i++;
    }
}

int ft_count_pipes(t_lexer *lex)
{
    t_lexer *tmp;
    int i;

    tmp = lex;
    i = 0;
    while (tmp)
    {
        if (tmp->type == T_PIPE)
            i++;
        tmp = tmp->next;
    }
    return i;
}

int  get_last(t_lexer *lex, int start)
{
    t_lexer *tmp;
	int		last_index;

	last_index = -1;
    tmp = lex;
    while (tmp && tmp->next)
    {
        if (tmp->type == T_PIPE && tmp->index > start)
            return (tmp->index - 1);
        tmp = tmp->next;
    }
	last_index = tmp->index;
    return (last_index);
}

void ft_redirect(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = -1;
	if (tmp->type == T_REDIR_IN)
    {
		fd = open(tmp->next->data, O_RDONLY);
		(*cmd_node)->redir_in = fd;
    }
    else if (tmp->type == T_REDIR_OUT)
    {
        fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*cmd_node)->redir_out = fd;
    }
    else if (tmp->type == T_APPEND)
    {
        fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		(*cmd_node)->redir_out = fd;
    }
/* 	else if (tmp->type == T_HEREDOC)
		(*cmd_node)->heredoc = ft_strdup(tmp->next->data); */
}

static void fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int *end)
{
    t_lexer *tmp;
    int aux;

    tmp = lex;
    while (tmp && tmp->index != *start)
        tmp = tmp->next;
    aux = *start;
    while (tmp && aux <= *end)
    {
        if (tmp->type >= 4 && tmp->type <= 10) 
        {
            if (tmp->index == *start) 
            {
                ft_redirect(tmp, cmd_node);
                *start += 2;
            } 
            else if (tmp->index == *end - 1) 
            {
                ft_redirect(tmp, cmd_node);
                *end -= 2;
            }
        }
        tmp = tmp->next;
        aux++;
    }
}

static void fill_cmd_args(t_lexer *tmp, t_parser **cmd_node, int start, int end)
{
    int i;

    i = -1;
    while (tmp && start <= end)
    {
        if (tmp->type == T_PIPE)
        {
            tmp = tmp->next;
            start++;
        }
        if ((*cmd_node)->cmd == NULL) // El type T_CMD no se esta actualizando correctamente cuando hay un a redireccion al principio
            (*cmd_node)->cmd = ft_strdup(tmp->data);
        else // El type T_ARG no se esta actualizando correctamente cuando hay un a redireccion al principio
        {
            if (++i < MAX_ARGUMENTS)
                (*cmd_node)->args[i] = ft_strdup(tmp->data);
            else
            {
                printf("Error: too many args\n");
                break;
            }
        }
        tmp = tmp->next;
        start++;
    }
}

void ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start, int end)
{
    t_lexer *tmp;

    tmp = lex;
    while (tmp && tmp->index != start)
        tmp = tmp->next;
    fill_redir(lex, cmd_node, &start, &end);
    while (tmp && tmp->index != start)
        tmp = tmp->next;
    (*cmd_node)->args = ft_calloc(MAX_ARGUMENTS, sizeof(char *));
    if ((*cmd_node)->args)
        fill_cmd_args(tmp, cmd_node, start, end);
}


void    ft_add_nodes(t_parser **cmd_node, t_lexer *lex)
{
    int start;
    int num_pipes;
    int i;
    int end;

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
    t_parser *tmp2 = *parser;
    while(tmp2)
    {
        printf("\n");
        printf("command: %s\n", tmp2->cmd);
        for (int i = 0; tmp2->args[i] != NULL; i++)
            printf("argument: %s\n", tmp2->args[i]);
        if (tmp2->redir_in)
            printf("file_input: %i\n", tmp2->redir_in);
        if (tmp2->redir_out)
            printf("file_output: %i\n", tmp2->redir_out);
/*         if (tmp2->heredoc)
            printf("heredoc, limiter: %s\n", tmp2->heredoc); */
        tmp2 = tmp2->next;
    }

}

void	ft_free_parserlist(t_parser **parser)
{
	t_parser *tmp;
    int i;

	while (*parser)
	{
		tmp = (*parser)->next;
		free((*parser)->cmd);
        i = 0;
        while ((*parser)->args[i])
        {
            free((*parser)->args[i]);
            i++;
        }
        free((*parser)->args);
/*         free((*parser)->heredoc); */
		free(*parser);
		*parser = tmp;
	}
	*parser = NULL;
}