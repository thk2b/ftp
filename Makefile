### FILES ###

CLIENT = client
SERVER = server

SHARED_INC = -I ftp_shared/inc
SERVER_INC = -I ftp_server/inc
CLIENT_INC = -I ftp_client/inc

SHARED_SRC = $(addprefix ftp_shared/src/, )
SERVER_SRC = $(addprefix ftp_server/src/,\
	$(addprefix listener/,\
		$(addprefix transitions/, sl_init.c)\
		sl_transitions.c\
	)\
	$(addprefix controller/,\
		$(addprefix transitions/, sc_process_data.c)\
		sc_transitions.c\
	)\
	s_main.c\
)
CLIENT_SRC = $(addprefix ftp_client/src/,\
	$(addprefix transitions/, c_error.c c_failure.c )\
	c_transitions.c c_main.c\
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
	$(CC) $(FLAGS) $(SHARED_INC) $(CLIENT_INC) $(SHARED_OBJ) $(CLIENT_OBJ)

$(SERVER): $(SHARED_OBJ) $(SERVER_OBJ)
	$(CC) $(FLAGS) $(SHARED_INC) $(SERVER_INC) $(SHARED_OBJ) $(SERVER_OBJ)

ftp_shared/%.o: ftp_shared/%.c
	$(CC) $(FLAGS) $(SHARED_INC) -c $< -o $@

ftp_client/%.o: ftp_client/%.c
	$(CC) $(FLAGS) $(SHARED_INC) $(CLIENT_INC) -c $< -o $@

ftp_server/%.o: ftp_server/%.c
	$(CC) $(FLAGS) $(SHARED_INC) $(SERVER_INC) -c $< -o $@

clean:
	rm -f $(SHARED_OBJ) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER) 
