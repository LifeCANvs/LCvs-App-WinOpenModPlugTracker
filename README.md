
# README


# OpenMPT and libopenmpt

This repository contains OpenMPT, a free Windows/Wine-based
[tracker](https://en.wikipedia.org/wiki/Music_tracker) and libopenmpt,
a library to render tracker music (MOD, XM, S3M, IT MPTM and dozens of other
legacy formats) to a PCM audio stream. libopenmpt is directly based on OpenMPT,
offering the same playback quality and format support, and development of the
two happens in parallel.

## Systems support

OpenMPT System Requirements - from https://openmpt.org/system_requirements

OpenMPT has rather modest system requirements. The software runs on old 32-Bit machines as well as on modern 64-Bit systems.

### Recommended specs

For modern versions of OpenMPT with *full features* and *optimal performance*:
- Windows 10 20H2 or newer
- An x86- or amd64-compatible CPU with the SSE2 instruction set, 2+ GHz and two or more cores
- A large display
- A sound device with native low-latency ASIO support is recommended if you plan to do low-latency live recording
- A high capacity SSD / HDD for storing many modules and samples

### Minimum specs

For modern versions of OpenMPT with perhaps some *reduced* features and performance:
- Windows 7 SP1 or newer
- Pentium 4 or a better x86- or amd64-compatible CPU with SSE2 support, or a device that supports Windows on ARM
- Display resolution: 800x600
- Some kind of sound device
- 30 MB of free disk space

### Historic specs

For retro / legacy versions of OpemMPT:
- Windows XP - for using experimental reduced-functionality builds of current version of OpenMPT; or for legacy version OpenMPT 1.28.10.00
- Windows 2000 **or** Windows 98SE / ME **with** *KernelEx* Windows NT5.x compatibility layer and all updates - for using legacy version OpenMPT 1.26.14.00
- Windows 98SE / ME - for natively using legacy version OpenMPT 1.18.03.00


Note: VST plugins have their own system requirements and you will probably need a much more powerful computer system to run some of them.

### Wine

If you are running Linux or a similar Operating System, you can run OpenMPT through Wine 1.8 or newer. The software runs fairly well with the exception of a few little glitches.

OpenMPT works fine with the Wine version that ships with current Linux distributions.

## Downloads

Get compiled executables at https://openmpt.org/download

### Modern

- Windows 7 SP 1 / Wine 1.8 or newer, SSE2-capable CPU or ARM / ARM64 (installer)
- Windows 10 21H2 / Wine 1.8 or newer, SSE2-capable CPU (32-bit portable)
- Windows 10 21H2 / Wine 1.8 or newer, 64-bit CPU (64-bit portable)
- Windows 10 21H2 or newer, ARM CPU (portable)
- Windows 10 21H2 or newer, 64-bit ARM CPU (portable)
- Windows 7 SP 1 / Wine 1.8 or newer, SSE2-capable CPU (32-bit portable)
- Windows 7 SP 1 / Wine 1.8 or newer, 64-bit CPU (64-bit portable)

### Retro

Experimental builds with reduced functionality for older systems (*OpenMPT-RETRO*)

These builds work on Windows XP and Windows Vista, as well as in Wine on macOS.

- Windows XP / Wine 1.8 or newer, i586 class CPU (installer)
- Windows XP / Wine 1.8 or newer on macOS, x86 i586 class CPU (32-bit portable)
- Windows XP x64 / Wine 1.8 or newer on macOS, 64-bit CPU (64-bit portable)

### Legacy

Older releases of OpenMPT can be found in the release archive. If you found a bug in the current version or have other issues that prevent you from upgrading, please don't just go back to using an old version - report the bug so that we can actually fix it.

- The last official version of OpenMPT supporting *Windows XP* and *Windows Vista* is OpenMPT 1.28.10.00. See above for experimental newer builds.
- The last version of OpenMPT supporting *Wine 1.6* is OpenMPT 1.27.11.00.
- The last version of OpenMPT supporting *Windows 98 SE, Windows ME* (both with *KernelEx* and all updates installed), Windows 2000, and Wine 1.0 is OpenMPT 1.26.14.00.
- The last version of OpenMPT supporting *Windows 98 SE and Windows ME natively* is OpenMPT 1.18.03.00.

Additional information about running OpenMPT on older systems can be found in this [forum thread](https://forum.openmpt.org/index.php?topic=6188.0).

## Terminal / Command-line player

openmpt123 is a cross-platform command-line or terminal based module file player.

- download from the release pages linked at **https://lib.openmpt.org/libopenmpt/** or the news/updates page at https://lib.openmpt.org/libopenmpt/news/

Find the "Binary download links" section on the version release news page and download from the available compiled executable releases for supported systems / platforms for a particular version of openmpt123...

For example, [libopenmpt 0.7.8 release (2024-06-09)](https://lib.openmpt.org/libopenmpt/2024/06/09/security-update-0.7.8-releases-0.6.17-0.5.31-0.4.43/) includes **openmpt123** player and a plugin for XMPlay, for the following systems:
- Windows 10 21H2 / Windows 7 SP1
- Windows XP SP1
- Windows 98 with KernelEx compatibility layer and updates installed
- Windows 95 / 98SE / ME native systems
- DOS 5 (which may also work with the latest version of FreeDOS)

- Also available for download are **source code** archives which could possibly compile on other systems, for which executables are not provided for download...
- **Development library** downloads are available as well, for using the libopenmpt library with other software projects on various platforms. The libopenmpt 0.7.8 downloads include these for Windows 10 21H2 / Windows 7 SP1, Windows XP SP1, and WebAssembly / Javascript
- **Documentation** for these releases can also be downloaded.

- Linux distributions - openmpt123 can be found via the package managers of various Linux systems (distributions), e.g. Arch Linux, Debian Linux...


## OpenMPT library

- see https://lib.openmpt.org/libopenmpt/

- libopenmpt is a cross-platform C++ and C library to decode tracked music files (modules) [wikipedia] into a raw PCM audio stream.
- libopenmpt is based on the player code of the OpenMPT project (Open ModPlug Tracker). In order to avoid code base fragmentation, libopenmpt is developed in the same source code repository as OpenMPT.
- libopenmpt ships with a **plugin for XMPlay**, xmp-openmpt.
- libopenmpt also provides a **compatibility layer** implementing the libmodplug interface on top of libopenmpt in the libopenmpt-modplug package.
- libopenmpt also did provide **plugins** for **Winamp** (in_openmpt) and foobar2000 (foo_openmpt) is the past. These are now **deprecated** in favour of WinAMP or WACUP which both provide their own plugin based on libopenmpt, and foo_openmpt54 which is a fork of foo_openmpt, respectively.

For a large list of other software (distribution packages, player plugins, media framework support, and language bindings), see our [Wiki page](https://wiki.openmpt.org/Libopenmpt).


## License

The OpenMPT/libopenmpt project is distributed under the *BSD-3-Clause* License.
See [LICENSE](LICENSE) for the full license text.

**Note:** Files below the `include/` (external projects) and `contrib/` (related assets
not directly considered integral part of the project) folders may be subject to
other licenses. See the respective subfolders for license information. These
folders are not distributed in all source packages, and in particular they are
not distributed in the Autotools packages.


## How to compile / build

### OpenMPT

 -  Supported Visual Studio versions:

     -  Visual Studio 2019, and 2022 Community/Professional/Enterprise

        To compile the project, open `build/vsVERSIONwin7/OpenMPT.sln` (VERSION
        being 2019, or 2022) and hit the compile button. Other target systems
        can be found in the `vs2019*`, and `vs2022*` sibling folders.

        Note that you have to build the `PluginBridge` and `PluginBridgeLegacy`
        projects manually for architectures other than the one you are building
        OpenMPT for, as Visual Studio only builds one architecture configuration
        at a time.

        Please note that we do not support building with a later Visual Studio
        installation with an earlier compiler version. This is because, while
        later Visual Studio versions allow installing earlier compilers to be
        available via the later version's environment, in this configuration,
        the earlier compiler will still use the later C and C++ runtime's
        headers and implementation, which significantly increases the matrix of
        possible configurations to test.

     -  Visual Studio 2017 XP targeting toolset

 -  OpenMPT requires the compile host system to be Windows 8.1 or later on
    amd64 for VS2019 and VS2017, Windows 10 or later on amd64 for VS2022, or
    Windows 11 or later ARM64.

 -  In order to build OpenMPT **for Windows XP**, the Visual Studio 2017 XP 
    targeting toolset as well as the Windows 8.1 SDK need to be installed. The
    SDK is optionally included with Visual Studio 2017, but must be separately
    installed with later Visual Studio versions.

    The Windows 8.1 SDK is available from
    <https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/> or
    directly from
    <https://download.microsoft.com/download/B/0/C/B0C80BA3-8AD6-4958-810B-6882485230B5/standalonesdk/sdksetup.exe>
    .

 -  Microsoft Foundation Classes (MFC) are required to build OpenMPT.

### libopenmpt and openmpt123

openmpt123

- Live sound output requires one of the following libraries:
  - PulseAudio
  - SDL 2
  - PortAudio v19
  - Win32
  - liballegro 4.2 on **DJGPP/DOS**
- Rendering to PCM audio files can use these libraries (optional dependencies):
  - FLAC 1.2 or higher
  - libsndfile
  - Win32 for WAVE
  - raw PCM has no external dependencies
- help2man is required to build the documentation (optional).

See [Dependencies](doc/libopenmpt/dependencies.md) and
[Getting Started](doc/libopenmpt/gettingstarted.md) for more details about dependencies of tools and libraries required to build libopenmpt and the openmpt123 textual player application.

- Basically any C++20 or C++17 compliant compiler can be used to **build** libopenmpt.
- To **use** libopenmpt in a software project
  - any C89 / C99 / C11 / C17 compatible compiler should work with the C API as long as a C99 compatible stdint.h is available
  - any C++20 or C++17 compatible compiler should work with the C++ API
- J2B support requires an inflate (deflate decompression) implementation:
  - zlib (or miniz can be used internally)
- MO3 support requires:
  - libmpg123 >= 1.14.0 (or minimp3 can be used internally)
  - libogg, libvorbis, and libvorbisfile (or stb_vorbis can be used internally)
- Building on Unix-like systems requires:
  - GNU make
  - pkg-config
- The Autotools-based build system requires:
  - pkg-config 0.24 or higher
  - zlib
  - doxygen



## Contributing to OpenMPT/libopenmpt

See [contributing](doc/contributing.md).

