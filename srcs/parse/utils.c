#include "minishell.h"


int is_operator(char *data, int index)
{
    int i;
    int dq = 0;
    int sq = 0;
    int pr = 0;

    i = -1;
    while (data[++i] && i < index)
    {
        if (data[i] == '"' && dq == 0)
            dq++;
        else if (data[i] == '"' && dq)
            dq--;
        if (data[i] == '\'' && sq == 0)
            sq++;
        else if (data[i] == '\'' && sq)
            sq--;
        if (data[i] == '(')
            pr++;
        else if (data[i] == ')')
            pr--;
    }
    if (sq == 0 && dq == 0 && pr == 0)
        return (1);
    return (0);
}

char **split_and_or(char *row_data)
{
    char **data;

    data = malloc(sizeof(char *) * split_and_or_len(row_data));

    int i;
    int u = 0;
    int j = 0;

    i = -1;
    while (row_data[++i])
    {
        if (ft_strncmp("&&", &row_data[i], 2) == 0 && is_operator(row_data, i))
        {
            data[u++] = ft_strdup("&&");
            i++;
        }
        else if (ft_strncmp("||", &row_data[i], 2) == 0 && is_operator(row_data, i))
        {
            data[u++] = ft_strdup("||");
            i++;
        }
        else
            data[u++] = get_split_line(&row_data[i], &i);
    }
    data[u] = NULL;
    return (data);
}
char *get_split_line(char *row_data, int *index)
{
    int i;
    int j = 0;
    char *split;

    split = malloc(sizeof(char) * split_line_len(row_data));
    (*index)--;
    i = -1;
    while (row_data[++i])
    {
        if ((ft_strncmp(&row_data[i], "&&", 2) == 0 || ft_strncmp(&row_data[i], "||", 2) == 0) && is_operator(row_data, i))
            break;
        else
            split[j++] = row_data[i];
        (*index)++;
    }
    split[j] = 0;
    return (split);
}

int split_line_len(char *row_data)
{
    int i;

    i = -1;
    while (row_data[++i])
        if ((ft_strncmp(&row_data[i], "&&", 2) == 0 || ft_strncmp(&row_data[i], "||", 2) == 0) && is_operator(row_data, i))
            break;
    return (i + 1);
}

int     split_and_or_len( char *row_data)
{
    int i;
    int len;
    int dq = 0;
    int sq = 0;
    int pr = 0;

    len = 1;
    i = -1;
    while (row_data[++i])
    {
        if ((ft_strncmp(&row_data[i], "&&", 2) == 0 || ft_strncmp(&row_data[i], "||", 2) == 0) && is_operator(row_data, i))
        {
            len += 2;
            i++;
        }
    }
    return (len + 1);
}

int     check_input(char *row_data)
{
    return (0);
}

t_aolist    *last_node_aolist(t_aolist *head)
{
    t_aolist *tmp;

    tmp = head;
    while (tmp && tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void    create_aolist()
{
    t_aolist *head;
    t_aolist *node;
    t_aolist *last;
    
    int i;
    
    i = 0;
    head = NULL;
    while (ptr.parse.data[i])
    {
        last = last_node_aolist(head);
        node = new_node_aolist(ptr.parse.data[i], last);
        if (!head)
            head = node;    
        else
            last->next = node;
        i++;
    }
    ptr.parse.aolist = head;
}
