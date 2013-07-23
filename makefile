CC       = g++
CFLAGS   = -g -std=c++11
INCLUDES = -I../glfw/include/
LIB_PATH = -L../glfw/src
LIBS     = -lglfw3 -lpthread -lGL -lX11 -lm -lXrandr -lXxf86vm -lXi -ldl

ifeq ($(DRAW_BOUNDS), 1)
	CFLAGS += -DDRAW_BOUNDS
endif

ifeq ($(WIREFRAME), 1)
	CFLAGS += -DWIREFRAME
endif
CFLAGS += -DWIREFRAME


all: main.o ball.o object.o state.o bounds.o platform.o player.o
	$(CC) $^ -o out $(LIB_PATH) $(LIBS) $(CFLAGS)

%.o: %.cpp %.h
	$(CC) $< $(CFLAGS) $(INCLUDES) -c  -o $@

%.o: %.cpp
	$(CC) $< $(CFLAGS) $(INCLUDES) -c  -o $@

run: all
	./out

clean:
	rm -Rf *.o out
