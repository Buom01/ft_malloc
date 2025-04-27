ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC 			:=	clang
NAME		:=	libft_malloc_$(HOSTTYPE).so
SYMLINK		:=	libft_malloc.so
LIBFT		:=	libft/libft.a
RM			:=	rm -f

SRCS		:=	srcs/allocations.c \
			srcs/multithreading.c \
			srcs/system.c \
			srcs/malloc.c \
			srcs/calloc.c \
			srcs/free.c \
			srcs/realloc.c \
			srcs/ft_putptr_fd.c \
			srcs/ft_putnbr_fd.c

LIBRARY		?=	-I ./libft

OBJS		:=	$(SRCS:.c=.o)
CFLAGS		?=	-Wall -Werror -Wextra -g3 -fPIC $(LIBRARY)

# Colors
RED			:= $(shell printf "\033[0;91m")
GREEN		:= $(shell printf "\033[0;92m")
BLUE		:= $(shell printf "\033[0;94m")
MAGENTA		:= $(shell printf "\033[0;95m")
RESET		:= $(shell printf "\033[0;0m")
PREFIX		:= $(MAGENTA)$(NAME)$(RESET) => 

$(NAME): $(LIBFT) $(OBJS) $(SYMLINK) 
	@echo "$(PREFIX)$(GREEN)Bundling $(RESET)$(NAME)$(GREEN) library$(RESET)"
	@$(CC) -shared $(CFLAGS) $(OBJS) $(LIBFT) $(LIBRARY) -o $@

$(SYMLINK):
	@echo "$(PREFIX)$(GREEN)Symlinking to $(RESET)$(SYMLINK)"
	@ln -sf $(NAME) $(SYMLINK)

$(LIBFT):
	cd libft && make

%.o: %.c
	@echo "$(PREFIX)$(GREEN)Compiling file $(RESET)$< $(BLUE)to $(RESET)$@"
	@$(CC) $(CFLAGS) $(LIBRARY) -c $< -o $@

all: $(NAME)

fclean:
	cd libft && make fclean
	$(RM) $(OBJS)
	$(RM) $(SYMLINK)
	$(RM) $(NAME)

clean:
	cd libft && make clean
	$(RM) $(OBJS)

re: fclean
	$(MAKE) all
