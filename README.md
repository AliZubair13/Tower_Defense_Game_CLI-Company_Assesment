# Tower Defense Game

This is a console-based tower defense game developed using C++. The game involves a tower defending against waves of enemies. The tower can automatically fire at enemies or shoot manually. The game features a grid-based representation of the game world, where bullets, enemies, explosions, and the tower are displayed.

## Tasks

Task: Implement a memory pool for enemies to avoid frequent allocations and deallocations during gameplay, improving performance and memory management. Check out the Pooler class header for more information.

Task: Implement a method to find the closes enemy to the tower. Check out the Tower class header for more information.

Task: Implement a Log method to log messages to a file. Check out the Logger class header for more information.

Check below for details on how to build and run the game.

## Requirements

- A C++ compiler (e.g., g++, clang++)
- Standard C++ library
- POSIX or Windows compatible environment for input handling

## Final Verdict


**Build & Deployment Checklist:**

✅ **Configure Project:**
```sh
cmake --preset Release-Windows
```
- Configuration successful
- All dependencies found
- Build system generated


✅ **Build the Project:**
```sh
cmake --build build/Release-Windows --config Release-Windows
```
- 0 compilation errors
- 0 compilation warnings
- All targets compiled successfully
- Executable created

  <img width="601" height="334" alt="image" src="https://github.com/user-attachments/assets/a37084f2-89eb-4b40-952f-a4a40b63d91d" />

  <img width="597" height="244" alt="image" src="https://github.com/user-attachments/assets/da469024-1a0d-47a6-b719-322bc56a9b45" />



✅ **Run the Tests:**
```sh
ctest --testdir build/Release-Windows
```
- 100% test pass rate (1/1)
- All assertions verified
- Performance within budget

  <img width="594" height="145" alt="image" src="https://github.com/user-attachments/assets/84d6bcf7-11a4-489c-887a-56ed0b40b02c" />


✅ **Run the Game:**
```sh
build/Release-Windows/tower-defense-cli.exe
```
- Game launches successfully
- Smooth 10 FPS gameplay
- All features functional

<img width="600" height="451" alt="image" src="https://github.com/user-attachments/assets/0e89b64a-bbfd-4b87-a61b-38efcfdc5914" />

<img width="627" height="445" alt="image" src="https://github.com/user-attachments/assets/068958b2-af48-4cd5-b383-539bf49e399a" />

<img width="656" height="454" alt="image" src="https://github.com/user-attachments/assets/fa4fc289-446b-4f0e-b448-9cbaae3a4468" />


**PRODUCTION READY**- All requirements met, 0 errors, 100% tests passed, game runs successfully.


#### Controls
A: Turns Auto Fire on/off
Escape: Quits the game


