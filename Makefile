HEAD = Glfw.hpp
#includes/

#SRCS_DIR = srcs/

#_SRCS = 

#SRCS = $(addprefix $(SRCS_DIR), $(_SRCS))

SRCS = main.cpp Glfw.cpp

OBJS = ${SRCS:.cpp=.o}

CXX = c++

CFLAGS = -I/$(HOME)/.brew/Cellar/glfw/3.3.9/include
#cluster for mac
#-I/$(HOME)/.brew/Cellar/glfw/3.3.9/include
#-Wall -Wextra -Werror

GLFW_FLAGS = -L$(HOME)/.brew/Cellar/glfw/3.3.9/lib -lglfw -framework OpenGL
#cluster for mac
#-L$(HOME)/.brew/Cellar/glfw/3.3.9/lib -lglfw -framework OpenGL
#home for linux
#-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

D_FLAGS = -g3
#-fsanitize=address

NAME = cpp_cub3d

#color
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all : ${NAME}

%.o : %.cpp
	${CXX} ${CFLAGS} -c $< -o $@ 
#-I${HEAD}

${NAME} : ${OBJS} ${HEAD}
	${CXX} ${CFLAGS} ${OBJS} -o ${NAME} ${GLFW_FLAGS}
	@echo "$(GREEN)cpp_cub3d compiled!$(DEF_COLOR)"

debug : ${SRCS}
	${CXX} ${D_FLAGS} $^ -o ${NAME} 
#	-I${HEAD}
	@echo "$(GREEN)cpp_cub3d debug compiled!$(DEF_COLOR)"

clean :
	@rm -f ${OBJS}
	@echo "$(BLUE)cpp_cub3d, object files cleaned!$(DEF_COLOR)"

fclean : clean
	@rm -f ${NAME}
	@echo "$(YELLOW)cpp_cub3d, library files cleaned!$(DEF_COLOR)"

re :
	${MAKE} fclean
	${MAKE} all
	@echo "$(MAGENTA)Cleaned and rebuilt everything for cpp_cub3d!$(DEF_COLOR)"

.PHONY : all clean fclean re bonus