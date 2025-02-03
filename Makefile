CLIENT = client
SERVER = server

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRCDIR = src
CLIENTC_BASE = $(SRCDIR)/utils.c $(SRCDIR)/client.c
SERVERC_BASE = $(SRCDIR)/utils.c $(SRCDIR)/server.c
CLIENTC_BONUS = $(SRCDIR)/utils.c $(SRCDIR)/client_bonus.c
SERVERC_BONUS = $(SRCDIR)/utils.c $(SRCDIR)/server_bonus.c

ifeq ($(filter bonus,$(MAKECMDGOALS)),)
    CLIENTC = $(CLIENTC_BASE)
    SERVERC = $(SERVERC_BASE)
else
    CLIENTC = $(CLIENTC_BONUS)
    SERVERC = $(SERVERC_BONUS)
endif

CLIENTO = $(CLIENTC:.c=.o)
SERVERO = $(SERVERC:.c=.o)

ALLO = $(CLIENTC_BASE:.c=.o) $(SERVERC_BASE:.c=.o) \
       $(CLIENTC_BONUS:.c=.o) $(SERVERC_BONUS:.c=.o)


all: $(SERVER) $(CLIENT)

bonus: $(SERVER) $(CLIENT)

$(SERVER): $(SERVERO)
	$(CC) $(CFLAGS) $(SERVERO) -o $(SERVER)

$(CLIENT): $(CLIENTO)
	$(CC) $(CFLAGS) $(CLIENTO) -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ALLO)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re
