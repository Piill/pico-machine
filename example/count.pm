start
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


