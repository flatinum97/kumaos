extern interrupt_handler

global interrupt_handler_1

interrupt_handler_1:
    push dword 0
    push dword 1
    jmp common_interrupt_handler

common_interrupt_handler:
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push esp
    push ebp

    ; call the C function
    call interrupt_handler

    pop ebp
    pop esp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ; restore the esp
    add esp, 8

    ; return to the code that got interrupt
    iret
