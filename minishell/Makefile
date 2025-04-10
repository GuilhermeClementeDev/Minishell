NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

LIBFT = $(LIB_DIR)/libft.a

SRCS = \
		$(SRC_DIR)/main.c \

VASCAO = \
		$(OBJ_DIR)/main.o \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(VASCAO) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
	@mv $(OBJS) $(OBJ_DIR)/

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all
