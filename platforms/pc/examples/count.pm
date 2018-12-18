# This programs enables interactive execution and counts to 10
PUSH 0
SYSCALL
PUSH 0
loop
PUSH 1
ADD
DUP
# Test if equals
PUSH 10
EQUALS
NOT
PUSH loop
IF
POP
EXIT


