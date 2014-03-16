# CS 160 Simple Testbed
# Winter 2014
# Do not distribute
#
#
# Don't modify any code before the
# comment "Your code starts here."
#

.text

#### METHOD IMPLEMENTATION

#### METHOD IMPLEMENTATION
_Program_mult:
 pushl %ebp
 movl %esp , %ebp
 subl $4, %esp
#### PRIMITIVE 
 movl $1, %eax
 pushl %eax
 popl %eax
 leave
 ret
#### METHOD IMPLEMENTATION
_Program_test:
 pushl %ebp
 movl %esp , %ebp
 subl $4, %esp
#### PRIMITIVE 
 movl $5, %eax
 pushl %eax
 leave
 ret

.globl _Tester
_Tester:
  # pushl %ebp
  # movl  %esp, %ebp
  # pushl 8(%ebp)
  # pushl 12(%ebp)
  
  # 
  # Your code starts here.
  # Parameters 1 and 2 are on the
  # stack. Param 2 is on the top,
  # param 1 is below it.
  # 
  # The code below simply adds the
  # two parameters, and pushes the
  # result. Replace with your code.
  # 

pushl %ebp
 movl %esp , %ebp
 subl $8, %esp
#### ASSIGNMENT
#### PRIMITIVE 
 movl $100, %eax
 pushl %eax
 movl %eax , -8(%ebp)
#### ASSIGNMENT
#### AND
#### PRIMITIVE 
 movl $1, %eax
 pushl %eax
#### PRIMITIVE 
 movl $1, %eax
 pushl %eax
 popl %ebx
 popl %eax
 andl %ebx, %eax
 pushl %eax
 movl %eax , -4(%ebp)
#### IF Statemet
 movl -4(%ebp) , %eax
 pushl %eax
 popl %eax
 movl $0 , %ebx
 cmp %eax, %ebx
 je skip_0
#### ASSIGNMENT
#### PRIMITIVE 
 movl $5, %eax
 pushl %eax
 movl %eax , -8(%ebp)
 skip_0: 
 movl -8(%ebp) , %eax
 pushl %eax
 leave
 ret

 
# #### METHOD IMPLEMENTATION
# _Program_start:
#  pushl %ebp
#  movl %esp %ebp
#  subl $0 %esp
#  leave
#  ret
  # 
  # Your code ends here.
  # Leave the return value on the
  # stack, and it will be printed.
  # 
  # Don't modify anything below this.
  # 
  
  # popl  %eax
  # leave
  # ret