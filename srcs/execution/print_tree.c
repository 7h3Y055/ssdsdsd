#include "minishell.h"



void    print_command(t_cmd *tmp)
{
    char **args;
    int i;
    t_io *io;

    printf("###CMD###\n");
    printf("IN: \n");
    io = tmp->in_red;
    while (io)
    {
        printf("\t%c:%s\n", io->type, io->file);
        io = io->next;
    }
    printf("ARGS: \n");
    i = 0;
    args = tmp->args;
    while (args && args[i])
    {
        printf("\t%s\n", args[i]);
        i++;
    }
    printf("OUT: \n");
    io = tmp->out_red;
    while (io)
    {
        printf("\t%c:%s\n", io->type, io->file);
        io = io->next;
    }
    printf("###CMD###\n");
}

void    print_pipe(t_plist *head)
{
    printf("\n------------ PIPE OPEN ------------\n");
    while (head)
    {
        if (head->type == 'T')
            print_tree(head->data);
        else if (head->type == 'C')
            print_command(head->data);
        else if (head->type == 'O')
            printf("O:%s", head->data);
        else if (head->type == 'P')
            print_pipe(head->data);
        head = head->next;
    }
    printf("------------ PIPE CLOSE -----------\n\n");
}

void    print_all()
{
    t_plist *head;
    t_cmd *tmp;
    int     i = 0;

    while (ptr.parse.aolist)
    {
        if (ptr.parse.aolist->type == 'C')
            print_command(ptr.parse.aolist->data);
        else if (ptr.parse.aolist->type == 'P')
            print_pipe(ptr.parse.aolist->data);
        else if (ptr.parse.aolist->type == 'O')
            printf("O:%s\n", (char *)ptr.parse.aolist->data);
        else if (ptr.parse.aolist->type == 'T')
            print_tree(ptr.parse.aolist->data);
        else
            printf("ERROR !!!! \n");
        ptr.parse.aolist = ptr.parse.aolist->next;
    }
}

void    print_tree(t_aolist *tree)
{
    t_plist *head;

    printf("\n------------ TREE OPEN ------------\n");
    while (tree)
    {
        if (tree->type == 'C')
            print_command(tree->data);
        else if (tree->type == 'P')
            print_pipe(tree->data);
        else if (tree->type == 'O')
            printf("O:%s\n", (char *)tree->data);
        else if (tree->type == 'T')
            print_tree(tree->data);
        tree = tree->next;
    }
    printf("------------ TREE CLOSE -----------\n\n");
}
