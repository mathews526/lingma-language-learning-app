# Lingma English-Language-Learning-SRS

For English language learners and students who desire strong retention and efficient learning of English language skills, our product is a language learning and study tool that specializes in spaced repetition, a study technique that is scientifically-proven to be effective for learning. It will aid in retention of basic English language skills.

Open Lingma.sln in Visual Studio, and use F5 to build the executable file.

If accessing through a zip, find the executable through the Lingma folder.

## Getting Started

### Prerequisites
Download and extract [SFML 3.0.2 for Visual C++](https://www.sfml-dev.org/download/sfml/3.0.2/).

### Installation

1. Clone the repo
```bash
   git clone https://github.com/mathews526/sfml-minesweeper.git
```
2. **Open the project:**
   Open `Lingma.sln` in Visual Studio.
3. **Configure SFML Paths:**
   Right-click the project in **Solution Explorer** and select **Properties**:
   - **C/C++ > General > Additional Include Directories**: Add the path to your SFML `include/` folder (e.g., `C:\SFML-3.0.2\include`).
   - **Linker > General > Additional Library Directories**: Add the path to your SFML `lib/` folder (e.g., `C:\SFML-3.0.2\lib`).
4. **Build & Run:**
   Select your build configuration (**Debug** or **Release**) and build the project (`F5`).

> **Note on Static Linking:** This project links SFML statically (`SFML_STATIC`). The library code is compiled directly into the executable using static libraries (`sfml-*-s.lib`) and native Windows dependencies (`opengl32.lib`, `winmm.lib`, `gdi32.lib`). **No SFML `.dll` files are required in the output folder to run the application.**
