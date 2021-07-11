@
@ Copyright 2021 Gerardo Ospina, ngospina@gmail.com
@
.globl _start
_start:
    mov sp,#0x8000
    bl kernel
loop: b loop
