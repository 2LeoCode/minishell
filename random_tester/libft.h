#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# ifndef __WORDSIZE
#  error __WORDSIZE is not defined
# endif
# if __WORDSIZE == 32
#  define HIMAGIC 0x80808080UL
#  define LOMAGIC 0x01010101UL
# elif __WORDSIZE == 64
#  define HIMAGIC 0x8080808080808080UL
#  define LOMAGIC 0x0101010101010101UL
# else
#  define HIMAGIC -1
#  define LOMAGIC -1
# endif

# define SWAP_BUFFER_SIZE 128
# define NULL_ENDED ((unsigned int)-1)

unsigned int		ft_abs(int n);
int					ft_atoi(const char *s);
unsigned int		ft_atoi_u(const char *s);
long				ft_atol(const char *s);
unsigned long		ft_atol_u(const char *s);
long long			ft_atoll(const char *s);
unsigned long long	ft_atoll_u(const char *s);
void				ft_beep(void);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				ft_destroy_array(void **ar, unsigned int size);
int					ft_getchar(void);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
char				*ft_itoa(int n);
char				*ft_itoa_u(unsigned int n);
char				*ft_lltoa(long long n);
char				*ft_lltoa_u(unsigned long long n);
char				*ft_ltoa(long n);
char				*ft_ltoa_u(unsigned long n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memcdup(const void *s, size_t len, char c);
void				*ft_memchr(const void *b, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memdup(const void *s1, size_t len);
void				*ft_memjoin(const void *s1, const void *s2, size_t len1,
						size_t len2);
void				*ft_memfind(const void *haystack, const void *needle,
						size_t h_len, size_t n_len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memndup(const void *s1, size_t len, size_t n);
void				*ft_mempcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memsub(const void *s, size_t len, unsigned int start,
						size_t n);
void				*ft_memtrim(const void *s, const void *set, size_t s_len,
						size_t set_len);
int					ft_putchar(int c);
int					ft_putchar_fd(int c, int fd);
int					ft_putendl(const char *s);
int					ft_putendl_fd(const char *s, int fd);
int					ft_putllong(long long nb);
int					ft_putllong_fd(long long nb, int fd);
int					ft_putlong(long nb);
int					ft_putlong_fd(long nb, int fd);
int					ft_putnbr(int nb);
int					ft_putnbr_fd(int nb, int fd);
int					ft_putstr(const char *s);
int					ft_putstr_fd(const char *s, int fd);
char				*ft_rplchr(char *s, int before, int after);
char				**ft_split(const char *s, int c);
char				*ft_stpcpy(char *dst, const char *src);
char				*ft_stpncpy(char *dst, const char *src, size_t n);
int					ft_strcasecmp(const char *s1, const char *s2);
char				*ft_strcasestr(const char *haystack, const char *needle);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strcdup(const char *s, char c);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
int					ft_strerase(char **s, unsigned int i);
int					ft_strinsert(char **s, unsigned int i, int c);
int					ft_strisalnum(const char *s);
int					ft_strisalpha(const char *s);
int					ft_strisascii(const char *s);
int					ft_strisdigit(const char *s);
int					ft_strislower(const char *s);
int					ft_strisprint(const char *s);
int					ft_strisspace(const char *s);
int					ft_strisupper(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strcjoin(const char *s1, const char *s2, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int					ft_strncasecmp(const char *s1, const char *s2, size_t n);
char				*ft_strncat(char *dst, const char *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strndup(const char *s1, size_t n);
size_t				ft_strnlen(const char *s, size_t maxlen);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
char				*ft_strntrim(const char *s, const char *set, size_t n);
char				*ft_strrchr(const char *s, int c);
int					ft_strreplace(char *s, char *before, char *after);
int					ft_strreplace_first(char **dst_ptr, char *before,
						char *after, void (*destructor)(void *));
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strtrim(const char *s, const char *set);
char				*ft_substr(const char *s, unsigned start, size_t n);
void				ft_swap(void *a, void *b, size_t size);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_wrdlen(const char *s);

#endif
