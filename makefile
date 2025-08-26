Unix_SDL_image:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lSDL2_image -lm && ./main
push:
	git add .
	git commit -m "SDL2 Chaste Chess Update"
	git push
