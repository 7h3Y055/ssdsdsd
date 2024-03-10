all:
	gcc -no-pie -g -g3 srcs/*.c srcs/parse/Syntax_Check/*.c srcs/parse/*.c srcs/execution/built_in_cmd/*.c srcs/parse/GNL/*.c srcs/execution/*.c ./lib/libft/libft.a -I./includes/ -lreadline -o minishell   # -fsanitize=address
clean:
	rm -rf minishell vgcore*
libft:
	make re -C ./lib/libft


# check "" in a command
# check thet += in export and digith in start
# check exit status
