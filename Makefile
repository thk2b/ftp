CLIENT = client
SERVER = server

SHARED_SRC = $(addprefix src/, protocol.c status.c)
SHARED_INC = -I src

CLIENT_INC = $(SHARED_INC) -I src/client
CLIENT_SRC = $(SHARED_SRC) $(addprefix src/client/, init.c main.c)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_INC = $(SHARED_INC) -I src/server
SERVER_SRC = $(SHARED_SRC) $(addprefix src/server/, init.c run.c  main.c)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS += -fsanitize=address -g
COMPILE = $(CC) $(FLAGS)

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJ)
	$(COMPILE) $(CLIENT_OBJ) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(COMPILE) $(SERVER_OBJ) -o $(SERVER)

%.o: %.c
	$(COMPILE) $(SERVER_INC) $(CLIENT_INC) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all
