CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MAKEFLAGS += --silent
SRC = ft_atoi.c ft_putchar_fd.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_memcmp.c \
      ft_memcpy.c ft_memmove.c ft_memset.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c ft_strlen.c \
      ft_strncmp.c ft_strrchr.c ft_bzero.c ft_memchr.c ft_putendl_fd.c ft_strlcpy.c ft_substr.c \
      ft_calloc.c ft_tolower.c ft_toupper.c ft_strnstr.c ft_strmapi.c ft_strjoin.c ft_striteri.c \
      ft_strdup.c ft_strchr.c ft_putstr_fd.c ft_isprint.c ft_split.c ft_itoa.c ft_lstnew.c \
      ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstaddback.c ft_lstadd_front.c \
      get_next_line.c

OBJ = $(SRC:.c=.o)

NAME = libft.a

AR = ar -rcs

# Farben für den Fortschritt
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@figlet "Libft"
	@echo "$(YELLOW)Building: [#.........]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [##........]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [###.......]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [####......]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [######....]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [#######...]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [########..]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [#########.]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [##########]$(RESET)\r\n"
	$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN) ✅ Build Complete! $(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
