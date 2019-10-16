CC      = g++
CFLAGS	= -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -L /usr/lib64/ -lglut -lGL -lGLU
  endif
endif


PROJECT = mandelbrot

OBJECTS = mandelbrot.o

all: ${PROJECT}
${PROJECT} : ${OBJECTS} 
	${CC} ${CFLAGS} -o ${PROJECT} ${OBJECTS} ${LDFLAGS} 


%.o: %.cpp
	${CC} -c ${CFLAGS} $<
  
clean:
	rm -f core.* *.o *~ ${PROJECT}