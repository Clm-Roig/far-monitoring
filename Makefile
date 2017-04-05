obj_dir=obj/
bin_dir=bin/
src_dir=src/
CC=gcc
CFLAGS=-Wall -lSDL2_image -lSDL2  -g
LDFLAGS=`sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_gfx -g
EXEC=$(bin_dir)serverPosition.exe

all: $(EXEC)

$(bin_dir)serverPosition.exe: $(obj_dir)init.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	find . -type f | xargs -n 5 touch
	rm -f $(obj_dir)* $(bin_dir)*

start:
	./bin/serverPosition.exe
