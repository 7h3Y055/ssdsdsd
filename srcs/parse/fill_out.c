#include "minishell.h"

t_io    *ft_out_file_appand(char *file)
{
    t_io    *new;

    new = new_io_node(NULL, 'A');
    new->fd = -1;
    new->next = NULL;
    file = ft_strdup(file);
    new->file = remove_quotation(file);
    return (new);
}

t_io    *ft_out_file(char *file)
{
    t_io    *new;

    new = new_io_node(NULL, 'O');
    new->fd = -1;
    new->next = NULL;
    file = ft_strdup(file);
    new->file = remove_quotation(file);
    return (new);
}

t_io    *fill_outred(char **args)
{
    t_io    *head;
    t_io    *new;
    int     i;

    head = NULL;
    i = 0;
    while (args[i])
    {
        if (ptr.parse.tmp_flag == -1)
            return (NULL);
        if (ft_strncmp(args[i], ">>", 3) == 0)
        {
            new = ft_out_file_appand(args[i + 1]);
            args[i][0] = 0;
            args[i + 1][0] = 0;
            add_back_io(&head, new);
        }
        else if (ft_strncmp(args[i], ">", 2) == 0)
        {
            new = ft_out_file(args[i + 1]);
            args[i][0] = 0;
            args[i + 1][0] = 0;
            add_back_io(&head, new);
        }
        i++;
    }
    return (head);
}






