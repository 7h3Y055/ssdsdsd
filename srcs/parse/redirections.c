#include "minishell.h"

void    add_back_io(t_io **head, t_io *new)
{
    t_io *tmp;

    if (!new)
        return ;
    if (!(*head))
    {
        *head = new;
        return ;
    }
    tmp = *head;
    while (tmp && tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = new;
}

char *remove_quotation(char *str)
{
    char *s;
    int     i;
    int     j;
    int     u = 0;
    char intquots;

    i = 0;
    s = malloc(sizeof(char) * 30);
    intquots = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            j = skip_quotes(str, &i)  - 1;
            while (j > 1)
            {
                s[u++] = str[i - j];
                j--;
            }
        }
        else
            while (str[i] && !(str[i] == '"' || str[i] == '\''))
                s[u++] = str[i++];
    }
    s[u] = 0;
    // free(str);
    return (s);
}

int skip_quotation(char *data, int index)
{
    int i;
    int sq;
    int dq;

    sq = 0;
    dq = 0;
    i = index;
    while (data[i] && isspace(data[i]))
        i++;
    if (data[i] == '"')
        dq++;
    else if (data[i] == '\'')
        sq++;
    else
        return (i);
    i++;
    while (data[i])
    {
        if (data[i] == '"' && dq)
            return (i + 0);
        else if (data[i] == '\'' && sq)
            return (i + 0);
        i++;
    }
    return (i);
}

char *get_file(char *data)
{
    char *file;
    int i;
    int tmp_i;
    int j;

    i = 0;
    j = 0;
    while (data[i] && isspace(data[i]))
        i++;
    tmp_i = i;
    while (data[i] && !isspace(data[i]))
    {
        j++;
        i = skip_quotation(data, i);
        if (data[i] == '<' || data[i] == '>')
            break;
        i++;
    }
    if (data[tmp_i] == '<' || data[tmp_i] == '>' || !j)
    {
        ft_print_error("here doc","syntax error!\n", 0);
        ptr.parse.tmp_flag = -1;
        exit (0);
    }
    file = strndup(&data[tmp_i], i - tmp_i);
    file = remove_quotation(file);
    // printf("[%s]\n", file);
    return (file);
}

t_io    *new_io_node(char *data, char type)
{
    t_io *new;

    new = malloc(sizeof(t_io));
    new->type = type;
    new->file = data;
    new->next = NULL;
}

char **fill_args(char **args)
{
    int i;
    int u;
    int len;
    char **data;

    i = 0;
    len = 1;
    while (args[i])
    {
        if (ft_strlen(args[i]) != 0);
            len++;
        i++;
    }
    data = malloc(sizeof(char *) * len);
    i = 0;
    u = 0;
    while (args[i])
    {
        if (ft_strlen(args[i]) != 0)
            data[u++] = ft_strdup(args[i]);
        i++;
    }
    data[u] = NULL;
    return (data);
}


t_cmd   *create_command(char *data)
{
    t_cmd   *cmd;
    char    **args;
    int i;

    args = ft_split_own(data);

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->in_red = fill_inred(args);
    cmd->out_red = fill_outred(args);
    cmd->args = fill_args(args);
    ptr.parse.tmp_flag = 0;
    return (cmd);
}