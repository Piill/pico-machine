# This program fills the stack with the Stack depth and the Stack pointer
# until a stack overflow occours. At this point the virtual machine should handle the exception and halt execution.
loop
PUSH 56
PUSH 93
PUSH 93
ADD
ADD
LOAD
PUSH 55
PUSH 93
PUSH 93
ADD
ADD
LOAD
PUSH loop
JUMP
