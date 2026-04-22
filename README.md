# b3sh - Be Free Shell.

# b3sh – A Custom Linux Shell

`b3sh` is a simple interactive UNIX command line interpreter written in C++.  
It implements core shell features like process execution, pipelines, raw input mode, persistent command history, and tab completion.  
This project was built to gain a deep understanding of system calls, terminal handling, and process management in Linux.

## Features

- **Interactive prompt** with custom `b3sh> ` display
- **Raw terminal input mode** – reads keystrokes directly for full control
- **Line editing** – left/right arrow navigation, backspace support
- **Command history** – navigate with up/down arrows, saved to `~/.b3sh_history`
- **Tab completion** for built-in commands and executables in `PATH`
- **Pipeline support** – chain commands using `|`
- **Built-in commands:** `cd`, `pwd`, `export`, `exit`
- **Signal handling** – `Ctrl+C` clears the current line, `Ctrl+D` exits

## Requirements

- C++20 compiler
- CMake 3.16 or newer
- Linux (uses POSIX system calls and terminal I/O)

## Build

```bash
git clone https://github.com/llwizard1024/b3sh.git
cd b3sh
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Examples
```bash
b3sh> pwd
/home/user
b3sh> cd /tmp
b3sh> ls -l | grep test | wc -l
b3sh> pw<Tab>        # completes to `pwd`
b3sh> <Up arrow>     # browse previous commands
b3sh> exit
```

## Project structure
```
b3sh/
├── CMakeLists.txt
├── include/b3sh/
|   |── commands/       # Builtin commands
│   ├── handlers/       # Command execution and builtins
│   ├── terminal/       # Raw mode, input handling, completion
│   └── utils/          # Helpers
├── src/
│   ├── main.cpp
|   |── commands/
│   ├── handlers/
│   ├── terminal/
│   └── utils/
└── README.md
```
