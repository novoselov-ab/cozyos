  ;global descriptor table
  gdt:
 
  gdt_null:
  dq 0
 
  gdt_code:
  dw 0FFFFh
  dw 0
 
  db 0
  db 10011010b
  db 11001111b
  db 0
 
  gdt_data:
  dw 0FFFFh
  dw 0
 
  db 0
  db 10010010b
  db 11001111b
  db 0
 
  gdt_end:
 
  gdt_desc:
   dw gdt_end - gdt - 1
   dd gdt
 

 global load_gdt
 
  ;load gdt
  load_gdt:
    ;push bp
    ;mov bp, sp

    cli  ;disable interrupts
    lgdt [gdt_desc]  ;load GDT
    sti  ;enable interrupts

	  mov ax,0x10 ;0x10 is address of second descriptor[kernel data segment] (Loading the segment selector registers is easy for the data registers)
	  ;load all data segment selectrors
    mov ds,ax 
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
  	jmp 0x08:.flush_cs ;0x08 is the address of our kernel code segment : far jump -- It will first set cs to 0x08 and then jump to flush_cs using its absolute address.
	  .flush_cs: ; to load cs we have to do a “far jump”:
		ret

