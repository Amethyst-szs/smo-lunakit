![Luna Kit Logo](assets/LunaKitText.png "Logo")

LunaKit is a development tool / modification of Super Mario Odyssey designed to assist in debugging, testing, experimenting, and more! Uses ImGui ExLaunch with a special dedicated SD card folder to allow being layered on top of any RomFS or Starlight mod

![A gameplay screenshot showing LunaKit in Metro Kingdom with the heap viewer, parameter editor, and info viewer open](https://user-images.githubusercontent.com/62185604/232249144-4c7a594e-2abc-44ac-8743-f76eb785cf3e.png)

## Features:
- Custom in-game GUI built on [Dear ImGui](https://github.com/ocornut/imgui)
![Showing the docking system in LunaKit to position windows on the screen](https://user-images.githubusercontent.com/62185604/232249641-826e034e-798e-41c7-9581-8f141ba43917.png)
- View and edit large amounts of game info
- Browse, search, favorite, and manipulate every object in a stage![Gameplay screenshot showing the capabilities of the actor browser](https://user-images.githubusercontent.com/62185604/232249306-c96d515f-6e64-45a4-83f1-0d2048ce8155.png)
- Many game settings and cheats for players and developers alike
- Primitive Rendering to visually draw additonal game info
![Gameplay screenshow showing the primitive rendering options](https://user-images.githubusercontent.com/62185604/232249361-9db6af48-b183-455d-b8f9-4a536c879416.png)
- Extremely fast stage warping, including custom stages using [Custom Stage plugins](https://github.com/Amethyst-szs/smo-lunakit/wiki/Custom-Stage-Support)
- Easy to make [Custom Theme plugins](https://github.com/Amethyst-szs/smo-lunakit/wiki/LunaKit-Theme-Plugins)
![The window menu open over Cascade Kingdom, showing the bult in themes](https://user-images.githubusercontent.com/62185604/232249852-e2e5ebaf-1bf7-4a01-bcdc-0c89fb13c6fd.png)
- Automatically install new updates as they come out with a built in automatic updater
- Highly modular and expandable code with a detailed [Wiki page](https://github.com/Amethyst-szs/smo-lunakit/wiki)

## How to use:

### Installation on switch
- Install Atmosphere and SMO V1.0.0
- Remove any previous mods that would cause conflicts
- Download newest build from [releases](https://github.com/Amethyst-szs/smo-lunakit/releases/)
- Drag and drop the included `atmosphere` and `LunaKit` folders onto the root of your SD card

### Installation on [Ryujinx](https://ryujinx.org/)
- Enable mouse input in Ryujinx settings
- Download newest build from [releases](https://github.com/Amethyst-szs/smo-lunakit/releases/)
- Drag and drop the included `atmosphere` and `LunaKit` folders onto the root of the [emulated SD card](https://github.com/Ryujinx/Ryujinx/wiki/Ryujinx-Setup-&-Configuration-Guide#managing-mods)

### Installation on Yuzu is NOT actively supported.

## Controls:
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

## Building:
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
- [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON): C JSON Parser


# Original SMO-Exlaunch-Base Description

A base repository using exlaunch-cmake that contains code for modifying Super Mario Odyssey 1.0.

## Credits

- [exlaunch](https://github.com/shadowninja108/exlaunch/)
- [exlaunch-cmake](https://github.com/EngineLessCC/exlaunch-cmake/)
- [BDSP](https://github.com/Martmists-GH/BDSP)
- [Sanae](https://github.com/Sanae6)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere)
- [oss-rtld](https://github.com/Thog/oss-rtld)
