# TOSH

TOSH (Thoth Official SHell) is a shell designed to operate on POSIX systems. It is simple and lightweight, providing few features beyond the basic functionality you would expect from a shell.

## Getting a copy

```
git clone https://www.github.com/zesterer/tosh.git
```

## Building

```
cd tosh
./setup.sh
tup build-default
```

## Running

```
./build-default/tosh
```

## Example

```
Welcome to TOSH!
10:52:41
joshua@/home/joshua/Documents/Projects/tosh$ echo "TOSH supports basic expression expansion!"
TOSH supports basic expression expansion!
10:52:56
joshua@/home/joshua/Documents/Projects/tosh$ echo "{tput setaf 6}Here's how!"
Here's how!
10:53:17
joshua@/home/joshua/Documents/Projects/tosh$
```

## Syntax

```

# Double quotes are counted as a string
echo "Hello, there!"

# Brackets are evaluated as a command expansion, unless prefixed by a '\'
echo "My name is {whoami}, not \{whoami\}"

```
