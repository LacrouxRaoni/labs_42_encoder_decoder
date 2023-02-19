NAME	=	encoder

SRC_DIR	=	sources

PATH_OBJ	=	objects

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

RM	=	rm -rf

SRC_FILES	=	encoder.c\
				file_reader.c\
				frequency_table.c\
				linked_list.c\
				huffman.c\
				dictionary.c\
				bin_converter.c\
				memory_share.c\
				memory.c\
				utils.c\
				log.c\
				ft_superjoin.c\
				ft_substr.c


INCLUDES	=	-I ./includes

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ	=	$(SRC:$(SRC_FILES)/%.c=$(PATH_OBJ)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJ) -g3 -o $(NAME) $(INCLUDES)

$(PATH_OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) $(CFLAGS) -g3 -o $@ $<

clean:
	@$(RM) $(PATH_OBJ)
	@echo obj removed

fclean: clean
	@$(RM) $(NAME)
	@echo clean everything

re: fclean all
