#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <thread>
#include <atomic>

namespace fs = std::filesystem;

class MusicPlayer {
public:
    MusicPlayer() : isPaused(false) {
        // Initialize SDL audio subsystem
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            // Handle initialization failure
        }

        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
            std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
            // Handle initialization failure
        }
    }

    ~MusicPlayer() {
        // Close SDL_mixer and SDL
        Mix_CloseAudio();
        SDL_Quit();
    }

    void loadMusicFiles(const std::string& folderPath) {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            const std::string fileExtension = entry.path().extension().string();
            // Check if the file has a supported extension (e.g., mp3 or flac)
            if (fileExtension == ".mp3" || fileExtension == ".flac" || fileExtension == ".wav") {
                musicFiles.push_back(entry.path().string());
            }
        }

        // Sort the music files alphabetically
        std::sort(musicFiles.begin(), musicFiles.end());
    }

    void togglePause() {
        isPaused = !isPaused;
        if (isPaused) {
            Mix_PauseMusic();
            std::cout << "Paused playback." << std::endl;
        } else {
            Mix_ResumeMusic();
            std::cout << "Resumed playback." << std::endl;
        }
    }

    void play() {
        for (const auto& musicFile : musicFiles) {
            Mix_Music* music = Mix_LoadMUS(musicFile.c_str());
            if (!music) {
                std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
                // Handle loading failure
            }

            std::cout << "Now playing: " << musicFile << std::endl;

            Mix_PlayMusic(music, 0);

            // Wait for the music to finish playing
            while (Mix_PlayingMusic() != 0) {
                SDL_Delay(100);
            }

            Mix_FreeMusic(music);
        }
    }

    bool getIsPaused() const {
        return isPaused;
    }

private:
    std::vector<std::string> musicFiles;
    std::atomic<bool> isPaused;
};

void handleInput(MusicPlayer& musicPlayer, std::atomic<bool>& quit) {
    while (!quit) {
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "q") {
            quit = true;
        } else if (userInput == " ") {
            // Toggle play/pause on Space key press
            musicPlayer.togglePause();
        }
    }
}

int main() {
    MusicPlayer musicPlayer;

    // Specify the folder path where the music files are stored
    const std::string folderPath = "downloadedMusic";

    // Load music files from the specified folder
    musicPlayer.loadMusicFiles(folderPath);

    std::cout << "Press Space then Enter to toggle play/pause. Press Ctrl + C quit." << std::endl;

    // Play the loaded music files
    std::atomic<bool> quit(false);
    std::thread inputThread(handleInput, std::ref(musicPlayer), std::ref(quit));

    musicPlayer.play();

    // Wait for the input thread to finish
    inputThread.join();

    return 0;
}

