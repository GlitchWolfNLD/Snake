game:
	g++ src/game_object.cpp src/game.cpp src/snake.cpp src/main.cpp -o play -I include -L lib -l SDL2-2.0.0