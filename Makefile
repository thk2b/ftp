### FILES ###

CLIENT = client
SERVER = server

SHARED_INC = -I shared/inc
SERVER_INC = -I server/inc
CLIENT_INC = -I client/inc

SHARED_SRC = $(addprefix shared/src/, )
SERVER_SRC = $(addprefix server/src/,
	$(addprefix listener/, )
	$(addprefix controller/, )
)
CLIENT_SRC = $(addprefix client/src/,

)

SHARED_OBJ = $(SHARED_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

### FLAGS ###

CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast
FLAGS += -fsanitize=address -g

### RULES ###

all: $(CLIENT) $(SERVER)

$(CLIENT): $(SHARED_OBJ) $(CLIENT_OBJ)
	$(CC) $(FLAGS) $(SHARED_OBJ) $(CLIENT_OBJ)

$(SERVER): $(SHARED_OBJ) $(SERVER_OBJ)
	$(CC) $(FLAGS) $(SHARED_OBJ) $(SERVER_OBJ)

shared/%.c: shared/%.o
	$(CC) $(FLAGS) $(SHARED_INC) -c $< -o $@

client/%.c: client/%.o
	$(CC) $(FLAGS) $(CLIENT_INC) -c $< -o $@

server/%.c: server/%.o
	$(CC) $(FLAGS) $(SERVER_INC) -c $< -o $@

clean:
	rm -f $(SHARED_OBJ) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER)
