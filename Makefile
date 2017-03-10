obj_dir=obj/
bin_dir=bin/
src_dir=src/
CC=gcc
CFLAGS=-Wall -lSDL2_image -lSDL2 
LDFLAGS=`sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_gfx
EXEC=$(bin_dir)ServeurPosition.exe

all: $(EXEC)

$(bin_dir)ServeurPosition.exe: 
	$(obj_dir) hello.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(obj_dir)* $(bin_dir)*

start:
	./bin/ServeurPosition.exe

