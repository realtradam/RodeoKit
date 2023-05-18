
<!-- <img align="right" src="https://user-images.githubusercontent.com/11139432/233201393-5a683fd2-6661-4af9-a332-1b9b0d5e5edb.png" width="288px">  -->

# Rodeo Kit

<img align="right" src="https://user-images.githubusercontent.com/11139432/233207951-1c804cf4-365e-44e8-849d-9fc1a4c49be1.gif">  

[API Cheatsheet](https://dev.catgirls.rodeo/rodeo_kit/cheatsheet)

[See here](https://dev.catgirls.rodeo/rodeo_kit) for more details about the goals and approach of this project.

<!-- [Rodeo Kit Example](https://github.com/realtradam/rodeo_sample_game) -->

## Short-Term Roadmap

### Rendering

- [x] Low level 2D rendering system by collecting vertices/indices and then uploading them in batches to the GPU through [BGFX](https://github.com/bkaradzic/bgfx).
- [x] Loading and drawing textures.
- [x] Default shader that allows tinting of any textures drawn.

### Input

- [x] Callback event-based input system.
- [x] Bind inputs(such as character keys) to function pointers. Once the key is pressed the function is called.
- [x] Abstract into "commands" which allows adding functions, adding multiple inputs, and assigning to "scenes" that can be enabled or disabled.  
- [X] Implementing further input abstractions by 5 categories:  
    - [x] Binary (such as keys on a keyboard, or buttons on a controller)
    - [X] Bounded Range (such as the x and y joysticks on a controller)
    - [ ] Bounded Magnitude (such as pressure sensitive triggers on a controller)
    - [x] Unbounded Range (such as the x and y mouse delta)
    - [x] Positional (such as the position of a mouse)

### Logging

- [x] Implemented logging system with 3 different levels(info, warn, error).
- [x] System allows for setting your own logging function instead if the default "print to console" is not desired.
- [ ] Option to disable specific warning levels.

### Build System

- [x] CMake build system which manages pulling dependencies from git-submodules and building them automatically as required.
- [ ] Builds for all target platforms.
    - [x] Linux.
    - [x] Web(Emscripten).
    - [ ] Windows.

### Sound

- [x] A basic system for loading sounds and music, as well as playing it.

### Documentation

- [ ] Add short descriptions above each function.
- [x] Automated static site generator for the documentation, in the style of the [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html).
- [ ] Example games showing off common usages of the kit.

### Scripting Bindings

- [ ] Bindings to an embedded version of Ruby known as mruby.
- [ ] Create bindings directly to C versions of functions.
- [ ] Create comfortable API on top of the direct bindings.

