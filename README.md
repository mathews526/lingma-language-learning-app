# Lingma: English Language Learning SRS
 
A desktop language-learning app for English learners that uses a **spaced repetition system (SRS)** to build long-term retention of basic English vocabulary. Words you know well come back less often, and words you struggle with come back sooner, so study time goes where it matters most.
 
**What makes Lingma different:** the app uses only images and audio, with no written words. Learners hear each English word and connect it directly to a picture of an object or action, the way people learn their first language. Because nothing depends on reading, the app is accessible to learners of any background or native language, including those who cannot yet read English.
 
Built in **C++** with **SFML** as a four-person team project for CEN3031, Spring 2026.

## Getting Started

### Prerequisites
Download and extract [SFML 3.0.2 for Visual C++](https://www.sfml-dev.org/download/sfml/3.0.2/).

### Installation

1. Clone the repo
```bash
   https://github.com/mathews526/lingma-language-learning-app.git
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
