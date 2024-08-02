# Project 1 - Text Processing

# KeyFilter

KeyFilter is a program that emulates the algorithm for enabling and disabling keys on a virtual keyboard in a car's dashboard navigation system. The navigation system has a database of addresses and expects input from the user via the virtual keyboard. The goal of KeyFilter is to make the input easier for the user by only allowing selected keys on the keyboard at any given moment - those keys that, when used, would still lead to a known address.

## Description

Imagine a virtual keyboard in a car's dashboard navigation system. The navigation system has a database of addresses and expects input from the user via the virtual keyboard. To make the input easier for the user, only selected keys are allowed on the keyboard at any given moment - those keys that, when used, would still lead to a known address. For example, the navigation system knows the cities Brno, Beroun, and Bruntál. If the user has already entered the letters "BR," only the keys "N" (leading to "Brno") and "U" (leading to "Bruntál") will be allowed.

## Usage

The program should be implemented in a single source file named `keyfilter.c`. Input data will be read from standard input (stdin), and output will be printed to standard output (stdout).

### Compilation and Execution

To compile the program, use the following command:

```
$ gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter
```

To execute the program, use the following command:

```
$ ./keyfilter ADDRESS <file.txt
```

If the program is run without arguments, it takes the entered address as an empty string.

## Input Address Database

The address database consists of text data where each line represents one address. Each line contains a maximum of 100 characters. The list of addresses is unordered. All data is case insensitive. The program must support at least 42 addresses.

## Program Output

The program's output can be one of three types:

1. **Address Found**

    Found: S

    This output is printed if the database contains a single address `S` whose prefix matches the user-entered address `ADDRESS`. (Note: the prefix `P` of the string `S` is a string where `S` starts with `P`).

2. **Address Requires Specification**

    Enable: CHARS

    If multiple addresses matching the given prefix `ADDRESS` are found in the database, the program prints a line formatted like this with the allowed characters `CHARS`. `CHARS` is an alphabetically sorted list of characters where, for each character `C`, there is an address in the database whose prefix matches the concatenation of the string `ADDRESS` with the character `C`.

3. **Address Not Found**

    Not found

