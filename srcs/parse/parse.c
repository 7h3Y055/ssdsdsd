#include "minishell.h"

void    parse()
{
    ptr.parse.row_data = readline("% ");
    if (!ptr.parse.row_data || !ft_strlen(ptr.parse.row_data))
        return ;
    add_history(ptr.parse.row_data);
    if (check_syntax_validity(ptr.parse.row_data))
    {
        printf("Syntax Error!\n");
        return ;
    }
    ptr.parse.data = split_and_or(ptr.parse.row_data);
    create_aolist();


    // while (ptr.parse.aolist)
    // {
    //     printf("%s\n", (char *)ptr.parse.aolist->data);
    //     ptr.parse.aolist = ptr.parse.aolist->next;
    // }
    // printf("DONE\n");
}