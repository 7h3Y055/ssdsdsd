#include "minishell.h"


void    execute_tree(t_aolist *tree);
void    execute_pipe(t_plist *head);
void    execute_command(t_cmd *cmd, int parent);


void    execution()
{
    while (ptr.parse.aolist)
    {
        if (ptr.parse.aolist->type == 'C')
            execute_command(ptr.parse.aolist->data, 1);
        else if (ptr.parse.aolist->type == 'P')
            execute_pipe(ptr.parse.aolist->data);
        else if (ptr.parse.aolist->type == 'T')
            execute_tree(ptr.parse.aolist->data);
		else if (ptr.parse.aolist->type == 'O')
        {
            if (ptr.pstatus == 0 && ft_strncmp(ptr.parse.aolist->data, "||", 2) == 0)
                return ;
            if (ptr.pstatus != 0 && ft_strncmp(ptr.parse.aolist->data, "&&", 2) == 0)
                return ;
        }
        ptr.parse.aolist = ptr.parse.aolist->next;
    }
}


void    execute(char **args, int parent)
{
    char *binary_path;

    // fprintf(stderr, "NONO\n");
    binary_path = get_final_path(args[0]);
    if (binary_path && access(binary_path, X_OK) != 0)
    {
        ptr.pstatus = ft_print_error(args[0], "Permission denied\n", 126);
        return ;
    }
    if (parent)
    {
        int pid = fork();
        if (pid == 0)
        {
            execve(binary_path, args, ptr.envp);
            exit(ptr.pstatus);
        }
        wait(&ptr.pstatus);
    }
    else
    {
        execve(binary_path, args, ptr.envp);
        exit(ptr.pstatus);
    }
}



void    execute_command(t_cmd *cmd, int parent)
{
    t_fdbackup  backup;

    if (!cmd->args)
        return ;

    fdbackup(&backup);
    apply_inredirections(cmd->in_red);
    apply_outredirections(cmd->out_red);
    handle_quots_value(cmd);
    if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        echo_handler(cmd->args);
    else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        cd_handler(cmd->args);
    else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
        {
			
		  }
    else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
        export_var(cmd->args);
    else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
        unset_var(cmd->args);
    else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
        printf_env();
    else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
        ft_exit(cmd->args);
    else
        execute(cmd->args, parent);
    default_io(backup);
}


//##################################################################################
//##################################################################################
//##################################################################################
//##################################################################################
//##################################################################################
//##################################################################################
//##################################################################################


void join_fd(int **fd_arr, int fd)
{
	int	i;
	int	j;
	int	*arr;
	
	i = 0;
	j = 0;
	while ((*fd_arr)[i] != -1337)
		i++;
	arr = (int*) malloc(sizeof(int) *(i + 2));
	while (j < i)
	{
		arr[j] = (*fd_arr)[j];
		j++;
	}
	arr[j++] = fd;
	arr[j] = -1337;
	free(*fd_arr);
	*fd_arr = arr;
}





void    execute_pipe_helper(t_plist *head, int in, int *np)
{
    int id;

    // // if (pp)
    // printf("%d:", in);
    // // else
    //     // printf("0:");
    // if (np)
    //     printf(":%d\n", np[1]);
    // else
    //     printf(":1\n");

    id = fork();
    if (id == 0)
    {
        if (in != 0)
        {
            // close(pp[1]);
            dup2(in, 0);
            close(in);
        }
        if (np[1] != 1)
        {
            close(np[0]); 
            dup2(np[1], 1);
            close(np[1]);
        }
        if (head->type == 'T')
            execute_tree(head->data);
        else if (head->type == 'C')
            execute_command(head->data, 0);
        else if (head->type == 'P')
            execute_pipe(head->data);
        exit(ptr.pstatus);
    }
    if (np)
    {
        close(np[1]);
        join_fd(&ptr.arr, np[0]);
    }
}

void	close_fd(int *fd_arr)
{
	int i;

	i = 0;
	while (fd_arr[i] != -1337)
	{
		if (fd_arr[i] != 0  && fd_arr[i] != 1 && fd_arr[i] != 2)
			close(fd_arr[i]);
		i++;	
	}
}

void    execute_pipe(t_plist *head)
{
    t_fdbackup  backup;
    int *next_pipe;
    // int *prev_pipe;
    int in;
    
    fdbackup(&backup);


    ptr.arr = malloc(sizeof(int) * 1);
    ptr.arr[0] = -1337;
    
    next_pipe = malloc(sizeof(int) * 2);
    // prev_pipe = NULL;

    in = 0;
    while (head)
    {
        if (head->next)
        {
            pipe(next_pipe);
            // printf("%d==%d\n", next_pipe[0], next_pipe[1]);
        }
        else
        {
            next_pipe[1] = 1;
        }
        execute_pipe_helper(head, in, next_pipe);
        in = next_pipe[0];
        // prev_pipe = next_pipe;
        head = head->next;
    }
    close_fd(ptr.arr);
    while (wait(NULL) != -1);
    default_io(backup);
}








// void    execute_pipe(t_plist *head)
// {
//     int fd[2];
//     int read_prev_end;
    
//     ptr.arr = malloc(sizeof(int) * 1);
//     ptr.arr[0] = -1337;
    
//     int in;
//     t_fdbackup  backup;


//     fdbackup(&backup);
//     read_prev_end = 0;
//     in = 0;
//     while (head)
//     {
//         if (head->next)
//             pipe(fd);
//         else
//             fd[1] = 1;
//         execute_pipe_helper(head, in, fd, read_prev_end);
//         in = fd[0];
//         head = head->next;
//         read_prev_end = fd[0];
//     }
//     close_fd(ptr.arr);
//     // int i = 0;
//     // while(ptr.arr[i] != -1337)
//     // printf("%d\n", ptr.arr[0]);
//     while (wait(&ptr.pstatus) != -1);
//     default_io(backup);
// }

void    execute_tree(t_aolist *tree)
{
	int id = fork();
	if (id == 0)
	{
		while (tree)
		{
			if (tree->type == 'C')
					execute_command(tree->data, 1);
			else if (tree->type == 'P')
					execute_pipe(tree->data);
			else if (tree->type == 'T')
					execute_tree(tree->data);
			else if (tree->type == 'O')
			{
					if (ptr.pstatus == 0 && ft_strncmp(tree->data, "||", 2) == 0)
						return ;
					if (ptr.pstatus != 0 && ft_strncmp(tree->data, "&&", 2) == 0)
						return ;
			}
			tree = tree->next;
		}
		exit(0);
	}
	wait(&ptr.pstatus);
}

