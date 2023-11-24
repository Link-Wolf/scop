# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 16:03:22 by xxxxxxx           #+#    #+#              #
#    Updated: 2023/11/24 15:26:51 by xxxxxxx          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	scop

SRCS_FILES		=	scop \
					draw \
					keys \
					manage_shaders \
					classes/Scop.class \
					classes/Parser.class

SRCS			=	$(addsuffix .cpp, $(addprefix srcs/, $(SRCS_FILES)))

OBJS			=	$(SRCS:.cpp=.o)

CC		=	c++
CFLAGS	=	#-Wall -Wextra -Werror
RM		=	rm -rf
LIBS	=	-lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lGLEW
DBG_FLAG=	-g3 -fsanitize=address

OBJ_COLOR		=		"\e[36m"
CLN_COLOR		=		"\e[31m"
FCLN_COLOR		=		"\e[35;5;161m"
BIN_COLOR		=		"\e[36m"
ERRASE_LINE		=		"\e[2K\r"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LIBS) $(DBG_FLAG)
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME)"\t\t\t\t[ ✓ ]\n\e[39m"

%.o: %.cpp
	@$(CC) $(CFLAGS) $(DBG_FLAG) -o $@ -c $<
	@printf $(ERRASE_LINE)$(OBJ_COLOR)"\t"$@"\e[39m"

clean:
	@$(RM) $(OBJS)
	@printf $(CLN_COLOR)"\tClean \t\t\t\t[ ✓ ]\n\e[39m"

fclean: clean
	@$(RM) $(NAME)
	@printf $(FCLN_COLOR)"\tBinary clean \t\t\t[ ✓ ]\n\e[39m"

re: fclean all

.PHONY: all clean fclean re bonus