#start
PUSH 0
PUSH 1
#loop begin
loop
DUP
#Save value for later
PUSH val
SWAP
STORE
#Add values
OVER
ADD
#Load saved value
PUSH val
LOAD
SWAP
# Is the last value reached?
# Note: 233 is too large to be a literal, so we need to calculate it
DUP
PUSH 60
DUP
DUP
PUSH 53
ADD
ADD
ADD
EQUALS
NOT
#loop end
PUSH loop
IF
EXIT
val
