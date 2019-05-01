NAME			 = ft_ssl

CC 				 = gcc
CCFLAGS			 = -Wall -Werror -Wextra

ifeq ($(DEBUG),true)
	CCFLAGS += -g -O0
endif

SRC_FILES		 =	main.c					\
					base64.c				\
					base64_encode_decode.c	\
					des.c					\
					des_init.c				\
					des_flags_1.c			\
					des_flags_2.c			\
					des_flags_3.c			\
					des_base64_bridge.c		\
					des_md5_bridge.c		\
					des_salt.c				\
					des_password.c			\
					des_printing.c			\
					des_encrypt_decrypt.c	\
					des_magic_number.c		\
					des_modes.c				\
					conversions1.c			\
					conversions2.c			\
					des_key.c				\
					des_pbkdf.c				\
					des_keys_processing_1.c	\
					des_keys_processing_2.c	\
					des_streaming.c			\
					des_algorithm_1.c		\
					des_algorithm_2.c		\
					des_algorithm_3.c		\
					des_iv.c				\
					md5.c					\
					md5_calculations.c		\
					read_file.c				\
					sha256.c				\
					sha256_calculations.c	\
					support1.c				\
					support2.c				\
					support3.c

SRC_DIR			 = srcs/
OBJ_DIR			 = obj/
OBJ_FILES		 = $(SRC_FILES:.c=.o)
SRC				 = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				 = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT_FILE		 = libft.a
LIBFT_DIR		 = libft/
LIBFT_FLAGS		 = -lft -L $(LIBFT_DIR)
LIBFT			 = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
INC 			 = includes/

FLAGS			 = $(CCFLAGS) $(LIBFT_FLAGS)

FT_SSL_HEADER = ft_ssl.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)$(FT_SSL_HEADER)
	$(CC) $(CCFLAGS) -I $(INC) -I $(LIBFT_DIR) -c $< -o $@ 

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
