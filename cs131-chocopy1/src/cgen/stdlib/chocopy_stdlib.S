.option norelax
.globl const_6
const_6:
.word 3                                  # Type tag for class: str
.word 9                                  # Object size
.word $str$dispatchTable                 # Pointer to dispatch table
.word 17                                 # Constant value of attribute: __len__
.string "Operation on None"              # Constant value of attribute: __str__
.align 2
.globl const_0
const_0:
  .word 2                                  # Type tag for class: str
  .word 4                                  # Object size
  .word $bool$dispatchTable                # Pointer to dispatch table
  .word 0                                  # Constant value of attribute: __bool__
  .align 2
.globl const_1
const_1:
  .word 2                                  # Type tag for class: str
  .word 4                                  # Object size
  .word $bool$dispatchTable                # Pointer to dispatch table
  .word 1                                  # Constant value of attribute: __bool__
  .align 2
.globl const_7
const_7:
  .word 3                                  # Type tag for class: str
  .word 9                                  # Object size
  .word $str$dispatchTable                 # Pointer to dispatch table
  .word 16                                 # Constant value of attribute: __len__
  .string "Division by zero"               # Constant value of attribute: __str__
  .align 2
.globl const_5
const_5:
  .word 3                                  # Type tag for class: str
  .word 8                                  # Object size
  .word $str$dispatchTable                 # Pointer to dispatch table
  .word 13                                 # Constant value of attribute: __len__
  .string "Out of memory"                  # Constant value of attribute: __str__
  .align 2
.globl const_8
const_8:
  .word 3                                  # Type tag for class: str
  .word 9                                  # Object size
  .word $str$dispatchTable                 # Pointer to dispatch table
  .word 19                                 # Constant value of attribute: __len__
  .string "Index out of bounds"            # Constant value of attribute: __str__
  .align 2
.globl const_2
const_2:
  .word 3                                  # Type tag for class: str
  .word 9                                  # Object size
  .word $str$dispatchTable                 # Pointer to dispatch table
  .word 16                                 # Constant value of attribute: __len__
  .string "Invalid argument"               # Constant value of attribute: __str__
  .align 2
.globl const_4
const_4:
  .word 3                                  # Type tag for class: str
  .word 6                                  # Object size
  .word $str$dispatchTable                 # Pointer to dispatch table
  .word 5                                  # Constant value of attribute: __len__
  .string "False"                          # Constant value of attribute: __str__
  .align 2
.globl const_3
const_3:
  .word 3                                  # Type tag for class: str
  .word 6                                  # Object size
  .word $str$dispatchTable                 # Pointer to dispatch table
  .word 4                                  # Constant value of attribute: __len__
  .string "True"                           # Constant value of attribute: __str__
  .align 2
.globl $input
$input:
# Function input
addi sp, sp, -16 # Reserve stack
sw ra, 12(sp) # Save registers
sw fp, 8(sp)
sw s1, 4(sp)
addi fp, sp, 16 # Set fp
la a0, $str$prototype # EOF: Return empty string.
call myscanf
lw t1, 12(a0) # Restore registers
bne t1, zero, input_done # Go to the end
la a0, $str$prototype # EOF: Return empty string.
j input_done
input_done:
lw s1, -12(fp)
lw ra, -4(fp)
lw fp, -8(fp)
addi sp, sp, 16
jr ra
.globl $len
$len:
# Function len
# We do not save/restore fp/ra for this function
# because we know that it does not use the stack or does not
# call other functions.
beq a0, zero, len_12 # None is an illegal argument
lw t0, 0(a0) # Get type tag of arg
li t1, 3 # Load type tag of `str`
beq t0, t1, len_13 # Go to len(str)
li t1, -1 # Load type tag for list objects
beq t0, t1, len_13 # Go to len(list)
.globl $object.__init__
$object.__init__:
# Init method for type object.
mv a0, zero # `None` constant
jr ra # Return
.globl abort
abort:
# Runtime support function abort (does not return).
mv t0, a0 # Save exit code in temp
lui a0, %hi(error_char) # Load high bit of error_char
addi a0, a0, %lo(error_char) # Load low bit of error_char
call myprintf # Print error message
mv a1, t0 # Move exit code to a1
li a7, 93 # Code for exit2 ecall
ecall # Exit with code
abort_17: # Infinite loop
j abort_17 # Prevent fallthrough

error_char:
.asciz "%s\n"
.globl accend
accend:
# Runtime support function accend
beqz s1, .accend_2
.accend_1:
call exit
.accend_2:
addi sp, sp, -16
sw a0, 0(sp)
sw a1, 4(sp)
sw a2, 8(sp)
sw a3, 12(sp)
addi a1, zero, 4
.accend_3:
addi a1, a1, -1
beqz a1, .accend_4
addi sp, sp, -8
sw a1, 0(sp)
sw ra, 4(sp)
addi sp, sp, -4
mv a0, sp
jal wait
addi sp, sp, 4
lw a1, 0(sp)
lw ra, 4(sp)
addi sp, sp, 8
j .accend_3
.accend_4:
lw a0, 0(sp)
lw a1, 4(sp)
lw a2, 8(sp)
lw a3, 12(sp)
addi sp, sp, 16
mv s1, zero
ret
.globl accstart
accstart:
# Runtime support function accstart
mv fp, sp
add t1, zero, zero
lui t1, 1044480
add sp, sp, t1
add sp, sp, -12
sw a0, 0(sp)
sw a1, 4(sp)
sw a2, 8(sp)
sw a3, 12(sp)
mv a3, a7
addi a2, zero, 4
accstart_1:
addi a2, a2, -1
beqz a2, accstart_2
addi a7, zero, 120
addi a0, zero, 20
mv a1, sp
ecall
bnez a0, accstart_1
accstart_2:
mv tp, a2
mv a7, a3
lw a0, 0(sp)
lw a1, 4(sp)
lw a2, 8(sp)
lw a3, 12(sp)
add sp, sp, 12
add s1, zero, zero
lui s1, 4096
add sp, sp, s1
ret
.globl alloc2
alloc2:
# Runtime support function alloc2 (realloc).
# Prototype address is in a0.
# Number of words to allocate is in a1.
li a2, 4 # Word size in bytes
mul a2, a1, a2 # Calculate number of bytes to allocate
add a2, gp, a2 # Estimate where GP will move
bgeu a2, s11, alloc2_15 # Go to OOM handler if too large
lw t0, 4(a0) # Get size of object in words
mv t2, a0 # Initialize src ptr
mv t3, gp # Initialize dest ptr
alloc2_16: # Copy-loop header
lw t1, 0(t2) # Load next word from src
sw t1, 0(t3) # Store next word to dest
addi t2, t2, 4 # Increment src
addi t3, t3, 4 # Increment dest
addi t0, t0, -1 # Decrement counter
bne t0, zero, alloc2_16 # Loop if more words left to copy
mv a0, gp # Save new object's address to return
sw a1, 4(a0) # Set size of new object in words
mv gp, a2 # Set next free slot in the heap
jr ra # Return to caller
alloc2_15: # OOM handler
li a0, 5 # Exit code for: Out of memory
la a1, const_5 # Load error message as str
addi a1, a1, 16 # Load address of attribute __str__
j abort # Abort
.globl alloc
alloc:
# Runtime support function alloc.
# Prototype address is in a0.
lw a1, 4(a0) # Get size of object in words
j alloc2 # Allocate object with exact size
.globl concat
concat:
# Function concat
addi sp, sp, -32
sw ra, 28(sp)
sw fp, 24(sp)
addi fp, sp, 32
sw s1, -12(fp)
sw s2, -16(fp)
sw s3, -20(fp)
sw s4, -24(fp)
sw s5, -28(fp)
lw t0, 4(fp)
lw t1, 0(fp)
beqz t0, concat_none
beqz t1, concat_none
lw t0, 12(t0)
lw t1, 12(t1)
add s5, t0, t1
addi a1, s5, 4
la a0, $.list$prototype
jal alloc2
sw s5, 12(a0)
mv s5, a0
addi s3, s5, 16
lw s1, 4(fp)
lw s2, 12(s1)
addi s1, s1, 16
lw s4, 12(fp)
concat_1:
beqz s2, concat_2
lw a0, 0(s1)
jalr ra, s4, 0
sw a0, 0(s3)
addi s2, s2, -1
addi s1, s1, 4
addi s3, s3, 4
j concat_1
concat_2:
lw s1, 0(fp)
lw s2, 12(s1)
addi s1, s1, 16
lw s4, 8(fp)
concat_3:
beqz s2, concat_4
lw a0, 0(s1)
jalr ra, s4, 0
sw a0, 0(s3)
addi s2, s2, -1
addi s1, s1, 4
addi s3, s3, 4
j concat_3
concat_4:
mv a0, s5
lw s1, -12(fp)
lw s2, -16(fp)
lw s3, -20(fp)
lw s4, -24(fp)
lw s5, -28(fp)
lw ra, -4(fp)
lw fp, -8(fp)
addi sp, sp, 32
jr ra
concat_none:
j error.None
.globl error.Div
error.Div:
li a0, 2 # Exit code for: Division by zero
la a1, const_7 # Load error message as str
addi a1, a1, 16 # Load address of attribute __str__
j abort # Abort
.globl error.None
error.None:
li a0, 4 # Exit code for: Operation on None
la a1, const_6 # Load error message as str
addi a1, a1, 16 # Load address of attribute __str__
j abort # Abort
.globl error.OOB
error.OOB:
li a0, 3 # Exit code for: Index out of bounds
la a1, const_8 # Load error message as str
addi a1, a1, 16 # Load address of attribute __str__
j abort # Abort
.globl heap.init
heap.init:
# Runtime support function heap.init.
addi sp, sp, -16
sw ra, 12(sp)
call sbrk # Code for ecall: sbrk
lw ra, 12(sp) # 4-byte Folded Reload
addi sp, sp, 16
jr ra # Return to caller
.globl initchars
initchars:
sw a0, 4(sp)
la a0, $str$prototype
lw t0, 0(a0)
lw t1, 4(a0)
lw t2, 8(a0)
li t3, 1
la a0, allChars
lw t4, 4(sp)
initchars_1:
sw t0, 0(a0)
sw t1, 4(a0)
sw t2, 8(a0)
sw t3, 12(a0)
sw t4, 16(a0)
addi a0, a0, 20
jr ra
.data
.align 2
.globl allChars
allChars:
.space 5120
.globl len_12
len_12:
# Invalid argument
li a0, 1 # Exit code for: Invalid argument
la a1, const_2 # Load error message as str
addi a1, a1, 16 # Load address of attribute __str__
j abort # Abort
.globl len_13
len_13:
# Get length of string
lw a0, 12(a0) # Load attribute: __len__
jr ra # Return to caller
.globl makebool
makebool:
slli a0, a0, 4
la t0, const_0
add a0, a0, t0
jr ra
.globl makeint
makeint:
addi sp, sp, -8
sw ra, 4(sp)
sw a0, 0(sp)
la a0, $int$prototype
jal ra, alloc
lw t0, 0(sp)
sw t0, 12(a0)
lw ra, 4(sp)
addi sp, sp, 8
jr ra
.globl makestr
makestr:
addi sp, sp, -8
sw ra, 4(sp)
sw a0, 0(sp)
la a0, $int$prototype
lw t0, 0(a0)
add a0, a0, t0
jr ra
.globl noconv
noconv:
li a0, 0
jr ra
.globl print_10
print_10:
# Print False object in A0
la a0, const_4 # String representation: False
j print_8 # Go to: print(str)
.globl print_11
print_11:
# Print null-terminated string in A1
lui a0, %hi(char_string) # Load high bits for "%s"
addi a0, a0, %lo(char_string) # Load low bits for "%s"
sw ra, 0(sp)
call myprintf # Call printf
lw ra, 0(sp)
j print_5 # Go to return
char_string:
.asciz "%s\n"
.globl print_5
print_5:
# End of function
mv a0, zero # Load None
jr ra # Return to caller
.globl print_6
print_6:
# Invalid argument
li a0, 1 # Exit code for: Invalid argument
la a1, const_2 # Load error message as str
addi a1, a1, 16 # Load address of attribute __str__
j abort # Abort
.globl print_7
print_7:
# Printing ints.
# Print int object in A0
lw a1, 12(a0) # Load attribute __int__
lui a0, %hi(char_int) # Load high bits for "%i"
addi a0, a0, %lo(char_int)
addi sp,sp,-16
sw ra, 0(sp)
call myprintf # Call printf
lw ra, 0(sp)
addi sp,sp,16
jr ra
char_int:
.asciz "%d\n"
.globl print_8
print_8:
# Printing strs.
# Print str object in A0
addi a1, a0, 16 # Load address of attribute __str__
j print_11 # Print the null-terminated string is now in A1
mv a0, zero # Load None
j print_5 # Go to return
.globl print_9
print_9:
# Printing bools
# Print bool object in A0
lw a0, 12(a0) # Load attribute __bool__
beq a0, zero, print_10 # Go to: print(False)
la a0, const_3 # String representation: True
j print_8 # Go to: print(str)
.globl print
print:
# Function print
beq a0, zero, print_6 # None is an illegal argument
lw t0, 0(a0) # Get type tag of arg
li t1, 1 # Load type tag of `int`
beq t0, t1, print_7 # Go to print(int)
li t1, 3 # Load type tag of `str`
beq t0, t1, print_8 # Go to print(str)
li t1, 2 # Load type tag of `bool`
beq t0, t1, print_9 # Go to print(bool)
.globl strcat
strcat:
# Function strcat
addi sp, sp, -12
sw ra, 8(sp)
sw fp, 4(sp)
sw a0, 4(fp)
sw a1, 0(fp)
addi fp, sp, 12
lw t0, 4(fp)
lw t1, 0(fp)
lbu t0, 12(t0)
beqz t0, strcat_4
lw t1, 12(t1)
beqz t1, strcat_5
add t1, t0, t1
sw t1, -12(fp)
addi t1, t1, 4
srli t1, t1, 2
addi a1, t1, 4
la a0, $str$prototype
jal alloc2
lw t0, -12(fp)
sw t0, 12(a0)
addi t2, a0, 16
lw t0, 4(fp)
lbu t1, 12(t0)
addi t0, t0, 16
strcat_1:
beqz t1, strcat_2
lbu t3, 0(t0)
sb t3, 0(t2)
addi t1, t1, -1
addi t0, t0, 1
addi t2, t2, 1
j strcat_1
strcat_2:
lw t0, 0(fp)
lw t1, 12(t0)
addi t0, t0, 16
strcat_3:
beqz t1, strcat_6
lbu t3, 0(t0)
sb t3, 0(t2)
addi t1, t1, -1
addi t0, t0, 1
addi t2, t2, 1
j strcat_3
strcat_4:
lw a0, 0(fp)
j strcat_7
strcat_5:
lw a0, 4(fp)
j strcat_7
strcat_6:
sb zero, 0(t2)
strcat_7:
lw ra, -4(fp)
lw fp, -8(fp)
addi sp, sp, 12
jr ra
.globl streql
streql:
# Function streql
addi sp, sp, -8
sw ra, 4(sp)
sw fp, 0(sp)
addi fp, sp, 8
lw a1, 4(fp)
lw a2, 0(fp)
lw t0, 12(a1)
lw t1, 12(a2)
bne t0, t1, streql_no
streql_1:
lbu t2, 16(a1)
lbu t3, 16(a2)
bne t2, t3, streql_no
addi a1, a1, 1
addi a2, a2, 1
addi t0, t0, -1
bgtz t0, streql_1
li a0, 1
j streql_end
streql_no:
xor a0, a0, a0
streql_end:
lw ra, -4(fp)
lw fp, -8(fp)
addi sp, sp, 8
jr ra
.globl strneql
strneql:
# Function strneql
addi sp, sp, -8
sw ra, 4(sp)
sw fp, 0(sp)
addi fp, sp, 8
lw a1, 4(fp)
lw a2, 0(fp)
lw t0, 12(a1)
lw t1, 12(a2)
bne t0, t1, strneql_yes
strneql_1:
lbu t2, 16(a1)
lbu t3, 16(a2)
bne t2, t3, strneql_yes
addi a1, a1, 1
addi a2, a2, 1
addi t0, t0, -1
bgtz t0, strneql_1
xor a0, a0, a0
j strneql_end
strneql_yes:
li a0, 1
strneql_end:
lw ra, -4(fp)
lw fp, -8(fp)
addi sp, sp, 8
jr ra
