%include "asm_io.inc"

global randNASM

SECTION .bss
retorno resd 1

SECTION .text


randNASM:

    push ebx
    push ecx
    mov ebx, [esp+12]; recebe lfsr ou a seed

    mov ecx, ebx; registrador para guardar os valores shiftados
    mov eax, ebx; lfsr >> 0
    shr ecx, 2  ; lfsr >> 2
    xor eax, ecx; (lfsr >> 0) ^ (lfsr >> 2)
    shr ecx, 1  ; lfsr >> 3
    xor eax, ecx; (lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3)
    shr ecx, 2  ; lfsr >> 5
    xor eax, ecx; (lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)
    shr ecx, 2  ; lfsr >> 7
    xor eax, ecx; (lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ^ (lfsr >> 7)
    shr ecx, 6  ; lfsr >> 13
    xor eax, ecx; (lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ^ (lfsr >> 7) ^ (lfsr >> 13)
    and eax, 1  ; &1u

    shl eax, 23        ; bit << 23
    shr ebx, 1         ; lfsr >> 1
    or  ebx, eax       ; lfsr = (lfsr >> 1) | (bit << 31)
    and ebx, 0x00FFFFFF; lfsr = lfsr & 0x00FFFFFF;

    mov eax, ebx; valor de retorno
    pop ecx
    pop ebx
    ret