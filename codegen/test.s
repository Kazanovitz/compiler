
.text    
.LC0:
       .string "%d\n"
       
.globl  Print
Print:
       pushl   %ebp
       movl    %esp, %ebp
       movl    20(%ebp), %eax
       pushl   %eax
       pushl   $.LC0
       call    _printf
       leave
       ret

# Start Function
.globl _Start
_Start:
        pushl   %ebp 
        movl    %esp, %ebp
        subl    $8, %esp
        pushl   $10
        subl    $12, %esp
        call    Print
        leave
        ret

#### METHOD IMPLEMENTATION
_Program_mult:
 pushl %ebp
 movl %esp , %ebp
 subl $20, %esp
 movl 20(%ebp) , %eax
 movl %eax , -4(%ebp)
 movl 16(%ebp) , %eax
 movl %eax , -8(%ebp)
 movl 12(%ebp) , %eax
 movl %eax , -12(%ebp)
 movl 8(%ebp) , %eax
 movl %eax , -16(%ebp)
#### MINUS
#### ADD
 movl -4(%ebp) , %eax
 pushl %eax
#### TIMES
 movl -8(%ebp) , %eax
 pushl %eax
 movl -12(%ebp) , %eax
 pushl %eax
 popl %ebx
 popl %eax
 imull %ebx, %eax
 pushl %eax
 popl %ebx
 popl %eax
 addl %ebx, %eax
 pushl %eax
 movl -16(%ebp) , %eax
 pushl %eax
 popl %ebx
 popl %eax
 subl %ebx, %eax
 pushl %eax
 movl %eax , -20(%ebp)
 movl -20(%ebp) , %eax
 pushl %eax
 leave
 ret
#### METHOD IMPLEMENTATION
_Program_look:
 pushl %ebp
 movl %esp , %ebp
 subl $4, %esp
#### SELF CALL
#### PRIMITIVE 
 movl $1, %eax
 pushl %eax
#### PRIMITIVE 
 movl $2, %eax
 pushl %eax
#### PRIMITIVE 
 movl $3, %eax
 pushl %eax
#### PRIMITIVE 
 movl $4, %eax
 pushl %eax
call Program_mult
addl $16 , %esp
 movl %eax , -4(%ebp)
 movl -4(%ebp) , %eax
 pushl %eax
 leave
 ret
#### METHOD IMPLEMENTATION
_Program_start:
 pushl %ebp
 movl %esp , %ebp
 subl $0, %esp
 leave
 ret