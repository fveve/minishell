NAME = minishell

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I includes

HEADER = minishell.h

BUILTINS = pwd cd export env unset echo

ENV = handle_variable handle_variable_utils handle_variable_utils2 handle_variable_utils3 shell_value unset_utils export_utils export_utils2 cd_utils cd_utils2 export_utils3 export_utils4 export_utils5

EXEC = exit

MAIN = main handle_here_doc manager signal redirections error_manager error_manager_utils redirections_utils redirections_utils2 error_manager_utils2 error_manager_utils3 error_manager_utils4
PARSING = init_data init_data_utils init_data_utils2 init_data_utils3

TOOLS = free_utils libutils ft_split_enhanced ft_split_enhanced_utils tools ft_itoa

PIPEX = ft_exec_cmd pipex utils find_path pipex_utils pipex_utils2

GNL = get_next_line get_next_line_utils

SRC = $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
	$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	$(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	$(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	$(addsuffix .c, $(addprefix srcs/pipex/, $(PIPEX))) \
	$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mMinishell Compiled !"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
	@echo "\n\033[0m./minishell to execute the program !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r\n" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all


.PHONY: clean fclean re 