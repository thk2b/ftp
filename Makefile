CLIENT = client
SERVER = server

LIB = libft/libft.a

SHARED_SRC = $(addprefix src/, protocol.c io.c)
SHARED_INC = -I src -I libft/includes

CLIENT_INC = $(SHARED_INC) -I src/client
CLIENT_SRC = $(SHARED_SRC) $(addprefix src/client/, commands.c status.c parse_addr.c init.c get_request.c send_request.c get_response.c resolve_address.c run.c main.c\
	$(addprefix handlers/, quit_handler.c list_handler.c pwd_handler.c cwd_handler.c retr_handler.c stor_handler.c pasv_handler.c mkd_handler.c)\
)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_INC = $(SHARED_INC) -I src/server
SERVER_SRC = $(SHARED_SRC) $(addprefix src/server/, status.c init.c responses.c get_request.c send_response.c format_addr.c path.c list.c controller.c run.c main.c\
	$(addprefix handlers/, quit_handler.c list_handler.c pwd_handler.c cwd_handler.c retr_handler.c stor_handler.c pasv_handler.c mkd_handler.c)\
)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
# FLAGS += -fsanitize=address -g
COMPILE = $(CC) $(FLAGS)

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LIB)
	$(COMPILE) $(CLIENT_OBJ) $(LIB) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(LIB)
	$(COMPILE) $(SERVER_OBJ) $(LIB) -o $(SERVER)

$(LIB):
	make -C libft

%.o: %.c
	$(COMPILE) $(SERVER_INC) $(CLIENT_INC) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)
	make clean -C libft

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	make fclean -C libft

re: fclean all
