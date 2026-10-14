# Lingma: English Language Learning SRS
 
A desktop language-learning app for English learners that uses a **spaced repetition system (SRS)** to build long-term retention of basic English vocabulary. Words you know well come back less often, and words you struggle with come back sooner, so study time goes where it matters most.
 
Unlike typical flashcard apps, Lingma uses only images and audio, with no written words. Learners hear each English word and connect it directly to a picture of an object or action, the way people learn their first language. Because nothing depends on reading, the app is accessible to learners of any background or native language, including those who cannot yet read English.
 
Built in **C++** with **SFML** as a four-person team for CEN3031, Spring 2026.

(put GIF here)

## Features
 
- **Image and audio only, no text**: words are taught through pictures and spoken audio rather than written definitions or translations. This makes the app usable by anyone and builds a direct link between the sound of a word and the object or action it names.
- **Spaced repetition engine**: every word is a card with an SRS level from 0 to 5, and new words start at level 0. Rate a card green to move it up a level, yellow to keep it at its level, or red to move it down. The rating also determines how soon the card reappears.
- **Lesson screen**: pairs each word's image with its audio pronunciation so you learn to associate the sound with the picture. Moving on from a lesson activates the word so it becomes available for review.
- **Review screen**: quizzes you on words you have already learned, with no audio hint so you push your recall. Each rating and its timestamp is saved to your progress file.
- **Progress dashboard**: six boxes show how many cards sit at each SRS level, plus a progress bar showing how close you are to mastering every card. It updates live as cards level up.
- **Learning goals**: set a word target for your session using a row of stars (one star equals one word) and confirm it with Enter. A progress bar and the stars fill in as you rate words green in review, and the bar turns green when you hit your goal.
- **User profiles**: create a profile or log in from the login screen. Text boxes accept alphanumeric characters only, and duplicate usernames are blocked.
- **Persistent progress**: SRS levels, review history, and learning goals are saved per user to local files, so progress is restored when you log back in.

## Built With

- C++17 (or higher)
- SFML 3.0.2 (rendering, input, and window management)

## Getting Started

### Prerequisites
- Windows with Visual Studio
- Download and extract [SFML 3.0.2 for Visual C++](https://www.sfml-dev.org/download/sfml/3.0.2/).

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

## Architecture
 
- **Screen-based design**: a `Screen` parent class holds shared logic, and screens such as `MainMenu`, `UserSelect`, `LessonScreen`, and `ReviewScreen` derive from it. An `AppState` struct carries shared state between screens.
- **Reusable UI components**: `Button`, `ImageButton`, and `Textbox` classes, with a `TextureManager` for loading and caching textures. Images and audio use SFML's texture, sprite, and sound buffer classes.
- **Local file persistence**: each user's progress and review timestamps are saved to text files in the `data` folder, and all users' learning goals are stored together in a single separate file.
