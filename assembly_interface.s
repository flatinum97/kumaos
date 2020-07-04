global outb

outb:
    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al
    ret

global inb

inb:
    mov dx, [esp+4]
    in al, dx
    ret

global lgdt

lgdt:
    mov edx, [esp+4]
    lgdt [edx]
    ret

global load_idt

load_idt:
   mov eax, [esp+4]
   lidt [eax]
   ret

global interrupt

interrupt:
    mov eax, [esp+4]
    int 9

global sti

sti:
  sti
  ret

global set_page_directory
; Sets cr3 to the physical address of a page directory
; page_directory: [esp+4] the physical address of the page directory
set_page_directory:
    mov eax, [esp+4]
    mov cr3, eax
    ret

global enable_paging
; Sets the paging bit on cr0 to enable paging
enable_paging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret
