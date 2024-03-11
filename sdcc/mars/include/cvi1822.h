
#ifndef __CVI1822_H__
#define __CVI1822_H__

/*  BYTE Registers */
__sfr __at (0x81) SP;           /* Stack Pointer                        */
__sfr __at (0x82) DPL;          /* Data Pointer 0: low byte             */
__sfr __at (0x82) DPL0;         /* Data Pointer 0: low byte             */
__sfr __at (0x83) DPH;          /* Data Pointer 0: high byte            */
__sfr __at (0x83) DPH0;         /* Data Pointer 0: high byte            */
__sfr __at (0x84) DPL1;         /* Data Pointer 1: low byte             */
__sfr __at (0x85) DPH1;         /* Data Pointer 1: high byte            */
__sfr __at (0x86) DPS;          /* Data Pointer Select                  */
__sfr __at (0x87) PCON;         /* Power Control                        */
__sfr __at (0x88) TCON;         /* Timer Control                        */
__sfr __at (0x89) TMOD;         /* Timer Mode                           */
__sfr __at (0x8a) TL0;          /* Timer 0: low byte                    */
__sfr __at (0x8b) TL1;          /* Timer 1: low byte                    */
__sfr __at (0x8c) TH0;          /* Timer 0: high byte                   */
__sfr __at (0x8d) TH1;          /* Timer 1: high byte                   */
__sfr __at (0x8e) CKCON;        /* Clock Control                        */
__sfr __at (0x8f) MWS;          /* Memory Write Select                  */
__sfr __at (0x91) EXIF;         /* External Interrupt Flag              */
__sfr __at (0x92) MPAGE;        /* Memory Page                          */
__sfr __at (0x92) _XPAGE;       /* XDATA/PDATA PAGE                     */
__sfr __at (0x98) SCON;         /* Serial Control 0                     */
__sfr __at (0x98) SCON0;        /* Serial Control 0                     */
__sfr __at (0x99) SBUF;         /* Serial Buffer 0                      */
__sfr __at (0x99) SBUF0;        /* Serial Buffer 0                      */
__sfr __at (0xa8) IE;           /* Interrupt Enable                     */
__sfr __at (0xb8) IP;           /* Interrupt Priority                   */
__sfr __at (0xc0) SCON1;        /* Serial Control 1                     */
__sfr __at (0xc1) SBUF1;        /* Serial Buffer 1                      */
__sfr __at (0xc8) T2CON;        /* Timer 2 Control                      */
__sfr __at (0xca) RCAP2L;       /* Timer 2 Capture Low                  */
__sfr __at (0xcb) RCAP2H;       /* Timer 2 Capture High                 */
__sfr __at (0xcc) TL2;          /* Timer 2 Low byte                     */
__sfr __at (0xcd) TH2;          /* Timer 2 High byte                    */
__sfr __at (0xd0) PSW;          /* Program Status Word                  */
__sfr __at (0xd8) EICON;        /* Enable Interrupt Control             */
__sfr __at (0xe0) ACC;          /* Accumulator                          */
__sfr __at (0xe8) EIE;          /* Extended Interrupt Enable            */
__sfr __at (0xf0) B;            /* B Register                           */
__sfr __at (0xf8) EIP;          /* Extended Interrupt Priority          */


/*  BITS Registers */

        /* TCON                                                         */
        /*  _7_ _6_ _5_ _4_ _3_ _2_ _1_ _0_                             */
        /* |TF1|TR1|TF0|TR0|IE1|IT1|IE0|IT0|                            */
  __sbit __at (0x88) IT0;         /* External Interrupt 0 Type          */
  __sbit __at (0x89) IE0;         /* External Interrupt 0 Edge Flag     */
  __sbit __at (0x8a) IT1;         /* External Interrupt 1 Type          */
  __sbit __at (0x8b) IE1;         /* External Interrupt 1 Edge Flag     */
  __sbit __at (0x8c) TR0;         /* Timer 0 On/Off Control             */
  __sbit __at (0x8d) TF0;         /* Timer 0 Overflow Flag              */
  __sbit __at (0x8e) TR1;         /* Timer 1 On/Off Control             */
  __sbit __at (0x8f) TF1;         /* Timer 1 Overflow Flag              */

        /* SCON                                                         */
        /*  _7_ _6_ _5_ _4_ _3_ _2_ _1_ _0_                             */
        /* |SM0|SM1|SM2|REN|TB8|RB8|TI |RI |                            */
  __sbit __at (0x98) RI;          /* Receive Interrupt Flag             */
  __sbit __at (0x98) RI0;         /* Receive Interrupt Flag             */
  __sbit __at (0x98) RI_0;        /* Receive Interrupt Flag             */
  __sbit __at (0x99) TI;          /* Transmit Interrupt Flag            */
  __sbit __at (0x99) TI0;         /* Transmit Interrupt Flag            */
  __sbit __at (0x99) TI_0;        /* Transmit Interrupt Flag            */
  __sbit __at (0x9a) RB8;         /* Receive Bit 8                      */
  __sbit __at (0x9a) RB8_0;       /* Receive Bit 8                      */
  __sbit __at (0x9b) TB8;         /* Transmit Bit 8                     */
  __sbit __at (0x9b) TB8_0;       /* Transmit Bit 8                     */
  __sbit __at (0x9c) REN;         /* Receive Enable                     */
  __sbit __at (0x9c) REN_0;       /* Receive Enable                     */
  __sbit __at (0x9d) SM2;         /* Multiprocessor Communication Enable*/
  __sbit __at (0x9d) SM2_0;       /* Multiprocessor Communication Enable*/
  __sbit __at (0x9e) SM1;         /* Serial Port Select Mode 1          */
  __sbit __at (0x9e) SM1_0;       /* Serial Port Select Mode 1          */
  __sbit __at (0x9f) SM0;         /* Serial Port Select Mode 0          */
  __sbit __at (0x9f) SM0_0;       /* Serial Port Select Mode 0          */

        /* IE                                                           */
        /*  _7_ _6_ _5_ _4_ _3_ _2_ _1_ _0_                             */
        /* |EA |ES1|ET2|ES0|ET1|EX1|ET0|EX0|                            */
  __sbit __at (0xa8) EX0;         /* Enable External Interrupt 0        */
  __sbit __at (0xa9) ET0;         /* Enable Timer 0 Interrupt           */
  __sbit __at (0xaa) EX1;         /* Enable External Interrupt 1        */
  __sbit __at (0xab) ET1;         /* Enable Timer 1 Interrupt           */
  __sbit __at (0xac) ES0;         /* Enable Serial Port 0 Interrupt     */
  __sbit __at (0xad) ET2;         /* Enable Timer 2 Interrupt           */
  __sbit __at (0xae) ES1;         /* Enable Serial Port 1 Interrupt     */
  __sbit __at (0xaf) EA;          /* Global Interrupt Enable            */

        /* IP                                                           */
        /*  _7_ _6_ _5_ _4_ _3_ _2_ _1_ _0_                             */
        /* |   |   |PT2|PS |PT1|PX1|PT0|PX0|                            */
  __sbit __at (0xb8) PX0;         /* External Interrupt 0               */
  __sbit __at (0xb9) PT0;         /* Timer 0                            */
  __sbit __at (0xba) PX1;         /* External Interrupt 1               */
  __sbit __at (0xbb) PT1;         /* Timer 1                            */
  __sbit __at (0xbc) PS;          /* Serial Port                        */
  __sbit __at (0xbc) PS0;         /* Serial Port                        */
  __sbit __at (0xbd) PT2;         /* Timer 2                            */
  __sbit __at (0xbe) PS1;         /* Serial Port 1                      */

        /* SCON1                                                        */
        /*  _7_ _6_ _5_ _4_ _3_ _2_ _1_ _0_                             */
        /* |SM0|SM1|SM2|REN|TB8|RB8|TI |RI |                            */
  __sbit __at (0xc0) RI1;         /* Receive Interrupt Flag             */
  __sbit __at (0xc0) RI_1;        /* Receive Interrupt Flag             */
  __sbit __at (0xc1) TI1;         /* Transmit Interrupt Flag            */
  __sbit __at (0xc1) TI_1;        /* Transmit Interrupt Flag            */
  __sbit __at (0xc2) RB8_1;       /* Receive Bit 8                      */
  __sbit __at (0xc3) TB8_1;       /* Transmit Bit 8                     */
  __sbit __at (0xc4) REN_1;       /* Receive Enable                     */
  __sbit __at (0xc5) SM2_1;       /* Multiprocessor Communication Enable*/
  __sbit __at (0xc6) SM1_1;       /* Serial Port Select Mode 1          */
  __sbit __at (0xc7) SM0_1;       /* Serial Port Select Mode 0          */

        /* T2CON                                                        */
        /*  _7_ _6_  _5_  _4_  _3_   _2_ _1_  _0_                       */
        /* |TF2|EXF2|RCLK|TCLK|EXEN2|TR2|C_T2|CP_RL2 |                  */
  __sbit __at (0xc8) CP_RL2;      /* Capture/Reload Flag                */
  __sbit __at (0xc9) C_T2;        /* Overflow Flag                      */
  __sbit __at (0xca) TR2;         /* Timer Run                          */
  __sbit __at (0xcb) EXEN2;       /* Timer External Enable              */
  __sbit __at (0xcc) TCLK;        /* Transmit Clock Flag                */
  __sbit __at (0xcd) RCLK;        /* Receive Clock Flag                 */
  __sbit __at (0xce) EXF2;        /* External Flag                      */
  __sbit __at (0xcf) TF2;         /* Overflow Flag                      */

        /* PSW                                                          */
        /*  _7_ _6_ _5_ _4_ _3_ _2_ _1_ _0_                             */
        /* |CY |AC |F0 |RS1|RS0|OV |F1 |P  |                            */
  __sbit __at (0xd0) P;           /* Parity Flag                        */
  __sbit __at (0xd1) F1;          /* General Purpose User Flag 1        */
  __sbit __at (0xd2) OV;          /* Overflow Flag                      */
  __sbit __at (0xd3) RS0;         /* Register Bank Select 0 Flag        */
  __sbit __at (0xd4) RS1;         /* Register Bank Select 1 Flag        */
  __sbit __at (0xd5) F0;          /* General Purpose User Flag 0        */
  __sbit __at (0xd6) AC;          /* Auxiliary Carry Flag               */
  __sbit __at (0xd7) CY;          /* Carry Flag                         */


        /* EICON                                                        */
        /*  _7_   _6_ _5_ _4_ _3_  _2_ _1_ _0_                          */
        /* |SMOD1|   |EAI|AI |WDTI|   |   |   |                         */
  __sbit __at (0xdb) WDTI;        /* Watchdog Timer Interrupt Flag      */
  __sbit __at (0xdc) PFI;         /* Power fail Interrupt Flag          */
  __sbit __at (0xdd) EPFI;        /* Enable Power fail Interrupt        */
  __sbit __at (0xdf) SMOD1;       /* Serial Port 1 Mode                 */

        /* EIE                                                        */
        /*  _7_ _6_ _5_ _4_  _3_ _2_ _1_ _0_                            */
        /* |   |   |   |EWDI|EX5|EX4|EX3|EX2|                           */
  __sbit __at (0xe8) EX2;         /* Enable External Interrupt 2        */
  __sbit __at (0xe9) EX3;         /* Enable External Interrupt 3        */
  __sbit __at (0xea) EX4;         /* Enable External Interrupt 4        */
  __sbit __at (0xeb) EX5;         /* Enable External Interrupt 5        */
  __sbit __at (0xec) EWDI;        /* Enable Watchdog Interrupt          */

        /* EIP                                                        */
        /*  _7_ _6_ _5_ _4_  _3_ _2_ _1_ _0_                            */
        /* |   |   |   |PWDI|PX5|PX4|PX3|PX2|                           */
  __sbit __at (0xf8) PX2;         /* External Interrupt 2 Priority      */
  __sbit __at (0xf9) PX3;         /* External Interrupt 3 Priority      */
  __sbit __at (0xfa) PX4;         /* External Interrupt 4 Priority      */
  __sbit __at (0xfb) PX5;         /* External Interrupt 5 Priority      */
  __sbit __at (0xfc) PWDI;        /* Watchdog Interrupt Priority        */


#endif
