/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:44:39 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/18 14:44:41 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

# define B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))

# define F1(a, b, c, d, x, ac) { (a) += F((b), (c), (d)) + (x) + (ac); }
# define F2(a, s) { (a) = ROTATE_LEFT ((a), (s)); }
# define F3(a, b) { (a) += (b); }

# define G1(a, b, c, d, x, ac) { (a) += G((b), (c), (d)) + (x) + (ac); }
# define G2(a, s) { (a) = ROTATE_LEFT ((a), (s)); }
# define G3(a, b) { (a) += (b); }

# define H1(a, b, c, d, x, ac) { (a) += H((b), (c), (d)) + (x) + (ac); }
# define H2(a, s) { (a) = ROTATE_LEFT ((a), (s)); }
# define H3(a, b) { (a) += (b); }

# define I1(a, b, c, d, x, ac) { (a) += I((b), (c), (d)) + (x) + (ac); }
# define I2(a, s) { (a) = ROTATE_LEFT ((a), (s)); }
# define I3(a, b) { (a) += (b); }

# define FF(a, b, c, d, x, s, ac) { F1(a, b, c, d, x, ac); F2(a, s); F3(a, b); }
# define GG(a, b, c, d, x, s, ac) { G1(a, b, c, d, x, ac); G2(a, s); G3(a, b); }
# define HH(a, b, c, d, x, s, ac) { H1(a, b, c, d, x, ac); H2(a, s); H3(a, b); }
# define II(a, b, c, d, x, s, ac) { I1(a, b, c, d, x, ac); I2(a, s); I3(a, b); }

# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define EP0(x) (ROTATE_RIGHT(x,2) ^ ROTATE_RIGHT(x,13) ^ ROTATE_RIGHT(x,22))
# define EP1(x) (ROTATE_RIGHT(x,6) ^ ROTATE_RIGHT(x,11) ^ ROTATE_RIGHT(x,25))
# define SIG0(x) (ROTATE_RIGHT(x,7) ^ ROTATE_RIGHT(x,18) ^ ((x) >> 3))
# define SIG1(x) (ROTATE_RIGHT(x,17) ^ ROTATE_RIGHT(x,19) ^ ((x) >> 10))

# define FILE 1
# define STRING 0

# define ENCRYPT 0
# define DECRYPT 1

# define TRUE 1
# define FALSE 0

# define MD5 0
# define SHA256 1

# define ECB 0
# define CBC 1
# define CFB 2
# define OFB 3

# define S11 7
# define S12 12
# define S13 17
# define S14 22
# define S21 5
# define S22 9
# define S23 14
# define S24 20
# define S31 4
# define S32 11
# define S33 16
# define S34 23
# define S41 6
# define S42 10
# define S43 15
# define S44 21

# define BUFFER_SIZE 640

typedef struct		s_read
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	int				buffer_chars;
	int				length;
}					t_read;

typedef struct		s_flags
{
	int				quiet;
	int				reverse;
	int				print;
	char			*input;
	char			*output;
	int				encode;
}					t_flags;

typedef struct		s_md5 {
	uint32_t		state[4];
	uint32_t		x[16];
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					t_md5;

typedef struct		s_sha256 {
	uint32_t		state[8];
	uint32_t		x[64];
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					t_sha256;

typedef struct		s_des
{
	uint8_t			dir;
	uint8_t			mode;

	uint64_t		bytes_read;
	char			*file;
	uint8_t			print;

	uint8_t			buffer[8];
	uint8_t			buffer_filled;

	char			*raw_key;
	uint8_t			key[64];
	uint8_t			key_in_bytes[8];
	uint8_t			final_keys[16][48];

	uint8_t			salted;
	char			*raw_salt;
	uint8_t			salt[8];

	char			*raw_iv;
	uint8_t			iv[8];

	uint8_t			last_block;
	char			*password;
	int				input_fd;
	int				output_fd;
	int				pipe[2];
	uint8_t			base64;
}					t_des;

typedef struct		s_main_dt
{
	char			*name;
	void			(*func)(int, char **);
}					t_main_dt;

typedef struct		s_flags_dt
{
	char			*name;
	void			(*func)(t_des *, int, char **, int *);
}					t_flags_dt;

typedef struct		s_ssl
{
	char			*name;
	unsigned char	*text;
	uint64_t		message_len;
	uint64_t		final_len;
	uint64_t		padded;
	t_flags			flags;
	t_sha256		sha256;
	t_md5			md5;
	int				output_fd;
	int				input_type;
	char			*input_name;
	int				algorithm;
}					t_ssl;

void				md5(int argc, char **argv);
void				sha256(int argc, char **argv);
void				base64(int argc, char **argv);
void				des_cbc(int argc, char **argv);
void				des_ecb(int argc, char **argv);
void				des_cfb(int argc, char **argv);
void				des_ofb(int argc, char **argv);
void				cbc_mode(t_des *des, uint8_t *message_8_bytes,
						uint8_t *g_result_in_bytes);
void				ecb_mode(t_des *des, uint8_t *message_8_bytes,
						uint8_t *g_result_in_bytes);
void				cfb_mode(t_des *des, uint8_t *message_8_bytes,
						uint8_t *g_result_in_bytes);
void				ofb_mode(t_des *des, uint8_t *message_8_bytes,
						uint8_t *g_result_in_bytes);
void				des_encryption(t_des *des, uint8_t *message_8_bytes);
void				parse_arguments(t_des *des, int argc, char **argv);
void				perform_base64_encoding(t_des *des);
void				perform_base64_decoding(t_des *des);
void				create_pipe(t_des *des);
void				perform_ip(uint8_t *message, uint8_t *new_message_right,
						uint8_t *new_message_left);
void				function_f(uint8_t *message_right, uint8_t *key,
						uint8_t *g_f_output);
void				xor(uint8_t *vector1, uint8_t *vector2,
						uint8_t n_elements, uint8_t *vector_res);
void				partition_right_left(u_int8_t *vector, uint8_t length,
						uint8_t *key_right, uint8_t *key_left);
void				function_s(uint8_t *i_vector, uint8_t *o_vector);
void				key64_to_key56(uint8_t *key, uint8_t *new_key);
void				key56_to_key48(uint8_t *key, uint8_t *new_key);

void				des_init(t_des *des);
void				des_update(t_des *des, uint8_t *input,
						uint64_t input_length);
void				des_final(t_des *des);

void				processing_routine(t_des *des);

void				set_input_fd(t_des *des, int argc, char **argv,
						int *pointer);
void				set_output_fd(t_des *des, int argc, char **argv,
						int *pointer);
void				set_base64(t_des *des, int argc, char **argv,
						int *pointer);
void				set_key(t_des *des, int argc, char **argv,
						int *pointer);
void				set_password(t_des *des, int argc, char **argv,
						int *pointer);
void				set_salt(t_des *des, int argc, char **argv,
						int *pointer);
void				set_printing(t_des *des, int argc, char **argv,
						int *pointer);
void				set_decrypt_direction(t_des *des, int argc, char **argv,
						int *pointer);
void				set_encrypt_direction(t_des *des, int argc, char **argv,
						int *pointer);
void				set_iv(t_des *des, int argc, char **argv, int *pointer);

void				base64_encode(t_ssl *ssl, int fd);
void				base64_decode(t_ssl *ssl, int fd);
void				base64_processing(t_ssl *ssl, char *str);
void				init_ssl(t_ssl *ssl, char *name);
void				usage(t_ssl *ssl);
char				*reading_routine(t_read *rd);
void				append_padding(t_ssl *ssl, char *str);
void				md5_append_length(t_ssl *ssl);
char				*process_file(t_ssl *ssl, char *file_name, int flag);
char				*process_string(t_ssl *ssl, char **argv, int *i);
void				print_results(t_ssl *ssl, unsigned char *str, uint64_t len);
void				print_error_and_exit(char *str);
void				chars_to_words(unsigned int *output, unsigned char *input,
						unsigned int len);
void				words_to_chars(unsigned char *output,
						unsigned int *input, unsigned int len);
void				words_to_chars_inverse(unsigned char *output,
						unsigned int *input, unsigned int len);
void				ssl_memset(unsigned char *output, int value,
						unsigned int len);
void				md5_transform(t_md5 *md5, unsigned char block[64]);
void				sha256_transform(t_sha256 *sha256,
						unsigned char block[64]);
uint64_t			ssl_strlen(const char *s);
void				keys_generator(t_des *des);
void				des_preencryption(t_des *des, uint8_t *message);
void				print_vector(uint8_t *ip, uint8_t length);
void				join_halves(uint8_t *vector, uint8_t length,
						uint8_t *key_right, uint8_t *key_left);
void				bytes_to_bits(uint8_t *bytes, uint8_t *bits,
						uint64_t n_bits);
void				hex_to_bits(uint8_t *hex, uint8_t *bits, uint64_t n_bits);
void				bits_to_bytes(uint8_t *bits, uint8_t *bytes,
						uint64_t n_bytes);
int					hex_to_number(uint8_t hex);
uint8_t				number_to_hex(uint8_t number);
void				char_to_uint8_t(uint8_t char_var, uint8_t *bool_vec,
						uint8_t n_bits);
void				algorithm_not_found(char *str);
void				validate_raw_key(char *key);
void				parse_raw_key(t_des *des);
void				validate_raw_iv(char *iv);
void				raw_iv_to_iv(t_des *des);
void				trim_iv(t_des *des);
void				generate_key(t_des *des);
void				get_password(t_des *des);
void				generate_salt(t_des *des);
void				create_salt_in_hex(t_des *des);
void				validate_raw_salt(char *salt);
void				validate_magic_number(t_des *des);
void				read_salt_from_file(t_des *des);
void				raw_salt_to_salt(t_des *des);
void				pbkdf(t_des *des);
void				print_key_salt_iv_in_hex(t_des *des);
void				print_salted(t_des *des);
void				parse_md5_results(t_des *des, uint8_t digest[16]);
void				init_md5_standalone(t_md5 *md5);
void				split_key_into_halves(uint8_t *vector, uint8_t length,
						uint8_t *key_right, uint8_t *key_left);
void				xor_in_bytes(uint8_t *a, uint8_t *b, uint8_t len);
void				des_usage(void);

#endif
