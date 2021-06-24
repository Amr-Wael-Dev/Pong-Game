# Pong-Game
A classic game that consists of two players and a ball, the ball can bounce off the ceiling and the floor while the players keep trying to get it to pass the other player's side. The first player to reach a score of 10 wins. The game contains many game modes such as 2 players, classic, inverted, mouse, and warp. This game is written in C++ using the SFML library.

## This project depends on the sfml library, so make sure to update in the project's properties page:
### 1: (All configurations) path\to\your\sfml\folder\include (in the C/C++ tab > General > Additional Include Directories)
### 2: (All configurations) path\to\your\sfml\folder\lib (in the Linker tab > General > Additional Library Directories)
### 3: (Release mode) sfml-graphics.lib;sfml-system.lib;sfml-audio.lib;sfml-network.lib;sfml-window.lib; (in the Linker tab > Input > Additional Dependencies)
### 3: (Debug mode) sfml-graphics-d.lib;sfml-system-d.lib;sfml-audio-d.lib;sfml-network-d.lib;sfml-window-d.lib; (in the Linker tab > Input > Additional Dependencies)
