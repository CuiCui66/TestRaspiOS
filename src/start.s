.section .text.start
.global _start
_start:
  mov sp, #0x8000
  MRC p15,0,r0,c0,c0,5;
  and r0, r0, #7
  cmp r0,#0
  bne loop
  ldr pc, =kmain

loop:
  wfe
  b loop

