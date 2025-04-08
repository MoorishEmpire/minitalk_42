# Mandatory Variables CC = cc CCFLAGS = -Wall -Werror -Wextra
CC_COMPILER_CALL = $(CC) $(CCFLAGS)
RM = rm -f
HEADER = ./mandatory/minitalk.h
CLIENT = client.c
SERVER = server.c

# Mandatory Sources
CLIENT_SRC = mandatory/client.c
SERVER_SRC = mandatory/server.c

# Bonus Variables
HEADER_BONUS = ./bonus/minitalk_bonus.h
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

# Bonus Sources
CLIENT_BONUS_SRC = bonus/client_bonus.c
SERVER_BONUS_SRC = bonus/server_bonus.c

# Libft Path
LIBFT_DIR = ./libft_mandatory
LIBFT_LIB = ./libft_mandatory/libft.a

# Targets
all: $(CLIENT) $(SERVER)

$(CLIENT) : $(LIBFT_LIB) $(CLIENT_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

$(SERVER) : $(LIBFT_LIB) $(SERVER_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS) : $(LIBFT_LIB) $(CLIENT_BONUS_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

$(SERVER_BONUS) : $(LIBFT_LIB) $(SERVER_BONUS_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) mandatory/client.o mandatory/server.o bonus/client_bonus.o bonus/server_bonus.o

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: clean

@echo "\033[0m"
@echo "\033[0;32m"
@echo "\t   ____                     _                           _    "
@echo "\t  | __ ) _   _    __ _ ___ | |      _ __ ___   ___  ___| |_  "
@echo "\t  |  _ \| | | |  / _\`|/ _ \  |_____| '\''_  \\ / _ \/ __| __| "
@echo "\t  | |_) | |_| | | (_| |  __/ |_____| | | | | | (_) \__ \ |_  "
@echo "\t  |____/ \__, |  \__,_|\___|_|     |_| |_| |_|\___/|___/\__| "
@echo "\t         |___/                                               "
@echo "\033[0m"
@echo "\033[0;33m" 
@echo "\t  _ ____________    __  __ ___ ___  "
@echo "\t / |__ /__ /__  |  |  \/  | __|   \ "
@echo "\t | ||_ \|_ \ / /   | |\/| | _|| |) |"
@echo "\t |_|___/___//_/    |_|  |_|___|___/ "
@echo "\033[0m"
endef
