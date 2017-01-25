
#	Library output
NAME = libft.a

#	GCC flags
CFLAGS = -Werror -g
ALL_CFLAGS = -Wall -Wextra $(CFLAGS)

#	Ojcts/Sources directories
INC_LIBFT = includes/
SRC_LIBFT = $(shell find . | grep "\.c$$" | sed "s/\.c$$//g")
INCLUDES += $(addprefix -iquote , $(INC_LIBFT))
SRCS += $(addsuffix .c, $(SRC_LIBFT))

#	Final OBJS
OBJS = $(SRCS:.c=.o)

#	Layout
VERBOSE = false

all: header $(NAME) footer

header:
	@echo "\033[1;36m[\033[1m$(NAME)]\033[0m\033[1;33m Compile, link & archive\033[0m"

footer:
	@echo "\033[1;36m[\033[1m$(NAME)]\033[0m\033[1;32m Well Done\033[0m"

$(NAME): $(OBJS)
ifeq ($(VERBOSE),true)
	@echo "\033[1;36m. Archive .\033[0m $(NAME)"
else
	@printf "\033[1;31m.\033[0m\n"
endif
	@$(AR) rcus $(NAME) $(OBJS)

%.o: %.c
ifeq ($(VERBOSE),true)
	@echo "\033[1;36m. Compile .\033[0m $<"
else
	@printf "\033[1;31m.\033[0m"
endif
	@$(CC) $(ALL_CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\033[1;36m[\033[1m$(NAME)]\033[0m\033[1;33m >>\033[0m \033[1;33mclean (*.o)\033[0m"
	@$(RM) $(OBJS)

fclean: clean
	@echo "\033[1;36m[\033[1m$(NAME)]\033[0m\033[1;33m >>\033[0m \033[1;33mfclean ($(NAME))\033[0m"
	@$(RM) $(NAME)

re: fclean all
