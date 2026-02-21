compile: 
	g++ -Isource/include -Isource/include/SDL2 -Isrc -Isrc/ev -Isrc/object -Lsource/lib -o main main.cpp src/ev/*.cpp src/object/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
run:
	./main.exe
