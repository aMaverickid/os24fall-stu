    .extern start_kernel
    .section .text.entry
    .globl _start
_start:
    #error Unimplemented
    # ------------------
    la sp, boot_stack_top   # 加载栈顶地址到栈指针寄存器 sp
    tail start_kernel       # 跳转到 start_kernel处
    # ------------------

    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 4096 # <-- change to your stack size

    .globl boot_stack_top
boot_stack_top:
    .equ boot_stack_top, boot_stack + 4096