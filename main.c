#include <stdio.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

void bar(int, int);

void foo(int a, int b) {
    int c = a + b;
    int d = a * b;
    bar(c, d);
    return;
}

void baz(void) {
  unw_cursor_t cursor;
    unw_context_t ctx;
    unw_word_t ip, reg;
    unw_getcontext(&ctx);
    unw_init_local(&cursor, &ctx);

    int frame = 0;
    while (unw_step(&cursor) > 0 && frame < 9) {
        unw_word_t offset, pc;
        char functionName[256];

        if (unw_get_reg(&cursor, UNW_REG_IP, &pc)) {
            printf("Error reading program counter\n");
            break;
        }

        if ((unw_get_proc_name(&cursor, functionName, sizeof(functionName), &offset) == 0)) {
            printf("Frame %d: %s (+0x%lx)\n", frame, functionName, offset);
            unw_get_reg(&cursor, UNW_X86_64_RDX, &reg);
            int* x = (int*)reg;
            printf("rsi is %d\n", reg);
        } else {
            printf("Frame %d: -- unknown function --\n", frame);
        }

        frame++;
    }

}

void bar(int a, int b) {
    baz();
    printf("%d", a-b);  
}

int main() {
    int x = 3;
    int y = 7;
    foo(x,y);
    return 0;
}
