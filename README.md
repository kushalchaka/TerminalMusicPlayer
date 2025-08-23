# Terminal Based Music Player
## Usage
- Put music files into the appropriately named folder
- Space followed by Enter to play/pause
- Ctrl + C to exit

I made this to work alongside a different program, so hopefully this is of some use to others as well with similar goals :)

## First Time Setup

Create a directory called downloadedMusic to put your music files inside of first

To compile the program, use this command
~~~
  g++ musicplayer.cpp -o musicplayer -lSDL2 -lSDL2_mixer -lsfml-graphics -lsfml-window -lsfml-system -lpthread -I /path/to/SDL2/include -L /path/to/SDL2/lib -std=c++17
~~~
To run the program, run this
~~~
./musicplayer
~~~
## Fixes to common issues (on Linux, untested on Windows and Mac so cannot verify that this will work on those OS)
~~~
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-mixer-dev install libsfml-dev
~~~
