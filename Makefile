NAME = pipex
INCLUDE = pipex.h
INCLUDE_B = pipex_bonus.h
SRC = 	pipex.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_split.c \
		ft_strjoin_beta.c \
		ft_strncmp.c \
		pipex_tools.c \
		get_next_line_utils.c \
		get_next_line.c \
		ft_strtrim.c \
		ft_strlcpy.c \

SRC1 = pipex_tools_bonus.c \
		ft_split_bonus.c \
		ft_strdup_bonus.c \
		ft_strjoin_beta_bonus.c \
		ft_strlcpy_bonus.c \
		ft_strlen_bonus.c \
		ft_strncmp_bonus.c \
		ft_strtrim_bonus.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		pipex_heredoc_bonus.c \
		pipex_bonus.c \

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRC:.c=.o)
OBJ_B = $(SRC1:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@rm -f  $(OBJ_B) $(NAME)
	@gcc   -I $(INCLUDE) -o $@ $^

bonus : $(OBJ_B)
	@rm -f $(OBJS) $(NAME)
	@gcc  -I $(SRC_B) $(INCLUDE_B) -o $(NAME) $^

clean:
	rm -f $(OBJS) $(OBJ_B)
fclean: clean
	rm -f $(NAME)
re: fclean all