# pico-Machine
pico-Machine is designed to be a minimal, stack based virtual machine, using only printable characters for the machine code, meaning that compiled code can be distributed via SMS, twitter and postcard.

For a detailed overview see the [documentation](./docs/README.md)

It is incomplete for made for fun, so don't go putting it into anm expensive rocket just yet.

# Project structure
`docs` contains all the documentation for the project, `core` contains the src for the core implementation, `assembler` contains the source for the assembler and `example` contains an example program using the core implementation.

# Example programs
If you want to see the full source, simply look in the examples folder, here you will also find a program able to run them in your terminal.

If you just want to the machine code, here it is:

Count to 10: `!!!"&#!+02!#1"!!3`

Fibonacci: `!!!"#!B$-%&!B,$#!]##!V&&&02!%1!B3`
