NAME = libft.a

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_strcpy.c\
	ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c ft_strcmp.c ft_realloc.c ft_strcat.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Creating libft archive...$(RESET)"
	@ar -rc $@ $?
	@echo "$(GREEN)✓ libft.a successfully built!$(RESET)"

%.o: %.c
	@printf "$(YELLOW)▶ Compiling... [%s]\r$(RESET)" $
	@$(CC) -c $(CFLAGS) $< -o $@
	@printf "$(GREEN)✓ Compiled   $(RESET)\n"

clean:
	@echo "$(BLUE)Cleaning libft object files...$(RESET)"
	@rm -f $(OBJECTS)

fclean: clean
	@echo "$(BLUE)Removing libft archive...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re