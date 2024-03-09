#include "minishell.h"

int ft_print_error(char *str, char *error, int n)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    write(2, "minishell: ", 11);
    write(2, str, i);
    write(2, ": ", 2);
    write(2, error, ft_strlen(error));
    return (n);
}

char *file_content(char *path)
{
    int fd;
    char *buffer = ft_strdup("");
    char *tmp;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        ptr.parse.tmp_flag = ft_print_error(path, " : No such file or directory\n", 1);
        
        return (NULL);
    }
    while (1)
    {
        tmp = get_next_line_G(fd);
        if (!tmp)
            break;
        buffer = ft_strjoin(buffer, tmp);
    }
    free(path);
    return (buffer);
}

void    apply_inredirections(t_io *io)
{
    int pipefd[2];
    char *buffer;

    while (io)
    {
        if (ptr.parse.tmp_flag)
            return ;

        if (io->type == 'R')
            io->file = file_content(io->file);

        pipe(pipefd);
        dup2(pipefd[0], 0);
        write(pipefd[1], io->file, ft_strlen(io->file));
        close(pipefd[1]);
        io = io->next;
    }
}

void    apply_outredirections(t_io *io)
{
    while (io)
    {
        if (ptr.parse.tmp_flag)
            return ;

        if (io->type == 'O')
            io->fd = open(io->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else if (io->type == 'A')
            io->fd = open(io->file, O_WRONLY | O_APPEND, 0644);
        if (io->fd == -1)
        {
            ptr.parse.tmp_flag = ft_print_error(io->file, " : No such file or directory\n", 1);
            return ;
        }
        dup2(io->fd, 1);
        io = io->next;
    }
}


void    default_io(t_fdbackup backup)
{
    dup2(backup.in, 0);
    dup2(backup.out, 1);
}

void    fdbackup(t_fdbackup *backup)
{
    backup->in = dup(0);
    backup->out = dup(1);
}







// void    execute_pipe(t_plist *head, int in, int out)
// {
//     int fd[2];
//     int a;
//     int b;
//     // t_fdbackup  backup;

//     in = 0;
//     // fdbackup(&backup);
//     while (head)
//     {
//         // if (head->next)
//         //     pipe(fd);
//         // else
//         //     fd[1] = 1;
//         // head->pid = fork();
//         // if (head->pid == 0)
//         // {
//             // close(fd[0]);
//         if (head->type == 'T')
//             execute_tree(head->data, 0, 1);
//         else if (head->type == 'C')
//             execute_command(head->data, in, fd[1]);
//         else if (head->type == 'P')
//             execute_pipe(head->data, 0, 1);
//         //     exit(0);
//         // }
//         // else
//         // {
//         //     close(fd[1]);
//         // }
//         // in = fd[0];
//         head = head->next;
//     }
//     // while (wait(NULL) != -1);
//     // close(fd[0]);
//     // default_io(backup);
// }



