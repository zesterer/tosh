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

## Syntax

```

# Double quotes are counted as a string
echo "Hello, there!"

# Brackets are evaluated as a command expansion, unless prefixed by a '\'
echo "My name is {whoami}, not \{whoami\}"

```
