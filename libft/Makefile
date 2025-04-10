###############
## VARIABLES ##
###############

NAME = libft.a
CC = cc
CCFLAGS = -Wall -Werror -Wextra
CC_COMPILER_CALL = $(CC) $(CCFLAGS)
AR = ar
ARFLAGS = rcs
RM = rm -f
HEADERS = libft.h

###################
#### MANDATORY ####
###################

SRC =   ft_isalpha.c ft_isdigit.c ft_isascii.c \
                ft_isprint.c ft_strlen.c ft_memset.c \
                ft_bzero.c ft_memcpy.c ft_memmove.c \
                ft_strlcpy.c ft_strlcat.c ft_toupper.c \
                ft_tolower.c ft_strchr.c ft_strrchr.c \
                ft_strncmp.c ft_memchr.c ft_memcmp.c \
                ft_isalnum.c ft_strnstr.c ft_atoi.c \
                ft_calloc.c ft_strdup.c ft_substr.c \
                ft_strjoin.c ft_strtrim.c ft_split.c \
                ft_itoa.c ft_strmapi.c ft_striteri.c \
                ft_putchar_fd.c ft_putstr_fd.c \
                ft_putendl_fd.c ft_putnbr_fd.c

###################
#### GET_NEXT_LINE ####
###################

GET_LINE_SRCS = \
        get_next_line/get_next_line.c\
        get_next_line/get_next_line_utils.c

###################
#### FT_PRINTF ####
###################

FT_PRINTF_DIR = ft_printf

###################
#### OBJECTS ####
###################

OBJ = $(SRC:.c=.o)
GET_LINE_OBJS = $(GET_LINE_SRCS:.c=.o)

#############
## TARGETS ##
#############

all: $(NAME)

$(NAME): $(OBJ) $(GET_LINE_OBJS)
	@make -C $(FT_PRINTF_DIR)
	@$(AR) $(ARFLAGS) $@ $^
	@$(AR) $(ARFLAGS) $@ ft_printf/*.o

%.o: %.c $(HEADERS)
	@$(CC_COMPILER_CALL) -c $< -o $@

clean:
	@make clean -C $(FT_PRINTF_DIR)
	@$(RM) $(OBJ) $(GET_LINE_OBJS)
	@echo "\033[0;33m🧹 Cleaned object files.\033[0m"

fclean: clean
	@make fclean -C $(FT_PRINTF_DIR)
	@$(RM) $(NAME)
	@echo "\033[0;33m🧹 Fully cleaned library.\033[0m"

re: fclean all

bonus: all

###############
#### PHONY ####
###############

.PHONY: all clean fclean re bonus

##################
## HELP MESSAGE ##
##################

help:
	@echo "Available targets:"
	@echo "  all     - Build the library"
	@echo "  bonus   - Build the library with bonus features"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove object files and the library"
	@echo "  re      - Rebuild the library"
	@echo "  help    - Show this help message"

####################
## DEFAULT TARGET ##
####################
.DEFAULT_GOAL := all
