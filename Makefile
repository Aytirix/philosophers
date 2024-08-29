NAME = Philosophers
OBJDIR = objets
SRC = Philosophers.c \
      tools.c

OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
LIBFT = Libft
LIBFT_A = $(LIBFT)/libft.a
FLAGS = -Wall -Wextra -Werror
LIBS = -L$(LIBFT) -lft

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT) --no-print-directory

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)
	@echo "$(BLUE)$(NAME) linked successfully!$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -I$(LIBFT) -c $< -o $@

clean_objs:
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

clean: clean_objs
	@$(MAKE) -C $(LIBFT) clean --no-print-directory
	@rm -f $(BONUS_FLAG_FILE)

fclean: clean
	@echo "$(RED)Cleaning all files...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory

re: fclean all

.PHONY: all clean clean_objs fclean re