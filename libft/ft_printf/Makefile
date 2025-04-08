# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 15:21:00 by ael-most          #+#    #+#              #
#    Updated: 2024/11/17 18:54:16 by ael-most         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############
## VARIABLES ##
###############

NAME = libftprintf.a
CC = cc
CCFLAGS = -Wall -Werror -Wextra
CC_COMPILER_CALL = $(CC) $(CCFLAGS) 
AR = ar rcs
RM = rm -f
HEADERS = ft_printf.h

###################
#### MANDATORY ####
###################

SRC = ft_printf.c ft_specifier.c \
	  conversions_src/ft_putchar.c conversions_src/ft_putstr.c \
	  conversions_src/ft_putnbr.c conversions_src/ft_putnbr_unsigned.c \
	  conversions_src/ft_putnbr_hex.c conversions_src/ft_putptr.c

OBJ = $(SRC:.c=.o)

#############
## TARGETS ##
#############

clean:
	$(RM) $(OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

fclean: clean
	$(RM) $(NAME)

re: fclean all

################
### PATTERNS ###
################

%.o : %.c $(HEADERS)
	$(CC_COMPILER_CALL) -c $< -o $@

###############
#### PHONY ####
###############

.PHONY: clean

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
