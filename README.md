# Legion K Player (Full Version)

Legion K Player is a high-performance Android-style emulator frontend and virtual machine core. It is a full-featured emulator inspired by professional solutions, developed by **DEMO X HEXA** (Death Legion Team).

## Live Deployment
Visit the official **Legion K Player Landing Page** for downloads and information:
[**Download & Web Portal**](https://deathlegionteamlk.github.io/Legion-K-Player/) 

## Features
- **Polished UI**: A complete SDL2-based graphical interface with a sleek blue theme.
- **K-Engine Core**: A custom register-based Virtual Machine designed for high-speed bytecode execution.
- **Full Sidebar**: Interactive controls for Home, Back, and Settings.
- **App Dashboard**: A stylized app drawer with responsive icons.
- **Automated Builds**: Pre-compiled binaries available for Linux and Windows.

## Project Structure
- `src/`: Core implementation files.
- `include/`: Header definitions for the K-Engine and UI system.
- `web/`: Landing page and download portal.
- `assets/`: Resources for the player.

## Downloads
Built binaries (Linux and Windows `.exe`) are available as artifacts in the **GitHub Actions** tab after every build.

## How to Build
### Linux
Ensure you have `libsdl2-dev`, `libsdl2-image-dev`, and `libsdl2-ttf-dev` installed.
```bash
make
```

### Windows (Cross-Compile)
Ensure you have `g++-mingw-w64-x86-64` installed.
```bash
make win
```

## How to Run
```bash
./Legion-K-Player-Bin
```

### Test Mode (CLI)
To verify the VM engine logic without a GUI:
```bash
./Legion-K-Player-Bin --test
```

## Development
This project follows strict coding guidelines:
- **No Comments**: Pure, readable code as per the Legion K Player specification.
- **Zero Overhead**: Minimal dependencies for maximum performance.

---
Built with 💙 by **DEMO X HEXA** | Death Legion Team
