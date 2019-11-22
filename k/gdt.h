#ifndef GDT_H_
#define GDT_H_

#include "include/k/types.h"

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define SEG_DPL_KERNEL     0x0
#define SEG_DPL_USER       0x3


typedef struct gdt_desc_s {
    u16 limit0;
    u16 base0;
    u8  base16;
    u16 type : 4;
    u16 s : 1;
    u16 dpl : 2;
    u16 p : 1;
    u16 limit16 : 4;
    u16 avl : 1;
    u16 l : 1;
    u16 d_b : 1;
    u16 g : 1;
    u8  base24;
}__attribute__((packed)) gdt_desc_t;

typedef struct gdtr_s {
    u16 limit;
    u32 base_address;
}__attribute__((packed)) gdtr_t;

extern gdt_desc_t gdt[4];

void init_gdt();

#endif  /* !GDT_H_ */