# LunaKit for Super Mario Odyssey
![Luna Kit Logo](assets/LunaKitText.png "Logo")

LunaKit is a development tool / modification of Super Mario Odyssey designed to assist in debugging, testing, experimenting, and more! Uses ImGui ExLaunch with a special dedicated SD card folder to allow being layered on top of any RomFS or Starlight mod

![Gameplay 1](https://user-images.githubusercontent.com/62185604/220535481-78afc5ef-29df-4412-ba21-cb98c6b06bae.jpg)

## Features:
- Custom in-game GUI built on [Dear ImGui](https://github.com/ocornut/imgui)
- View and edit large amounts of game info
- Browse, search, favorite, and manipulate every object in a stage
- Many game settings and cheats for players and developers alike
- Primitive Rendering to visually draw additonal game info
- Extremely fast stage warping, including custom stages using [Custom Stage plugins](https://github.com/Amethyst-szs/smo-lunakit/wiki)
- Easy to make [Custom Theme plugins](https://github.com/Amethyst-szs/smo-lunakit/wiki)
- Highly modular and expandable code with a detailed [Wiki page](https://github.com/Amethyst-szs/smo-lunakit/wiki)

![Gameplay 2](https://user-images.githubusercontent.com/62185604/220535575-e94cbda0-a6bf-49fd-ac5f-8bfa92da732f.jpg)

## How to use:
### Controls:
- Open the interface by holding ZR + R and tapping L  
- Hide windows by pressing L-Stick  
- Mouse controls (RECOMMENDED)
  - Navigate interface with a mouse
  - Connect mouse to switch via USB
- Controller controls (NOT RECOMMENDED)
  - Activate or deactivate controller mode by holding ZR + R and tapping ZL
  - Navigate window with D-Pad
  - Interact with windows using A or B
  - Change windows by holding Y and using shoulder buttons

### Building:
- Requires running Linux (Ubuntu recommended)
  - If you're running Windows, try [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)!
- Install [devkitPro](https://devkitpro.org/wiki/Getting_Started) with the switch-dev platform
- Clone or fork this repository
  - If using WSL, make sure to clone the repo inside your WSL directories! Using a folder on your windows machine with WSL drastically slows compile times
- Open bash and run `make`
  - To send to your switch (requires editing FPT_IP in makefile), run make send
  - To increase core usage for compile, run make -j# (# for total cores to use)

## Credits:
- [Amethyst-szs](https://github.com/Amethyst-szs): LunaKit Creator
- [CraftyBoss](https://github.com/CraftyBoss): SMO ExLaunch, ImGui, and more
- [Mars](https://github.com/Mars2032): Referenced TAS Mod, Emotional support


# Original SMO-Exlaunch-Base Description

A base repository using exlaunch-cmake that contains code for modifying Super Mario Odyssey 1.0.

## Credits

- [exlaunch](https://github.com/shadowninja108/exlaunch/)
- [exlaunch-cmake](https://github.com/EngineLessCC/exlaunch-cmake/)
- [BDSP](https://github.com/Martmists-GH/BDSP)
- [Sanae](https://github.com/Sanae6)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere)
- [oss-rtld](https://github.com/Thog/oss-rtld)
