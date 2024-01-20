# Terminal Based Music Player
## Usage
- Put music files into the appropriately named folder
- Space followed by Enter to play/pause
- Ctrl + C to exit

## First Time Setup
To compile the program, use this command
~~~
  g++ musicplayer.cpp -o musicplayer -lSDL2 -lSDL2_mixer -lsfml-graphics -lsfml-window -lsfml-system -lpthread -I /path/to/SDL2/include -L /path/to/SDL2/lib -std=c++17
~~~
To run the program, run this
~~~
./musicplayer
~~~
## Fixes to common issues
~~~
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-mixer-dev install libsfml-dev
~~~
