CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = mandatory/client.c
SRC2 = mandatory/server.c
SRC3 = bonus/client_bonus.c
SRC4 = bonus/server_bonus.c
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)
OBJ4 = $(SRC4:.c=.o)
NAME = client
NAME2 = server
NAME3 = client_bonus
NAME4 = server_bonus
RM = rm -f
all: $(NAME) $(NAME2)
$(NAME): $(OBJ) mandatory/minitalk.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
$(NAME2): $(OBJ2) mandatory/minitalk.h
	$(CC) $(CFLAGS) $(SRC2) -o $(NAME2)
bonus: $(NAME3) $(NAME4)
$(NAME3): $(OBJ3) bonus/minitalk_bonus.h
	$(CC) $(CFLAGS) $(SRC3) -o $(NAME3)
$(NAME4): $(OBJ4) bonus/minitalk_bonus.h
	$(CC) $(CFLAGS) $(SRC4) -o $(NAME4)
clean:
	$(RM) $(OBJ) $(OBJ2) $(OBJ3) $(OBJ4)
fclean: clean
	$(RM) $(NAME) $(NAME2) $(NAME3) $(NAME4)
re: fclean all