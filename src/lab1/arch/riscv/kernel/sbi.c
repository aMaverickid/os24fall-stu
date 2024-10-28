#include "stdint.h"
#include "sbi.h"

struct sbiret sbi_ecall(uint64_t eid, uint64_t fid,
                        uint64_t arg0, uint64_t arg1, uint64_t arg2,
                        uint64_t arg3, uint64_t arg4, uint64_t arg5) {
    /**
     * 将 eid（Extension ID）放入寄存器 a7 中，fid（Function ID）放入寄存器 a6 中，将 arg[0-5] 放入寄存器 a[0-5] 中
     */
    __asm__ volatile (
        "mv a7, %0\n"
        "mv a6, %1\n"
        "mv a0, %2\n"
        "mv a1, %3\n"
        "mv a2, %4\n"
        "mv a3, %5\n"
        "mv a4, %6\n"
        "mv a5, %7\n"
        "ecall\n"
        :
        : "r"(eid), "r"(fid), "r"(arg0), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5)
        : "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
    )
    struct sbiret ret;
    __asm__ volatile (
        "mv %0, a0\n"
        "mv %1, a1\n"
        : "=r"(ret.error), "=r"(ret.value)
    )
    return ret;
}

struct sbiret sbi_debug_console_write_byte(uint8_t byte) {
    return sbi_ecall(0x4442434e, 0x0, byte, 0, 0, 0, 0, 0);
}

struct sbiret sbi_system_reset(uint32_t reset_type, uint32_t reset_reason) {
    return sbi_ecall(0x53525354, 0x0, reset_type, reset_reason, 0, 0, 0, 0);
}