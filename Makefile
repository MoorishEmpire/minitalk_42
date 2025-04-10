###############
## VARIABLES ##
###############
NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus
CC = cc
CCFLAGS = -Wall -Werror -Wextra
CC_COMPILER_CALL = $(CC) $(CCFLAGS)
RM = rm -f
HEADER = ./mandatory/minitalk.h
HEADER_BONUS = ./bonus/minitalk_bonus.h

# Libft Path
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a

###################
#### MANDATORY ####
###################
CLIENT_SRC = mandatory/client.c
SERVER_SRC = mandatory/server.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

###################
##### BONUS #######
###################
CLIENT_BONUS_SRC = bonus/client_bonus.c
SERVER_BONUS_SRC = bonus/server_bonus.c
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)

#############
## TARGETS ##
#############
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENT_OBJ) $(LIBFT_LIB)
	@$(CC_COMPILER_CALL) $(CLIENT_OBJ) $(LIBFT_LIB) -o $(NAME_CLIENT)
	@echo "\033[0;32m✅ Client compilation successful!\033[0m"

$(NAME_SERVER): $(SERVER_OBJ) $(LIBFT_LIB)
	@$(CC_COMPILER_CALL) $(SERVER_OBJ) $(LIBFT_LIB) -o $(NAME_SERVER)
	@echo "\033[0;32m✅ Server compilation successful!\033[0m"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(CLIENT_BONUS_OBJ) $(LIBFT_LIB)
	@$(CC_COMPILER_CALL) $(CLIENT_BONUS_OBJ) $(LIBFT_LIB) -o $(NAME_CLIENT_BONUS)
	@echo "\033[0;32m✅ Bonus client compilation successful!\033[0m"

$(NAME_SERVER_BONUS): $(SERVER_BONUS_OBJ) $(LIBFT_LIB)
	@$(CC_COMPILER_CALL) $(SERVER_BONUS_OBJ) $(LIBFT_LIB) -o $(NAME_SERVER_BONUS)
	@echo "\033[0;32m✅ Bonus server compilation successful!\033[0m"

%.o: %.c $(HEADER)
	@$(CC_COMPILER_CALL) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(CLIENT_OBJ) $(SERVER_OBJ) $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ)
	@echo "\033[0;33m🧹 Cleaned object files.\033[0m"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	@echo "\033[0;33m🧹 Fully cleaned project.\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
