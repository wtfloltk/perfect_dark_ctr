# Perfect Dark port

This repository contains a work-in-progress port of the [Perfect Dark decompilation](https://github.com/n64decomp/perfect_dark) to modern platforms.

To run the port, you must already have a Perfect Dark ROM, specifically one of the following:
* `ntsc-final`/`US V1.1`/`US Rev 1` (md5 `e03b088b6ac9e0080440efed07c1e40f`).  
  **This is the recommended version to use**.  
  Called `NTSC version 8.7 final` on the boot screen.
* `ntsc-1.0`/`US V1.0` (md5 `7f4171b0c8d17815be37913f535e4e93`).  
  Technically supported, but not recommended.  
  Called `NTSC version 8.7 final` on the boot screen as well.
* `jpn-final` (md5 `538d2b75945eae069b29c46193e74790`).  
  Technically supported, but requires a separate custom-built executable.  
  Called `JPN version 8.9 final` on the boot screen.

## Status

The game is in a mostly functional state, with both singleplayer and split-screen multiplayer modes fully working.  
There are minor graphics- and gameplay-related issues, and possibly occasional crashes.

**The following extra features are implemented:**
* mouselook;
* dual analog controller support;
* widescreen resolution support;
* configurable field of view;
* 60 FPS support, including fixes for some framerate-related issues;
* fixes for a couple original bugs and crashes;
* basic mod support, currently enough to load a few custom levels;
* slightly expanded memory heap size.

Currently only 32-bit platforms are supported, namely x86 Windows and Linux.  
Note that 32-bit binaries will still work on 64-bit versions of those platforms,
though you might have to install some additional libraries.

## Download

Latest [automatic builds](https://github.com/fgsfdsfgs/perfect_dark/actions) for supported platforms:
* [i686-windows](https://nightly.link/fgsfdsfgs/perfect_dark/workflows/c-cpp/port/pd-i686-windows.zip)
* [i686-linux](https://nightly.link/fgsfdsfgs/perfect_dark/workflows/c-cpp/port/pd-i686-linux.zip)

## Running

You must already have a Perfect Dark ROM to run the game, as specified above.  

1. Create a directory named `data` next to `pd.exe`.
2. Put your Perfect Dark ROM named `pd.ntsc-final.z64` into it.
3. Run `pd.exe`.

Additional information can be found in the [wiki](https://github.com/fgsfdsfgs/perfect_dark/wiki).

A GPU supporting OpenGL 3.0 or above is required to run the port.

## Controls

1964GEPD-style and Xbox-style bindings are implemented.

N64 pad buttons X and Y (or `X_BUTTON`, `Y_BUTTON` in the code) refer to the reserved buttons `0x40` and `0x80`, which are also leveraged by 1964GEPD.

Support for one controller, two-stick configurations are enabled for 1.2.

Note that the mouse only controls player 1.

Controls can be rebound in `pd.ini`. Default control scheme is as follows:

| Action           | Keyboard and mouse     | Xbox pad                 | N64 pad                   |
| -                | -                      | -                        | -                         |
| Fire / Accept    | LMB/Space              | RT                       | Z Trigger                 |
| Aim mode         | RMB/Z                  | LT                       | R Trigger                 |
| Use / Cancel     | E                      | N/A                      | B                         |
| Use / Accept     | N/A                    | A                        | A                         |
| Crouch cycle     | N/A                    | L3                       | `0x80000000` (Extra)      |
| Half-Crouch      | Shift                  | N/A                      | `0x40000000` (Extra)      |
| Full-Crouch      | Control                | N/A                      | `0x20000000` (Extra)      |
| Reload           | R                      | X                        | X `(0x40)`                |
| Previous weapon  | Mousewheel forward     | B                        | D-Left                    |
| Next weapon      | Mousewheel back        | Y                        | Y `(0x80)`                |
| Radial menu      | Q                      | LB                       | D-Down                    |
| Alt fire mode    | F                      | RB                       | L Trigger                 |
| Alt-fire oneshot | `F + LMB` or `E + LMB` | `A + RT`` or 'RB + RT`   | `A + Z`     or `L + Z`    |
| Quick-detonate   | `E + Q`   or `E + R`   | `A + B`   or `A + X`     | `A + D-Left`or `A + 0x40` |

## Building

### Windows

1. Install [MSYS2](https://www.msys2.org).
2. Open the `MINGW32` prompt. (**NOTE:** _not_ the `MSYS` prompt or the `MINGW64` prompt)
3. Install dependencies: `pacman -S mingw-w64-i686-toolchain mingw-w64-i686-SDL2 mingw-w64-i686-zlib make git`
4. Run `make -f Makefile.port` in the `perfect_dark` directory.
5. The resulting executable will be at `build/ntsc-final-port/pd.exe`.

### Linux

1. Ensure you have gcc, g++ and 32-bit versions of SDL2, libGL and ZLib installed on your system.
   * On a 64-bit system you also need to have `gcc-multilib` and `g++-multilib` (or your distro's analogues) installed.
2. Run the following command in the `perfect_dark` directory:
   * On a 64-bit system: ```make -f Makefile.port TARGET_PLATFORM=i686-linux```
   * On a 32-bit system: ```make -f Makefile.port```
3. The resulting executable will be at `build/ntsc-final-port/pd.exe`.  

Currently only `i686-linux` and `i686-windows` are supported, using `gcc -m32` and `i686-w64-mingw32-gcc` as compilers, respectively.  
Alternate compilers can be specified by passing `TOOLCHAIN=i686-whatever-` as a command line argument.

For both platforms you can optionally specify `ROMID=jpn-final` on the `make` command line to build the JPN executable.  
You will need to provide a `jpn-final` ROM for that, named `pd.jpn-final.z64`.

It might be possible to build a 32-bit ARM executable, but this has not been tested.

## Credits

* the original [decompilation project](https://github.com/n64decomp/perfect_dark) authors;
* doomhack for the only other publicly available [PD porting effort](https://github.com/doomhack/perfect_dark) I could find;
* [sm64-port](https://github.com/sm64-port/sm64-port) authors for the audio mixer and some other changes;
* [Ship of Harkinian team](https://github.com/Kenix3/libultraship/tree/main/src/graphic/Fast3D), Emill and MaikelChan for the libultraship version of fast3d that this port uses;
* lieff for [minimp3](https://github.com/lieff/minimp3);
* Mouse Injector and 1964GEPD authors for some of the 60FPS- and mouselook-related fixes;
* everyone who has submitted pull requests and issues to this repository and tested the port;
* probably more I'm forgetting.
