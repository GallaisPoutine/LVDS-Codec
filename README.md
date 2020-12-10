# LVDS Codec

This binary is used to quickly translate a LVDS frame into coressponding
registers and reciprocally.

## How to build

To compile the C part of the source code (which is the only reliable source
code on this repo), just using GNU C Compiler is a solution since there is
only two files.

```
gcc -static -DDSKW_TOGGLE main.c -o lvds
```

"-static" flag is optional, it is only required to be free from dependencies.

## How to use

Registers must be specified in hexadecimal with capital letters and a 8
padding to the left, otherwise it will not work.

```
./lvds lsbregister msbregister
```

Example :
```
./lvds 0x000FFFDE 0x00007BDF
```
