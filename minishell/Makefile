NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
LIB_DIR = lib
BUILTIN_DIR = builtins

LIBFT = $(LIB_DIR)/libft.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/utilits.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/utilits_env.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/utilits_export.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/builtins.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/builtins2.c \
	$(SRC_DIR)/$(BUILTIN_DIR)/error.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@clear
	@echo "✅ ${NAME} is compiled."

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJS)
	@clear
	@echo "🗑️ Objects removed."

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@clear
	@echo "🗑️ Program and objects removed."

re: fclean all
