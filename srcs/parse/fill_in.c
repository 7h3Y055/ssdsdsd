#include "minishell.h"

char	*read_heredoc(char *limiter)
{
	char	*tmp;
	char	*buffer;
	char	*new_buffer;

	write(1, ">", 1);
	buffer = NULL;
	tmp = get_next_line_G(0);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(tmp);
			break ;
		}
		new_buffer = ft_strjoin_G(buffer, tmp);
		free(buffer);
		buffer = new_buffer;
		free(tmp);
		write(1, ">", 1);
		tmp = get_next_line_G(0);
	}
	get_next_line_G(INT_MAX);
    free(limiter);
	return (buffer);
}

t_io    *ft_heredoc(char *limiter)
{
    t_io    *head;

    if (ptr.parse.tmp_flag == -1)
        return (NULL);
    head = new_io_node(NULL, 'H');
    limiter = remove_quotation(limiter);
    limiter = ft_strjoin(limiter, "\n");
    head->file = read_heredoc(limiter);
    head->next = NULL;
    head->fd = -1;
    // *index += i - 1;
    return (head);
}

t_io *ft_read_file(char *file)
{
    int i;
    t_io    *head;

    i = 1;
    if (ptr.parse.tmp_flag == -1)
        return (NULL);
    head = new_io_node(NULL, 'R');
    file = remove_quotation(file);
    head->file = ft_strdup(file);
    head->next = NULL;
    head->fd = -1;
    return (head);
}

t_io    *fill_inred(char **args)
{
    t_io    *head;
    t_io    *new;
    int i;

    i = 0;
    head = NULL;
    while (args[i])
    {
        if (ptr.parse.tmp_flag == -1)
            return (NULL);
        if (ft_strncmp(args[i], "<<", 3) == 0)
        {
            new = ft_heredoc(args[i + 1]);
            args[i][0] = 0;
            // if (args[i + 1])
            args[i + 1][0] = 0;
            add_back_io(&head, new);
        }
        else if (ft_strncmp(args[i], "<", 2) == 0)
        {
            new = ft_read_file(args[i + 1]);
            args[i][0] = 0;
            args[i + 1][0] = 0;
            add_back_io(&head, new);
        }
        i++;
    }
    return (head);
}