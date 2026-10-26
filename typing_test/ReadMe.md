# Typing Speed Test Analyzer

## Overview
This C++ program reads a typing pattern and user-typed files to analyze typing speed and accuracy.  
It uses linked lists to store words and calculates:

- Typing accuracy (% of correctly typed words)
- Typing speed (words per second)
- Words incorrectly typed by the user with the most mistakes

## How to Use
1. Prepare `pattern.txt` and user typed text files (`1.txt`, `2.txt`, …).
2. Compile the program:
g++ typing_test.cpp -o typing_test

markdown
Copy code
3. Run:
./typing_test

markdown
Copy code
4. Follow the prompts to enter user IDs, typing times, and filenames.

## File Structure
- `pattern.txt` – Reference text
- `1.txt` – User typed text
- `typing_test.cpp` – Source code