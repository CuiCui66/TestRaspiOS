ENTRY(_start)

SECTIONS {
. = 0x8000;

/* Make sure our entry stub goes first */
.stub   : { *(.text.start) }
.text   : { *(.text) }
.rodata : { *(.rodata) }
.data   : { *(.data) }
.bss    : { *(.bss COMMON) }
}
