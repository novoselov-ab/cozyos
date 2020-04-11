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
    cli  ;disable interrupts
    lgdt [gdt_desc]  ;load GDT
    sti  ;enable interrupts
    ret

