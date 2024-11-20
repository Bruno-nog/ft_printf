# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 16:40:21 by brunogue          #+#    #+#              #
#    Updated: 2024/11/20 13:12:00 by brunogue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome da biblioteca
NAME = libftprintf.a

# Configuração do compilador
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Arquivos fontes e objetos
MANDATORY_SRC = ft_printf.c ft_printf_utils.c
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

# Regra principal: compila tudo
all: $(NAME)

# Como criar a biblioteca
$(NAME): $(MANDATORY_OBJ)
	ar rcs $(NAME) $(MANDATORY_OBJ)

# Como compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Limpar arquivos .o
clean:
	rm -f $(MANDATORY_OBJ)

# Limpar tudo, incluindo a biblioteca
fclean: clean
	rm -f $(NAME)

# Recompilar tudo do zero
re: fclean all

# Define alvos que não são arquivos reais
.PHONY: all clean fclean re
