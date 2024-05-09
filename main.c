#include <stdio.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

void bar(int, int);

void foo(int a, int b) {
    bar(a, b);
    int c = a + b;
    int d = a * b;
    return;
}

void print_reg(unw_cursor_t* cursor, long rid, unw_word_t reg, char* word)
{
        unw_get_reg(cursor, rid, &reg);
//        printf("%s is %ld\n", word, reg);
        printf("%s is %lx\n", word, (unsigned long)(reg & 0xFFFFFFFF));

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
            printf("func: %s\n", functionName);
            printf("Frame %d: %s (+0x%lx)\n", frame, functionName, offset);
            print_reg(&cursor, UNW_X86_64_RDI, reg, "RDI");
            print_reg(&cursor, UNW_X86_64_RSI, reg, "RSI");
            print_reg(&cursor, UNW_X86_64_RDX, reg, "RDX");
            print_reg(&cursor, UNW_X86_64_RCX, reg, "RCX");
            print_reg(&cursor, UNW_X86_64_RAX, reg, "RAX");
            print_reg(&cursor, UNW_X86_64_R8, reg, "R8");
            print_reg(&cursor, UNW_X86_64_R9, reg, "R9");
            print_reg(&cursor, UNW_X86_64_RBX, reg, "RBX");
            print_reg(&cursor, UNW_X86_64_RBP, reg, "RBP");
            print_reg(&cursor, UNW_X86_64_RSP, reg, "RSP");
            print_reg(&cursor, UNW_X86_64_R10, reg, "R10");
            print_reg(&cursor, UNW_X86_64_R11, reg, "R11");
            print_reg(&cursor, UNW_X86_64_R12, reg, "R12");
            print_reg(&cursor, UNW_X86_64_R13, reg, "R13");
            print_reg(&cursor, UNW_X86_64_R14, reg, "R14");
            print_reg(&cursor, UNW_X86_64_R15, reg, "R15");
            print_reg(&cursor, UNW_X86_64_RIP, reg, "RIP");
        } else {
            printf("Frame %d: -- unknown function --\n", frame);
        }

        frame++;
    }

}



void bar(int a, int b) {
    baz();
    printf("%d\n", a-b);  
}

int main() {
    int x = 3;
    int y = 7;
    foo(x,y);
    return 0;
}
