%include "asm_io.inc"

%macro for 3                ;macro para o inicio da execucao do for
    %push for               ;cria um novo contexto e coloca no topo da pilha de contexto
    cmp %1, %2              ;se arg1 == arg2 zero flag recebe 1
    jz %$end_loop
    %$start_loop:           ; inicia corpo do for
%endmacro

%macro end_for 3
    cmp %3, 0               ;verifica se  o loop eh para decrementar ou incrementar
    jz %$decrementa
    %$incrementa: inc %1    ;arg1++
    jmp %$next
    %$decrementa: dec %1    ;arg2--
    %$next: cmp %1, %2      ;arg1 == arg2?

	jnz %$start_loop  		; faz um jump para o inicio loop caso nao tenha terminado
	%$end_loop:       		; termina a iteracao
	%pop             		; remove da pilha
%endmacro

global forNASM

section .data
iteracao db "Iteracao: ", 0 ; "Iteracao: \0"
newline  db 0xa, 0          ; "\n\0"

section .text

forNASM:
    enter 0, 0; constroi uma pilha de frames para a chamada de procedimentos de uma linguagem de alto nivel
    pusha     ; um alias para pushaw ou pushad dependento do numero de bits

    mov edx, [ebp+8]  ;arg1 = valor inicial
    mov ebx, [ebp+12] ;arg2 = valor de destino
    mov ecx, [ebp+16] ;arg3 = incrementa(1) ou decrementa(0)
    mov edi, 0        ;numero de iteracoes  = 0

    for edx, ebx, ecx
        inc edi            ;numero de iteracoes++
        mov eax, iteracao  ;mensagem de cada iteracao
        call print_string  ;imprime string de iteracao
        mov  eax, edi      ;grava no registrador eax para imprimir um inteiro
        call print_int     ;imprime um inteiro
        mov eax, newline
        call print_string
    end_for edx, ebx, ecx

    popa; realiza um pop de todos os registradores da pilha
    leave; destroi a pilha de frame criada pelo enter

    ret


