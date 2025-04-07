# Compiler & Flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Ilibft -IMLX42/include -I/opt/homebrew/include
LDFLAGS = -Llibft -LMLX42/build -lft -lmlx42 \
          -L/opt/homebrew/lib -lglfw \
          -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo



# Source Files
SRC = src/main.c \
      src/parse_map.c \
      src/parse_line.c \
      src/utils.c \
	  src/render.c \
	  src/drawing.c \
	  src/color.c

OBJ     = $(SRC:.c=.o)
NAME    = fdf
LIBFT   = libft/libft.a

# Colors
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ $(NAME) successfully built!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C libft

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@echo "$(RED)🧹 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "$(RED)🧹 $(NAME) and libft removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
