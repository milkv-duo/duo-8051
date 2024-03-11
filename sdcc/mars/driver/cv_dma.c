/*
 * Copyright (c) 2019, Cvitek. All rights reserved.
 *
 */

#include "cvi_reg.h"
#include "chip_cv1822.h"
#include "sysdma.h"

//
//  memcpy_dma(unsigned long *dst, unsigned long *src, uint32_t len)
//		dst: destination memory  address
//		src: pointer source buffer
//		len: length of tx buffer
//		return none
//
void memcpy_dma(unsigned long dst, unsigned long src, uint32_t len) __reentrant
{
	uint8_t ch = 0;
	uint32_t ctl[2], cfg[2];
	uint32_t llp = (uint32_t)(0x80A00000);
	uint32_t offset, xfer_count;

	SYSDMA_W32(DMAC_CFGREG, 0x0); // dma off

//	cfg[0] = (3UL << 2)    //3: linked list type of destination
//		| (3UL << 0);      //3: linked list type of source
//	cfg[1] = (15UL << (55-32))  //source outstanding request limit = 16
//		| (15UL << (59-32))  //destination outstanding request limit = 16
//		| (7UL << (49-32))   //7: highest priority, 0 is lowest priority
//		| (0UL << (32-32))   //0: MEM_TO_MEM_DMA
//		| (0UL << (36-32))   //0: hw Handshaking select of destination
//		| (0UL << (35-32))   //0: hw Handshaking select of source
//		| (ch << (39-32)) 	//hw handshake interface of source
//		| (ch << (44-32));	//hw handshake interface of destination
	cfg[0] = 0xf;
	cfg[1] = 0x7f8e0000;

	SYSDMA_W64(CH_CFG + ch*0x100, cfg[0], cfg[1]); //set CFG reg
	SYSDMA_W64(CH_LLP + ch*0x100, llp, 0); //set the first llp mem addr to CHANNEL LLP reg

	for (offset = 0; offset < len; offset += PAGE_SIZE) {
	//	ctl[0] = (0x0UL << 14)	//SRC_MSIZE (0x0: 1 Data Item read from Source in the burst transaction)
	//		| (0x0UL << 18)	//DST_MSIZE (0x0: 1 Data Item read from Destination in the burst transaction)
	//		| (0x0UL << 0)	//SMS (0x1: Destination device on Master-2interface layer)
	//		| (0x0UL << 2)	//DMS (0x1: Destination device on Master-2interface layer)
	//		| (0x0UL << 4)	//SINC (0: Increment)
	//		| (0x0UL << 6)	//DINC (0: Increment)
	//		| (0x2UL << 8)	//SRC_TR_WIDTH (0x2: 32bits data)
	//		| (0x2UL << 11);	//DST_TR_WIDTH (0x2: 32bits data)
	//	ctl[1] = (0x1UL << (62-32))	//DWC_CTL_SHADOWREG_OR_LLI_LAST
	//		| (0x1UL << (63-32));	//SHADOWREG_OR_LLI_VALID
		ctl[0] = 0x1200;
		if ((offset + PAGE_SIZE) < len) {
			xfer_count = PAGE_SIZE;
			ctl[1] = 0x80000000;
		} else {
			xfer_count = len - offset;
			ctl[1] = 0xC0000000;
		}

		mmio_write_64((uint32_t)llp + LLI_OFFSET_SAR, (uint32_t)(src + offset), 0); //SAR
		mmio_write_64((uint32_t)llp + LLI_OFFSET_DAR, (uint32_t)(dst + offset), 0); //DAR
		mmio_write_64((uint32_t)llp + LLI_OFFSET_BTS, xfer_count/4-1, 0); //BLOCK_TS[20:0]: block transfer size
		mmio_write_64((uint32_t)llp + LLI_OFFSET_LLP, llp + LLI_BLK_SIZE, 0);	//Starting Address In Memory of next LLI

		mmio_write_64((uint32_t)llp + LLI_OFFSET_CTL, ctl[0], ctl[1]); //Make itself the last LLP block

		llp += LLI_BLK_SIZE;
		// Flush D-cache
	//	flush_dcache_range((uint64_t)llp, LLI_BLK_SIZE);
	}

	SYSDMA_W32(DMAC_CFGREG, 0x1);

	SYSDMA_W32(DMAC_CHENREG, 0x101);

//	while (SYSDMA_R32(DMAC_CHENREG) & (1<<ch));

//	SYSDMA_W32(DMAC_CFGREG, 0x0); // dma off
}
