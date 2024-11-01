    .extern start_kernel
    # .section .text.entry # <- .text.entry 改为 .text.init
    .section .text.init
    .globl _start
_start:
    # ------------------
    la sp, boot_stack_top   # 加载栈顶地址到栈指针寄存器 sp

    # # set stvec = _traps
    la t0, _traps
    csrw stvec, t0

    # set sie[STIE] = 1, 第五位设为1，表示开启时钟中断
    li t0, 0x20
    csrrs x0, sie, t0

    # # set first time interrupt
    rdtime a0
    li a1, 1000000
    add a0, a0, a1
    # call sbi_set_timer 设置下一次时钟中断
    jal ra, sbi_set_timer

    # # set sstatus[SIE] = 1, 第一位设为1，表示开启中断
    li t0, 0x2
    csrrs x0, sstatus, t0

    j start_kernel       # 跳转到 start_kernel处
    # ------------------

    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 4096 # <-- change to your stack size

    .globl boot_stack_top
boot_stack_top: