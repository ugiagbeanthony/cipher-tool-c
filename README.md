# cipher-tool-c
A safe substitution cipher implemented in C with strict file‑handling rules to prevent accidental overwrites. Supports encryption and decryption using a validated 26‑character key as a command-line argument.

## Usage

Compile:
    gcc cipher.c -o cipher

Run:
    ./cipher <26-character-key>

Example:
    ./cipher qwertyuiopasdfghjklzxcvbnm

## Features
- Validates key (must be 26 unique alphabetic characters)
- Encrypts or decrypts text files
- Prevents accidental overwrite (input and output file cannot be the same)
- Optional deletion of original file after processing
- Handles uppercase and lowercase correctly
- Safe file handling (binary mode)

## future improvements
- support for same-name file overwrite
