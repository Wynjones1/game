CC := clang
CFLAGS   := --std=gnu99 -g
INCLUDES := -I../glfw/include/ -I../containers/include/
LIBS     := -L../glfw/src/

out: main.o ball.o draw.o simulate.o object.o init.o state.o callbacks.o ../containers/list.o
	$(CC) $^ -o $@ $(CFLAGS) $(INCLUDES) $(LIBS) -lglfw3 -lpthread -lGL -lX11 -lm -lXrandr -lXxf86vm -lXi -ldl

%.o: %.c %.h
	$(CC) $<  $(CFLAGS) $(INCLUDES) -c -o $@

%.o: %.c
	$(CC) $<  $(CFLAGS) $(INCLUDES) -c -o $@

run:
	make
	./out

clean:
	rm -rf *.o out
