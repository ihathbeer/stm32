MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
}

_estack = 0x20020000;    /* end of RAM */

SECTIONS
{
    /* program code and other data goes into FLASH*/
    /* functions will live under different sections of
     * the .text section when it's compiled */
    .text :
    {
        *(.text*)
    } >FLASH

    /* uninitialized data section goes into ram*/
    .bss :
    {
        *(.bss*)
    } >RAM
}
