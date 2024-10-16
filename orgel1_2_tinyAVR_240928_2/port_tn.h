/*
--------------------------------------------------------------------------
PORT - I/O Ports (SHIGEの勝手なｱﾚﾝｼﾞでPINnCTRLを配列にした)
--------------------------------------------------------------------------
*/

/* I/O Ports */
typedef struct PORTn_struct
{
    register8_t DIR;  /* Data Direction */
    register8_t DIRSET;  /* Data Direction Set */
    register8_t DIRCLR;  /* Data Direction Clear */
    register8_t DIRTGL;  /* Data Direction Toggle */
    register8_t OUT;  /* Output Value */
    register8_t OUTSET;  /* Output Value Set */
    register8_t OUTCLR;  /* Output Value Clear */
    register8_t OUTTGL;  /* Output Value Toggle */
    register8_t IN;  /* Input Value */
    register8_t INTFLAGS;  /* Interrupt Flags */
    register8_t reserved_1[6];
    register8_t PINnCTRL[8];  /* Pin Control */
    register8_t reserved_2[8];
} PORT_tn;
