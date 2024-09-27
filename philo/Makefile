NAME = philo
OBJDIR = objets
SRC = Philosophers.c \
	mini_lib.c \
      tools.c

OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread -g3 #-fsanitize=address

# Colors
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(BLUE)$(NAME) linked successfully!$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) # Vérification/création du répertoire objets
	@$(CC) $(FLAGS) -c $< -o $@

clean_objs:
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

clean: clean_objs
	@echo "$(YELLOW)Cleaning completed.$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning all files...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean clean_objs fclean re