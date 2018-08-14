# Overview
Pico-machine is a stack based virtual machine, with the goal of having a simple implementation and using a machine language that is representable using only distinguishable, non-whitespace, printable characters.
This means that all instructions and literals in the machine language is restricted to values from 0 to 93, but the machine operates internally using 8 bits.

# Memory layout
The memory uses a word-size of 8 bits, and is word addressable. 
Most of the memory, called program memory, is used to store the program, and can be further used to general purpose storage.
The rest of the memory is used for special values and memory mapped IO.

| Address | Description |
|---------|------------|
| `0x00` - `0xEF`| Program memory |
| `0xF0` | PC |
| `0xF1` | Stack depth |
| `0xF2` | SP | 
| `0xF3` | Std in |
| `0xF4` | std out |
| `0xF5` - `0xFF` | Reserved for memory mapped IO |


# The stack
The stack is guaranteed to have a minimum depth of 254. A stack overflow should terminate the program immediately.

# Instruction set
`N1` denotes the top of the stack, `N2` denotes the second value on the stack.
All values used by an instruction are removed from the stack, unless otherwise noted, and the result is always put on the top of the stack.
The value 0 and 1 is used to represent false and true, respectively.

| Name	|Assembler | ASCII |	Description |
|-------|-------|----------|---------------|
| Push	|	|!| Puts the next program-memory value on top of the stack, and advance PC by one.	|
| Pop	|	|"| Removes the `N1` from the stack |
| Dup	|	|#| Duplicates `N1`	|
| Swap	|	|$| Swaps the `N1` and `N2`	|
| Over	|	|%| Puts a duplicate of `N2` on top of the stack	|
| Add	|	|&| Adds `N1` and `N2` |
| Sub	|	|'| Subtracts `N2` from `N1` |
| Or	|	|(| Bitwise or |
| Xor	|	|)| Bitwise xor |
| And	|	|*| Bitwise and |
| Ones' complement	|	|+| Bitwise negation	|
| Load  |	|,| Reads the address denoted by `N1` |
| Store |	|-| Stores `N1`, at the address of `N2`	|
| Greater|	|.| `N1` > `N2`	|
| Less 	|	|/| `N1` < `N2`	|
| Equals|	|0| `N1` = `N2`	|
| If	|	|1| If `N2` is 0, jump to `N1`, if not, continue. `N1` is removed from the stack, regardless of the value of `N1` |
| Not	|	|2| If `N1` is 0, push 1 onto the stack, otherwise push 0 |
| Jump	|	|3| Jump to address `N1`	|
| SysCall|	|4| Makes a system call. This is implementation dependant. |
