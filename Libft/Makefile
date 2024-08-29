NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = 	chain_list/ft_lstadd_back.c \
		chain_list/ft_lstadd_front.c \
		chain_list/ft_lstclear.c \
		chain_list/ft_lstdelone.c \
		chain_list/ft_lstdup.c \
		chain_list/ft_lstiter.c \
		chain_list/ft_lstlast.c \
		chain_list/ft_lstmap.c \
		chain_list/ft_lstnew.c \
		chain_list/ft_lstprev.c \
		chain_list/ft_lstsize.c \
		chain_list/ft_lstswap.c \
		chain_list/ft_lstupdate.c \
		character/ft_bzero.c \
		character/ft_isalnum.c \
		character/ft_isalpha.c \
		character/ft_isascii.c \
		character/ft_isdigit.c \
		character/ft_isprint.c \
		character/ft_tolower.c \
		character/ft_toupper.c \
		conversion/ft_atoi.c \
		conversion/ft_calloc.c \
		conversion/ft_itoa.c \
		get_next_line/get_next_line_utils.c \
		get_next_line/get_next_line.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		memory/ft_memset.c \
		output/ft_putaddress_fd.c \
		output/ft_putchar_fd.c \
		output/ft_putendl_fd.c \
		output/ft_putnbr_base_fd.c \
		output/ft_putstr_fd.c \
		printf/ft_printf.c \
		string/ft_split.c \
		string/ft_strchr.c \
		string/ft_strdup.c \
		string/ft_striteri.c \
		string/ft_strjoin.c \
		string/ft_strlcat.c \
		string/ft_strlcpy.c \
		string/ft_strlen.c \
		string/ft_strmapi.c \
		string/ft_strncmp.c \
		string/ft_strnstr.c \
		string/ft_strrchr.c \
		string/ft_strtrim.c \
		string/ft_substr.c \
		math/ft_power.c \
		math/ft_abs.c

OBJDIR = objets
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

.PHONY: all clean fclean re directories

all: directories $(NAME)

directories:
	@mkdir -p $(OBJDIR)/chain_list $(OBJDIR)/character $(OBJDIR)/conversion $(OBJDIR)/get_next_line $(OBJDIR)/memory $(OBJDIR)/output $(OBJDIR)/printf $(OBJDIR)/string $(OBJDIR)/math

$(NAME): $(OBJ)
	@echo "$(BLUE)Building $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) built successfully!$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || (echo "Compilation failed for $<"; exit 1)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
