# SFML Minesweeper

An attempt to write the Minesweeper game in SFML. The textures are taken from the Minesweeper back in the Windows XP days.

## How to run

- Open `CMakeLists.txt` and change the `SFML_DIR` to your built library. For more information, refers to [how to build SFML with CMake](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php). Make sure the path is pointed to the folder that has the `SFMLConfig.cmake` (I planned to set the prefix path while typing into the terminal but that's just a pain while writing).

```
mkdir build && cd build
cmake ..
make
./play
```
