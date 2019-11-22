#include <string.h>
#include <stdio.h>
#include "gdt.h"

gdt_desc_t gdt[4];

static void __init_gdt_desc(gdt_desc_t* desc, u32 base, u32 limit,
                            u8 dpl, u8 type) {
    desc->limit0 = limit & 0xffff;
    desc->base0 = base & 0xffff;
    desc->base16 = (base >> 16) & 0xff;
    desc->type = type & 0xf;
    desc->s = 0x1;
    desc->dpl = dpl & 0x3;
    desc->p = 0x1;
    desc->limit16 = (limit >> 16) & 0xf;
    desc->avl = 0x1;
    desc->l = 0x0;
    desc->d_b = 0x1;
    desc->g = 0x1;
    desc->base24 = (base >> 24) & 0xff;
}

void init_gdt() {
    gdtr_t gdtr;

    printf("Initializing GDT...\r\n");
    __init_gdt_desc(&gdt[0], 0x0, 0x0, 0x0, 0x0); // Null Segment
    __init_gdt_desc(&gdt[1], 0x0, 0xfffff, SEG_DPL_KERNEL, SEG_CODE_EXRD); // Code Segment
    __init_gdt_desc(&gdt[2], 0x0, 0xfffff, SEG_DPL_KERNEL, SEG_DATA_RDWRA); // Data Segment
    __init_gdt_desc(&gdt[3], 0x0, 0x0, SEG_DPL_KERNEL, SEG_DATA_RDWREXPDA); // Stack Segment
    
    printf("Initializing GDTR...\r\n");
    gdtr.base_address = &gdt;
    gdtr.limit = sizeof(gdt) - 1;
    
    printf("Loading GDT...\r\n");
    asm volatile("lgdt %0\n":/* no output */: "m" (gdtr): "memory");
    
    printf("Setting PE on CR0...\r\n");
    asm("movl %cr0, %eax\n \
         orl $0x1, %eax\n \
         movl %eax, %cr0");

    printf("Reloading Segment Selector...\r\n");
    asm("movw $0x10, %ax \n \
         movw %ax, %ds  \n \
         movw %ax, %ss  \n \
         movw %ax, %fs  \n \
         movw %ax, %gs  \n \
         movw %ax, %es  \n \
         ljmp $0x08, $next \n \
         next:          \n");
}