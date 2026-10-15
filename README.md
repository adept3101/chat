# POSIX Sockets Chat

A lightweight TCP chat application written in **C**, built with POSIX sockets and POSIX threads.

The project implements client and server functionality, along with a logging system. It is designed for Linux and macOS and uses a `Makefile` for building.

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey.svg)
![Networking](https://img.shields.io/badge/networking-TCP-orange.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## Features

- **TCP networking** — communication using POSIX sockets.
- **Client and server** — both sides of the chat application are implemented.
- **Multithreading** — POSIX threads (`pthreads`) for concurrent operations.
- **Logging system** — logging functionality for application events.
- **Simple build process** — compile the project using the provided `Makefile`.
- **Cross-platform support** — intended for Linux and macOS.

## Requirements

Before building, make sure you have:

- A C compiler, such as GCC or Clang.
- GNU Make or a compatible `make` utility.
- A Linux or macOS environment.
- POSIX threads and socket APIs.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/adept3101/chat.git
cd chat
```

### 2. Build the project

```bash
make
```

The build process is managed by the provided `Makefile`.

### 3. Run the application

After building, run the generated client and server executables according to the targets and instructions defined in the project.

> **Note:** Exact executable names and launch commands can be added here once the build targets and command-line arguments are documented.

## Project Structure

The project contains the client, server, networking, and logging functionality. See the source files and `Makefile` for the current implementation details.

## Technologies

| Technology | Purpose |
| --- | --- |
| C | Core implementation |
| POSIX sockets | TCP communication |
| POSIX threads | Multithreading |
| Make | Build automation |

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Made with C by [adept3101](https://github.com/adept3101).
