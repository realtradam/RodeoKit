
<img align="right" src="https://user-images.githubusercontent.com/11139432/233201393-5a683fd2-6661-4af9-a332-1b9b0d5e5edb.png" width="288px">

# Rodeo Kit

Game development kit designed and implemented from the ground up for personal indie game development as well as learning. Inspired by the simplicity of [Raylib](https://www.raylib.com)'s design.

Design planning for this project is "Game Oriented", meaning that I would like to create games to stress test the implementation and see what works, what doesnt, and what is missing. The current and planned implementation is simply the "minimum" amount required to create simple game projects. Once this goal is reached, small games will be developed in tandem with this kit in order to drive its design and development.

The goal of this style of design approach is to avoid over-thinking of future design, as well as to save time from implementing features that go unused.

## Implemented

### Rendering

- Implementented low level 2D rendering system by collecting vertices/indices and then uploading them in batches to the GPU through [BGFX](https://github.com/bkaradzic/bgfx).
- Implemented loading and drawing textures.
- Implemented shader that allows tinting of any textures drawn.

### Input

- Callback event-based input system.
- Bind inputs(such as character keys) to function pointers. Once the key is pressed the function is called.

#### Input To-Do:

- Abstract into "commands" which allows naming, adding functions, adding multiple inputs, and assigning to "scenes" that can be enabled or disabled.  
- Implementing further input abstractions by 4 categories:  
    - Binary (such as keys on a keyboard, or buttons on a controller)
    - Bounded Range (such as the x and y joysticks on a controller)
    - Unbounded Range (such as the x and y mouse delta)
    - Positional (such as the position of a mouse)

### Logging

- Implemented logging system with 3 different levels(info, warn, error).
- System allows for setting your own logging function instead if the default "print to console" is not desired.

### Build System

- CMake build system which manages pulling dependencies from git-submodules and building them automatically as required.
- Builds for both desktop(Linux) and web(Emscripten) platforms.

#### Build System To-Do

- Build for the Windows desktop platform.

## Short-Term Roadmap

### Sound

- A system for loading sounds and music, as well as playing it.

### Documentation

- Add short descriptions above each function.
- Automated static site generator for the documentation, in the style of the [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html).
- Example games showing off common usages of the kit.

### Scripting Bindings

- Bindings to an embedded version of Ruby known as mruby.
- Create bindings directly to C versions of functions.
- Create comfortable API on top of the direct bindings.

