%include "io.inc"
;
;@author Dimoiu Cezar Gabriel - 322CB
;
%define MAX_INPUT_SIZE 4096

section .bss
    expr: resb MAX_INPUT_SIZE

section .text
global CMAIN

CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp

    GET_STRING expr, MAX_INPUT_SIZE

    ; my code goes here 
    xor ecx, ecx
    xor eax, eax
    mov esi, 1 ;trick pentru stabilire semn numar
citire:
    xor edx, edx
    xor ebx, ebx
    xor eax, eax
    mov bl, byte [expr + ecx]
    
    cmp bl, 0x2D ;cmp with '-'
    je verificare
    
    cmp bl, 0x2A ;cmp with '*'
    je inmultire
    
    cmp bl, 0x2B ;cmp with '+'
    je adunare
    
    cmp bl, 0x2F ;cmp with '/'
    je impartire
    
    cmp bl, 0x20 ;cmp with ' '
    je space
    
    cmp bl, 0x0
    je finish
    
numar:
    sub bl, 0x30 ; Ascii to value
    imul eax, 10
    add eax, ebx
    inc ecx
    xor ebx, ebx
    mov bl, byte [expr + ecx]
    cmp bl, 0x20
    jne numar
    
    imul eax, esi ;trick aplicat
    mov esi, 1
    push eax
    
    jmp citire    

verificare:
    mov dl, [expr + ecx + 1]
    inc ecx
    mov esi, -1
    cmp dl, 0x0 ;cmp with null
    je scadere
    cmp dl, 0x20 ;cmp with ' '
    je scadere
    jmp citire
    
scadere:
    pop eax
    pop ebx
    sub ebx, eax
    push ebx
    inc ecx
    cmp dl, 0x0
    mov esi, 1 ;trick pentru stabilire semn numar
    je finish
    jmp citire
    
adunare:
    pop eax
    pop ebx
    add ebx, eax
    push ebx
    inc ecx
    jmp citire
    
inmultire:
    pop ebx 
    pop eax 
    imul ebx ;eax = eax * ebx
    push eax
    inc ecx
    jmp citire
    
impartire:
    xor edx, edx ;ca sa mearga impartirea :)
    pop ebx 
    pop eax 
    cmp eax, 0
    jl ceva
    jge impartire2

ceva:
    mov edx, -1 ; ca sa mearga impartirea :)
impartire2:    
    idiv ebx ;rezultat in eax
    push eax
    inc ecx
    jmp citire
    
space: 
    inc ecx
    jmp citire

finish:
    pop edx
    PRINT_DEC 4, edx
            
    pop ebp
    ret
