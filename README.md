# 🧠 NeuroEscape

NeuroEscape is a stealth-themed 2D escape game built with **C++** and **SDL2**, featuring AI guards, collectible items, vision-based fog-of-war, and emoji-style characters. The player must navigate through a maze, avoid patrolling guards, collect a key, and unlock a door to escape — all while racing against time.

---

## 🎮 Gameplay Features

- ✅ **Emoji-Style Visuals**  
  - Player is a round green smiley face with tongue 😋  
  - Guards are angry red faces with hats 😠🧢  

- 🧱 **Maze Environment**  
  - Complex wall layouts with a checkerboard-style floor  
  - Real-time collision detection with walls and guards

- 👁️ **Fog of War System**  
  - Only reveals a circular area around the player  
  - Creates a stealth gameplay vibe

- 🚨 **AI Guards with Patrol & Chase Logic**  
  - Guards patrol a path by default  
  - If the player comes close, they switch to **chase mode**

- 🔑 **Key & Locked Door Mechanic**  
  - Collect a key to unlock the exit door  
  - Escaping triggers a win screen with your completion time

- ⏱️ **Escape Timer**  
  - Timer starts when the game begins  
  - Time shown in final escape message (used to track score)

---

## 🧰 Tools & Technologies

- **C++17**
- **SDL2** (Simple DirectMedia Layer)
- **CMake** (build system)
- **MinGW / MSYS2** (compiler + toolchain)
- **Visual Studio Code** (IDE)

---

## 🏁 Getting Started

### ✅ Prerequisites

- CMake
- SDL2 development libraries (installed via MSYS2 or other)
- MinGW (or any C++17-compatible compiler)

### 🔨 Build Instructions

```bash

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/msys64/ucrt64"
cmake --build build
cd build
./NeuroEscape.exe
NeuroEscape/
├── src/               # Source files (.cpp)
├── include/           # Header files (.hpp)
├── assets/ (optional) # Future: audio, textures, levels
├── build/             # CMake build folder
├── CMakeLists.txt     # Build configuration
├── README.md          # This file

```
---
🚀 Future Plans
- Multiple levels & file-based level loading

- Sound effects and background music

- Sprint/stamina system

- UI overlays (score, health, lives)

- Pause menu and settings
---
🙌 Author
- 👨‍💻 Shahab Jamali
- BSc Computer Science @ Nottingham Trent University
- LinkedIn: https://www.linkedin.com/in/shahab-jamali-133690249/
- GitHub: https://github.com/ShahabCompSci
---
📸 Screenshots
- (Coming soon — show off the player, guard, fog-of-war, and maze layout!)
---
🧠 Why This Project?
- This project demonstrates my strengths in:

- Object-oriented design

- Game loop architecture

- SDL2 graphics & event handling

- AI behavior implementation

Problem-solving and debugging complex interactions (collision, pathfinding, UI feedback)

It reflects my passion for building intelligent, interactive systems — especially those with real-world analogies like stealth, tracking, and visual limitations.
