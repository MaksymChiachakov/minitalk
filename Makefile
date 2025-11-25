# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/25 13:22:14 by mchiacha          #+#    #+#              #
#    Updated: 2025/11/25 14:05:00 by mchiacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

SRCS_CLIENTBONUS = client_bonus.c
SRCS_SERVERBONUS = server_bonus.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

OBJS_CLIENTBONUS = ${SRCS_CLIENTBONUS:.c=.o}
OBJS_SERVERBONUS = ${SRCS_SERVERBONUS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

bonus: $(NAME_SERVER)_bonus $(NAME_CLIENT)_bonus

$(NAME_SERVER)_bonus: $(OBJS_SERVERBONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVERBONUS) -o $(NAME_SERVER)

$(NAME_CLIENT)_bonus: $(OBJS_CLIENTBONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENTBONUS) -o $(NAME_CLIENT)

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENTBONUS) $(OBJS_SERVERBONUS) $(OBJS_CLIENT:.o=.d) $(OBJS_SERVER:.o=.d) $(OBJS_CLIENTBONUS:.o=.d) $(OBJS_SERVERBONUS:.o=.d)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(OBJS_CLIENT:.o=.d)
-include $(OBJS_SERVER:.o=.d)
-include $(OBJS_CLIENTBONUS:.o=.d)
-include $(OBJS_SERVERBONUS:.o=.d)