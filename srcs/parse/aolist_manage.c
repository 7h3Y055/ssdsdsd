#include "minishell.h"

int is_a_pipe(char *data)
{
    int i;

    i = 0;
    while (data[i])
    {
        if (data[i] == '|' && data[i + 1] != '|')
            if (is_operator(data, i))
                return (1);
        i++;
    }
    return (0);
}

int is_a_parenthesis(char *data)
{
    int i;

    i = 0;
    while (data[i] && isspace(data[i]))
        i++;
    if (data[i] == '(')
        return (1);
    return (0);
}

char get_type(char *data)
{
    int i;

    i = 0;
    while (data[i] && isspace(data[i]))
        i++;
    if (ft_strncmp("&&", &data[i], 2) == 0 || ft_strncmp("||", &data[i], 2) == 0)
        return ('O');
    else if (is_a_pipe(&data[i]))
        return ('P');
    else if (is_a_parenthesis(&data[i]))
        return ('T');
    else
        return ('C');
}


int pipe_line_len(char *data)
{
    int i;

    i = 0;
    while (data[i])
    {
        if (data[i] == '|' && is_operator(data, i))
            break;
        i++;
    }
    return (i + 1);
}


char *get_pipe_line(char *data, int *index)
{
    char *line;
    int i;
    int tmp;

    tmp = *index;
    i = 0;
    line = malloc(sizeof(char) * pipe_line_len(data));
    *index += pipe_line_len(data) - 1;
    while (data[i])
    {

        if (data[i] == '|' && is_operator(data, i))
            break;
        else
            line[i] = data[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

void    add_back(t_plist **head, t_plist *new)
{
    t_plist *tmp;

    if (!*head)
    {
        *head = new;
        return ;
    }
    tmp = *head;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = new;
}

t_plist *create_plist(char *data)
{
    int i;
    t_plist *head;
    t_plist *new;

    i = 0;
    head = NULL;
    while (i < ft_strlen(data))
    {
        new = new_node_plist(get_pipe_line(&data[i], &i));
        add_back(&head, new);
        i++;
    }
    return (head);
}


t_plist *new_node_plist(char *data)
{
    t_plist *new;

    new = malloc(sizeof(t_plist));
    new->type = get_type(data);
    if (new->type == 'P')
        new->data = create_plist(data);
    else if (new->type == 'T')
        new->data = create_tree(data);
    else if (new->type == 'C')
        new->data = create_command(data);
    else
        new->data = strdup(data);
    new->next = NULL;
    return (new);
}

int     close_pair(char *str, int i)
{
        int     open;
        int     close;

        open = 0;
        close = 0;
        while (str && str[i])
        {
                if (str[i] == '(')
                        open++;
                else if (str[i] == ')')
                        close++;
                if (open == close)
                        return (i);
                i++;
        }
        return (-1);
}

char *remove_parenthesis(char *row_data)
{
    char *data;
    int i;

    i = 0;
    while (row_data[i] && isspace(row_data[i]))
        i++;
    data = strndup(&row_data[i + 1], close_pair(row_data, i) - i - 1);
    free(row_data);
    return (data);
}

t_aolist *create_tree(char *row_data)
{
    t_aolist *head;
    t_aolist *node;
    t_aolist *last;
    char **data;
    int i;

    i = 0;
    head = NULL;
    row_data = remove_parenthesis(row_data);
    data = split_and_or(row_data);
    while (data[i])
    {
        last = last_node_aolist(head);
        node = new_node_aolist(data[i], last);
        if (!head)
            head = node;    
        else
            last->next = node;
        i++;
    }
    return (head);
}

// char *get_limiter(char *data)
// {
//     char *limiter;
//     int i;
//     int tmp_i;
//     int j;

//     i = 0;
//     j = 0;
//     while (data[i] && isspace(data[i]))
//         i++;
//     tmp_i = i;
//         while (data[i] && !isspace(data[i]))
//     {
//         if (data[i] == '<' || data[i] == '>')
//             break;
//         j++;
//         i++;
//     }
//     if (data[tmp_i] == '<' || data[tmp_i] == '>' || !j)
//     {
//         ft_print_error("here doc syntax error!\n", 0);
//         ptr.parse.tmp_flag = -1;
//         return (NULL);
//     }
//     limiter = strndup(&data[tmp_i], j);
//     ft_strlcat(limiter, "\n", ft_strlen(limiter) + 2);
//     return (limiter);
// }

// char	*read_heredoc(char *limiter)
// {
// 	char	*tmp;
// 	char	*buffer;
// 	char	*new_buffer;

// 	write(1, ">", 1);
// 	buffer = NULL;
// 	tmp = get_next_line_G(0);
// 	while (tmp != NULL)
// 	{
//         // printf("|%s|\n", limiter);
// 		if (ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1) == 0)
// 		{
// 			free(tmp);
// 			break ;
// 		}
// 		new_buffer = ft_strjoin_G(buffer, tmp);
// 		free(buffer);
// 		buffer = new_buffer;
// 		free(tmp);
// 		write(1, ">", 1);
// 		tmp = get_next_line_G(0);
// 	}
// 	get_next_line_G(INT_MAX);
//     free(limiter);
// 	return (buffer);
// }

// t_io    *new_io_node(char *data)
// {
//     t_io *new;

//     new = malloc(sizeof(t_io));
//     new->type = 'H';
//     new->file = data;
//     new->next = NULL;
// }

// t_io    *fill_heredoc(char *data)
// {
//     int i;
//     t_io    *head;

//     head = new_io_node(NULL);
//     i = 0;
//     while (data[i])
//     {
//         if (ptr.parse.tmp_flag == -1)
//             return (NULL);
//         if (strncmp("<<", &data[i], 2) == 0 && is_operator(data, 0) && is_operator(data, 1))
//         {
//             i += 2;
//             free(head->file);
//             head->file = read_heredoc(get_limiter(&data[i]));
//         }
//         i++;
//     }
//     head->next = NULL;
//     head->fd = -1;
//     return (head);
// }

// char *get_file_name(char *data)
// {
//     char *path;
//     int i;
//     int tmp_i;
//     int j;

//     i = 0;
//     while (data[i] && isspace(data[i]))
//         i++;
//     tmp_i = i;
//     while (data[i] && !isspace(data[i]))
//     {

//         i++;
//     }

//     return (path);
// }

// t_io    *fill_inred(char *data)
// {
//     t_io    *head;
//     t_io    *new;
//     int i;

//     if (ptr.parse.tmp_flag == -1)
//         return (NULL);
//     i = 0;
//     while (data[i])
//     {
//         if (data[i] == '<' && data[i] != '<')
//         {
//             i += 1;
//             new = malloc(sizeof(t_io));
//             new->file = get_file_name(&data[i]);
//             printf("%s\n", new->file);
//             exit(0);
//         }
//         i++;
//     }
//     return (head);
// }

// t_io    *fill_outred(char *data)
// {
//     if (ptr.parse.tmp_flag == -1)
//         return (NULL);
//     return (NULL);
// }

// t_io    *fill_outred_append(char *data)
// {
//     if (ptr.parse.tmp_flag == -1)
//         return (NULL);
//     return (NULL);
// }


// t_cmd   *create_command(char *data)
// {
//     t_cmd   *cmd;
//     int i;

//     cmd = malloc(sizeof(t_cmd));
//     cmd->here_doc = fill_heredoc(data);
//     cmd->in_red = fill_inred(data);
//     cmd->out_red = fill_outred(data);
//     cmd->out_red_append = fill_outred_append(data);
//     ptr.parse.tmp_flag = 0;
//     // if (cmd->here_doc && cmd->here_doc->file)
//     //     printf("%s\n", cmd->here_doc->file);
//     // else
//     //     printf("(nil)\n");
// }

t_aolist *new_node_aolist(char *data, t_aolist *prev)
{
    t_aolist *new;
    
    new = malloc(sizeof(t_aolist));
    new->type = get_type(data);
    new->next = NULL;
    new->prev = prev;
    if (new->type == 'P')
        new->data = create_plist(data);
    else if (new->type == 'T')
        new->data = create_tree(data);
    else if (new->type == 'C')
        new->data = create_command(data);
    else
        new->data = strdup(data);
    return (new);
}