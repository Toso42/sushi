# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 12:49:58 by tdi-leo           #+#    #+#              #
#    Updated: 2022/12/12 17:38:22 by kzak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
  				ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c\
				ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
				ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
				ft_split.c ft_strchr.c ft_strrchr.c ft_strdup.c\
  				ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c\
				ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
				ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
				ft_printf.c ft_printf_utils.c ft_printf_utils2.c ft_printbits.c\
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
				ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c\
				ft_lstmap.c\
				ft_sarfree.c ft_saradd_back.c ft_sarsize.c ft_sarprint.c\
				ft_sardel.c ft_strcmp_precision.c\
				ft_strintertrim.c ft_strjoinfree.c ft_strnstr_precision.c\
				ft_printd.c ft_sarcopy.c\
				ft_printfd.c ft_printfd_utils.c\
				ft_strcmp.c ft_char_to_str.c ft_atoicheck.c\
				ft_free.c \
#SRCSNEW		=	ft_sarfree.c ft_saradd_front.c ft_sarsize.c ft_sarprint.c\

OBJS_DIR	= objs

OBJS		= $(addprefix $(OBJS_DIR)/, ${SRCS:.c=.o})

#OBJSNEW		= $(addprefix $(OBJS_DIR)/, ${SRCS:.c=.o})

CC			= @gcc

RM			= @rm -rf

FLAGS		= -g -Wall -Wextra -Werror

NAME = libft.a

BONUS = lst.a

${NAME}:	${OBJS}
#			$(info [Making library..])
#			@ar rc ${NAME} ${OBJS} ${OBJSNEW}
			@ar rc ${NAME} ${OBJS}

$(shell echo $(OBJS_DIR))/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_DIR}
#			$(info [cleaning library objects ..])

fclean:		clean
			${RM} ${NAME}
#			$(info [cleaning all library..])

re:			fclean ${NAME}
