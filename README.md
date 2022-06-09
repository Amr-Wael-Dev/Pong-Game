# Pong Game

![Gameplay](https://github.com/Amr-Wael-Dev/Pong-Game/blob/main/Resources/4.jpg)

A classic game that consists of two players and a ball, the ball can bounce off the ceiling and the floor while the players keep trying to get it to pass the other player's side.

The first player to reach a score of 10 wins.

The game contains many game modes such as 2 players, classic, inverted, mouse, and warp. This game is written in C++ using the SFML library.

---

## Project Documentation
### How To Run:
#### This project depends on the SFML library, so make sure to update in the project's properties page:
1. (All configurations) path\to\your\sfml\folder\include (in the C/C++ tab > General > Additional Include Directories)
2. (All configurations) path\to\your\sfml\folder\lib (in the Linker tab > General > Additional Library Directories)
3. (Release mode) sfml-graphics.lib;sfml-system.lib;sfml-audio.lib;sfml-network.lib;sfml-window.lib; (in the Linker tab > Input > Additional Dependencies)
4. (Debug mode) sfml-graphics-d.lib;sfml-system-d.lib;sfml-audio-d.lib;sfml-network-d.lib;sfml-window-d.lib; (in the Linker tab > Input > Additional Dependencies)
5. Simply Run The Project

### You should be presented with a window that looks like this

![Main Menu](https://github.com/Amr-Wael-Dev/Pong-Game/blob/main/Resources/1.jpg)

---

### Controls
#### Menus
- :arrow_up:: Previous Menu Item
- :arrow_down:: Next Menu Item
- Esc: Go To Previous Menu
- Enter (Return): Choose Current Item

#### 1 Player Gameplay
- :arrow_up:: Move Player 1 Up
- :arrow_down:: Move Player 1 Down
- Space: Move The Ball After Scoring
- Esc: Pause/Continue

#### 2 Players Gameplay
- :arrow_up:: Move Player 1 Up
- :arrow_down:: Move Player 1 Down
- W: Move Player 2 Up
- S: Move Player 2 Down
- Space: Move The Ball After Scoring
- Esc: Pause/Continue
---
The variety of modes in this game is what makes this game so special

Current Available Modes:
- Classic
- Inverted
- Mouse
- Warp


![Mode Menu](https://github.com/Amr-Wael-Dev/Pong-Game/blob/main/Resources/3.jpg)

---
## I'd really like to get feedback on this project (keep in mind that this was my first interaction with code in my life 😅)
---
## Notes:
- Time feature doesn't work yet
- A bug arises when the ball hits a player from above or below
