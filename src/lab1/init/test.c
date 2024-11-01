#include "printk.h"

void test() {
    int i = 0;
    while (1) {
        if ((++i) % 200000000 == 0) {
            printk("kernel is running!\n");
            i = 0;
        }
    }
}