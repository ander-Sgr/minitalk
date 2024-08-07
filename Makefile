# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestrell <aestrell@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 01:41:47 by aestrell          #+#    #+#              #
#    Updated: 2024/08/07 01:41:47 by aestrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libminitalk.a
CLIENT_EXEC = client
SERVER_EXEC = server

SRCS = ./src/client.c ./src/server.c
LIBFT_DIR = ./includes/libft
FT_PRINT_DIR = ./includes/ft_printf
HEADER_DIR = ./includes/

LIBFT_LIB = $(LIBFT_DIR)/libft.a
FT_PRINT_LIB = $(FT_PRINT_DIR)/libftprintf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rcs

# Archivos objeto
CLIENT_OBJ = ./src/client.o
SERVER_OBJ = ./src/server.o
OBJS = $(SRCS:.c=.o)

# Reglas de construcción
all: $(LIBFT_LIB) $(FT_PRINT_LIB) $(NAME) $(CLIENT_EXEC) $(SERVER_EXEC)

# Compilación de archivos objeto
%.o: %.c
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# Construcción de la biblioteca estática
$(NAME): $(OBJS) $(LIBFT_LIB) $(FT_PRINT_LIB)
	@echo "Creating static library $(NAME) ..."
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(LIBFT_LIB) $(FT_PRINT_LIB)
	@echo "Library $(NAME) created."

# Construcción de los ejecutables
$(CLIENT_EXEC): $(CLIENT_OBJ) $(NAME)
	@echo "Linking client executable ..."
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(CLIENT_OBJ) $(LIBFT_LIB) $(FT_PRINT_LIB) -L. -lminitalk
	@echo "Executable $(CLIENT_EXEC) created."

$(SERVER_EXEC): $(SERVER_OBJ) $(NAME)
	@echo "Linking server executable ..."
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SERVER_OBJ) $(LIBFT_LIB) $(FT_PRINT_LIB) -L. -lminitalk
	@echo "Executable $(SERVER_EXEC) created."

# Construcción de libft
$(LIBFT_LIB):
	@echo "$(GREEN)Building libft library ...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)libft library built.$(RESET)"
# Construcción de ft_printf
$(FT_PRINT_LIB):
	@echo "$(GREEN)Building ft_printf library ...$(RESET)"
	@make -C $(FT_PRINT_DIR)
	@echo "$(GREEN)ft_printf libreary built.$(RESET)"

# Limpieza de archivos objeto
clean:
	@echo "$(GREEN)Cleaning object files ...$(RESET)"
	rm -f $(OBJS) $(CLIENT_OBJ) $(SERVER_OBJ)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINT_DIR) clean
	@echo "$(GREEN)Object files cleaned.$(RESET)"

# Limpieza completa
fclean: clean
	@echo "Cleaning all ..."
	rm -f $(NAME) $(CLIENT_EXEC) $(SERVER_EXEC)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINT_DIR) fclean
	@echo "All cleaned."

# Recompilación
re: fclean all
	@echo "Rebuilding all..."

# Declarar reglas phony
.PHONY: all clean fclean re
