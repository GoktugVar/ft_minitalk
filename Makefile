NAME                = minitalk
CLIENT              = client
SERVER              = server
CLIENT_BONUS        = client_bonus
SERVER_BONUS        = server_bonus

CLIENT_SRC          = mandatory/client.c mandatory/utils.c
SERVER_SRC          = mandatory/server.c mandatory/utils.c
CLIENT_BONUS_SRC    = bonus/client_bonus.c bonus/utils_bonus.c
SERVER_BONUS_SRC    = bonus/server_bonus.c bonus/utils_bonus.c

RM                  = rm -rf
CC                  = gcc
CFLAGS              = -Wall -Wextra -Werror

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_BONUS_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_BONUS): $(SERVER_BONUS_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

fclean: clean

re: fclean all

.PHONY: all clean fclean re bonus
