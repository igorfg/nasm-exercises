//nasm -f elf -d ELF_TYPE asm_io.asm && nasm -f elf for.asm && gcc -m32 asm_io.o for.o for.c -o a

#include <stdio.h>

void forNASM(int arg1, int arg2, int arg3);

int main() {
    printf("Teste forNASM\n");
    printf("for (int i = 0; i < 10; i++)\n");
    forNASM(0, 10, 1);
    printf("\nfor (int i = 10; i > 0; i--)\n");
    forNASM(10, 0, 0);
    return 0;
}