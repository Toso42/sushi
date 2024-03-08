NAME := sushi

OS 	 := $(shell uname)

ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

SRC_MAIN = 		src/main.c \
				src/header.c \

SRC_UTILS = src/0_splitting_utils/buffer_manipulation.c \
			src/0_splitting_utils/buffer_manipulation2.c \
			src/0_splitting_utils/case_eof.c \
			src/0_utils/char_checks.c \
			src/0_utils/char_checks2.c \
			src/0_utils/char_checks3.c \
			src/0_utils/char_checks4.c \
			src/0_utils/str_checks.c \
			src/0_utils/str_checks2.c \
			src/0_utils/msh_get_env_value.c \
			src/0_utils/copy_set_env.c \
			src/0_utils/shell_handling.c \
			src/0_utils/sigaction_termios.c \

SRC_PROMPT = src/1_prompt/msh_prompt.c \
			src/1_prompt/new_prompt.c \
			src/1_prompt/sub_prompt.c \
			src/1_prompt/prompt_utils.c \
			src/1_prompt/line_completion.c \
			src/1_prompt/assemble_promptline.c \

SRC_S_SPLITTER = src/2_syntax_splitter/msh_syntax_splitter.c \
				src/2_syntax_splitter/msh_syntax_cases.c \
				src/2_syntax_splitter/msh_lsplit_handlers.c \

SRC_S_PARSER		= src/3_syntax_parser/msh_syntax_parser.c \
					src/3_syntax_parser/syntax_cases.c \
					src/3_syntax_parser/syntax_handlers.c \
					src/3_syntax_parser/syntax_handlers_two.c \

SRC_L_FORKER		= src/4_logical_forker/msh_logical_forker.c \
						src/4_logical_forker/lforker_utils.c \
						src/4_logical_forker/bufferization.c \

SRC_P_SPLITTER = src/5_pipes_splitter/msh_pipes_splitter.c \
				src/5_pipes_splitter/msh_pipes_cases.c \

SRC_P_FORKER = src/6_pipes_forker/msh_pipes_forker.c \
				src/6_pipes_forker/forked_pipes.c \
				src/6_pipes_forker/pforker_utils.c \
				src/6_pipes_forker/compound_commands.c \

SRC_TOKEXP = 	src/7_tokenize_expand/msh_tokenize_expand.c \
				src/7_tokenize_expand/msh_expansion_cases.c \
				src/7_tokenize_expand/msh_expansion_handlers.c \
				src/7_tokenize_expand/msh_expansion_handlers2.c \

SRC_NAMEFILE =  src/8_namefile_expansion/msh_namefiles.c \
				src/8_namefile_expansion/wildcard.c \
				src/8_namefile_expansion/wildcard_do_wild.c \
				src/8_namefile_expansion/wildcard_cases.c \
				src/8_namefile_expansion/wildcard_cases2.c \

SRC_REDIRECTIONS = src/9_redirections/msh_redirection_handlers.c \
					src/9_redirections/msh_redirection_splitter.c \
					src/9_redirections/msh_red_resolvepath.c \
					src/9_redirections/heredoc.c \

SRC_BUILTINS = src/10_builtins/cd_home_path.c \
				src/10_builtins/cd.c \
				src/10_builtins/echo.c \
				src/10_builtins/env.c \
				src/10_builtins/exit.c \
				src/10_builtins/export_sort.c \
				src/10_builtins/export_utils.c \
				src/10_builtins/export_utils2.c \
				src/10_builtins/export.c \
				src/10_builtins/pwd.c \
				src/10_builtins/unset.c \
				src/10_builtins/utils_builtins.c \

SRC_EXECUTOR = src/10_executor/executor.c \
				src/10_executor/absolute_path.c \
				src/10_executor/executor_utils.c \
				src/10_executor/if_builtins.c \
				src/10_executor/relative_path.c \

SRC	= $(SRC_MAIN) $(SRC_UTILS) $(SRC_PROMPT) $(SRC_S_SPLITTER) $(SRC_S_PARSER) $(SRC_L_FORKER) $(SRC_P_SPLITTER) $(SRC_P_FORKER) $(SRC_TOKEXP) $(SRC_REDIRECTIONS) $(SRC_NAMEFILE) $(SRC_BUILTINS) $(SRC_EXECUTOR)

FLAGS				:= -g -Wall -Wextra -Werror -fcommon

OBJS				= $(addprefix $(OBJS_DIR)/, ${SRC:.c=.o})
READLINE			= $(addprefix $(READLINE_DIR), $(READLINE_A))
LIBFT				= $(addprefix $(LIBF_DIR), $(LIBFT_A))

# OBJS PREPARATIONS
OBJS_DIR			= objs

# READLINE PREPARATIONS
ifeq ($(OS), Darwin)
	READLINE_FLAG	:= -lreadline -lcurses
else
	READLINE_FLAG	:= -lreadline -ltinfo
endif
READLINE_DIR		:= readline/
READLINE_A			= readline/libhistory.a readline/libreadline.a
READLINE_MAKEFILE 	:= readline/Makefile 
READLINE_CONFIGURE	:= @cd readline && ./configure > /dev/null 
READLINE_MAKE		:= @cd readline && make --no-print-directory > /dev/null
RMREADLINE			:= @cd readline && make distclean --no-print-directory > /dev/null

# LIBFT PREPARATIONS
LIBFT_DIR	:= libft/
LIBFT_A		:= libft/libft.a
LIBFT_MAKE	:= @cd libft && make --no-print-directory && make clean --no-print-directory
RMLIB		:= @cd libft && make fclean --no-print-directory

CC	= @gcc

DEBUG_F	= -g -fsanitize=address

RACE_F	= -g -fsanitize=thread

LEAK_F  = -g -fsanitize=leak -llsan

$(NAME): $(OBJS) $(READLINE_MAKEFILE)
	@echo "	... [Making readline]"
#	@$(READLINE_CONFIGURE)
	@$(READLINE_MAKE) 
	@echo "		${GREEN}Readline compiled${RESET}"
	@echo "	... [Making libft]"
	@$(LIBFT_MAKE)
	@echo "		${GREEN}Libft compiled${RESET}"
	@echo "	... [Making $(NAME)]"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) $(READLINE_A) $(READLINE_FLAG) -o $(NAME) > /dev/null
	@echo "		${GREEN}Minishell compiled${RESET}"
#	@echo " [Compiled]"

# LINK ALL OBJECTS
$(shell echo $(OBJS_DIR))/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

# IF THERES NO READLINE MAKEFILE, CD AND RUN CONFIGURE SCRIPT
$(READLINE_MAKEFILE):
	@echo "	... [Executing Readline Configuration (creating Readline Makefile)]"
	@$(READLINE_CONFIGURE) > /dev/null
	@echo "		${GREEN}Readline's Makefile ready${RESET}"

all: $(NAME)

clean:
	@echo "	... [Removing minishell objs files]"
	@rm   -rf ${OBJS_DIR}
	@echo "		${RED}Minishell OBJS deleted${RESET}"

fclean: clean
	@echo "	... [Removing $(NAME)]"
	@rm -rf ${NAME}
	@echo "		${RED}*.a's deleted${RESET}"
	$(RMLIB)

clean_all: fclean
	$(RMREADLINE)
	$(RMLIB)

readline:	$(READLINE_MAKEFILE)

norm:
	@norminette -R CheckForbiddenSourceHeader src/*.c src/*.h src/*/*.c src/*/*.h libft/*c libft/*.h

sanitize:	re $(OBJS)
			@$(CC) $(DEBUG_F) $(OBJS) $(LIBFT_A) $(READLINE_A) $(READLINE_FLAG) -o $(NAME)
			$(info [Making with fsanitize=address ...])

race:		re $(OBJS)
			@$(CC) $(RACE_F) $(OBJS) $(LIBFT_A) $(READLINE_A) $(READLINE_FLAG) -o $(NAME)
			$(info [Making with fsanitize=thread ...])

leak:		re $(OBJS)
			@$(CC) $(LEAK_F) $(OBJS) $(LIBFT_A) $(READLINE_A) $(READLINE_FLAG) -o $(NAME)
			$(info [Making with fsanitize=leak ...])

re: 		fclean $(NAME)

ree:		clean_all $(NAME)

.PHONY : all clean fclean re
.SILENT: readline
