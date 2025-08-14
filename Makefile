# Nome do executável final
NAME = test_ft_printf

# Pasta de código fonte
SRC_DIR = src

# Pastas de headers
INC_DIR = includes

# Lista de arquivos fonte
SRCS = $(SRC_DIR)/ft_printf.c \
       $(SRC_DIR)/parser/ft_printf_parser.c \
       $(SRC_DIR)/handlers/ft_printf_handlers.c \
       $(SRC_DIR)/number_utils/ft_printf_number_utils.c \
       $(SRC_DIR)/utils/ft_printf_utils.c \
       main.c

# Lista de arquivos objeto (.o) correspondentes aos SRCS
OBJS = $(SRCS:.c=.o)

# Compilador C a ser usado
CC = gcc

# Flags de compilação rigorosas para o seu código (com -Werror)
FT_PRINTF_CFLAGS = -Wall -Wextra -Werror -g -I $(INC_DIR)

# Flags de compilação mais flexíveis para o arquivo de teste (sem -Werror)
MAIN_CFLAGS = -Wall -Wextra -g -I $(INC_DIR)

# Regra padrão
all: $(NAME)

# Regra para construir o executável final, ligando os objetos
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

# Regra para compilar ft_printf.c e suas partes
# Usamos uma regra genérica que aplica as flags rigorosas
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FT_PRINTF_CFLAGS) -c $< -o $@

# Regra para compilar main.c especificamente com as flags mais flexíveis
main.o: main.c
	$(CC) $(MAIN_CFLAGS) -c $< -o $@

# Regra para limpar apenas os arquivos objeto
clean:
	rm -f $(OBJS)

# Regra para limpar todos os arquivos gerados (objetos e executável)
fclean: clean
	rm -f $(NAME)

# Regra para recompilar tudo (limpa e constrói do zero)
re: fclean all

.PHONY: all clean fclean re