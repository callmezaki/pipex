NAME = pipex
INCLUDE = pipex.h
SRC = 	pipex.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_split.c \
		ft_strjoin_beta.c \
		ft_strncmp.c \
		pipex_tools.c \
		get_next_line_utils.c \
		get_next_line.c \
		pipex_heredoc.c \
		ft_strtrim.c \
		ft_strlcpy.c \

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)
$(NAME): $(INCLUDE) $(SRC:.c=.o)
	@gcc  $(SRC) -I $(INCLUDE) -o $(NAME)
clean:
	rm -f $(SRC:.c=.o)
fclean: clean
	rm -f $(NAME)
re: fclean all