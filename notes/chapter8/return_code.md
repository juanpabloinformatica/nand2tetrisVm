# Return code

# To translate

- FRAME = LCL
As FRAME is a temp variable
I can use general pourpose registers
(13 Or 14)
//[2] LCL
// FRAME variable is register 13
@2
D=M
@13
M=D
- RET = *(FRAME-5)
As is a pointer I need to access to the
value pointed to frame - 5
so in other words I calculate
the address and then dereference it,
besides as RET is a temporary variable
I will use (register 14)
@5
D=A
@13
M=M-D
A=M
D=M
@14
M=D

- *ARG = pop()
so I need to calculate pop
and put in the memory address pointer
by ARG
*ARG =
@3
A=M
M=x
pop()=
@0
M=M-1
A=M
D=M
x has to be replaced by pop()
@0

- THAT = *(FRAME-1)
Considering FRAME as register 13
THAT=
@4
M=x
*(FRAME-1)=
@1
D=A
@13
M=M-D
A=M
D=M










