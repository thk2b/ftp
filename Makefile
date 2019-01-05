CLIENT = client
SERVER = server

CLIENT_INC = -I src -I src/client
CLIENT_SRC = $(addprefix src/client/, main.c)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_INC = -I src -I src/server
SERVER_SRC = $(addprefix src/server/, main.c)
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
