# WinSize

**WinSize** is a lightweight C++ console utility that detects and displays the terminal (console) window size in real-time. It also includes tools for console manipulation, such as clearing the screen, printing centered text within borders, and displaying system information in a visually structured format.


---

## ✨ Features

- Detect and display terminal window size (width and height)
- Cross-platform support: Windows, Linux, macOS
- Clean and centered output with dynamic border rendering
- Simple console clearing functionality
- System platform detection (e.g., Linux, macOS, Windows 64-bit)
- Compatible with GCC and Clang (C++11 and later)
- Designed for 64-bit CPUs (Intel, AMD)

---

## 📦 Build & Run

### 🔧 Requirements

- C++11 or later
- GCC (8–15) or Clang/LLVM (8+)
- CMake (optional)
- Make or Ninja (optional)

### 🧱 Build with Make

```bash
make
./build/console_app
```

### 🔨 Build with Ninja

```bash
ninja -f build.ninja
./build/console_app
```

### 🛠️ Build Manually

```bash
g++ -std=c++17 -m64 -Iinclude src/main.cpp src/Console.cpp -o console_app
./console_app
```

---

## 📂 Project Structure

```
WinSize/
├── include/
│   └── Console.h
├── src/
│   ├── Console.cpp
│   └── main.cpp
├── build/              # Generated build files
├── Makefile
├── build.ninja
└── README.md
```

---

## 📋 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙋‍♀️ Why Use WinSize?

If you’re writing terminal-based tools or want to dynamically adjust output to match the terminal size, WinSize gives you a head start with a clean interface and reliable cross-platform behavior.

---

## 🤝 Contributing

Pull requests are welcome! If you have suggestions for improvements or additional features (like color support or interactive resizing), open an issue or start a discussion.

---

## 🧠 Author

Gregory Bowne <https://github.com/gbowne1>
