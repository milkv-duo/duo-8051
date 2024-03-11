#ifndef BITMAIN_SYSDMA_H
#define BITMAIN_SYSDMA_H
#include <stdio.h>
#include "cvi_reg.h"


#define DMAC_DMA_MAX_NR_MASTERS		2
#define DMAC_DMA_MAX_NR_CHANNELS	8
#define MAX_BLOCK_TX				0x100000
#define PAGE_SIZE					0x1000

#define DMAC_BASE			0x04330000

#define DMAC_CFGREG	0x10
#define DMAC_CHENREG	0x18
#define DMAC_RESETREG	0x58

#define DMAC_CFG_DMA_EN		(1 << 0)
#define DMAC_CFG_DMA_INT_EN	(1 << 1)

#define DWC_CTL_SMS(n)		((n & 0x1)<<0)	/* src master select */
#define DWC_CTL_DMS(n)		((n & 0x1)<<2)	/* dst master select */
#define DWC_CTL_SRC_INC		(0<<4)	/* Source Address Increment update */
#define DWC_CTL_SRC_FIX		(1<<4)	/* Source Address Increment not */
#define DWC_CTL_DST_INC		(0<<6)	/* Destination Address Increment update */
#define DWC_CTL_DST_FIX		(1<<6)	/* Destination Address Increment not */
#define DWC_CTL_SRC_WIDTH(n)	((n & 0x7)<<8)	/* Source Transfer Width */
#define DWC_CTL_DST_WIDTH(n)	((n & 0x7)<<11)	/* Destination Transfer Width */
#define DWC_CTL_SRC_MSIZE(n)	((n & 0xf)<<14)	/* SRC Burst Transaction Length, data items */
#define DWC_CTL_DST_MSIZE(n)	((n & 0xf)<<18)	/* DST Burst Transaction Length, data items */
#define DWC_CTL_AR_CACHE(n)	((n & 0xf)<<22)
#define DWC_CTL_AW_CACHE(n)	((n & 0xf)<<26)
#define DWC_CTL_N_LAST_W_EN	(1<<30)	/* last write posted write enable/disable */
#define DWC_CTL_N_LAST_W_DIS	(0<<30)	/* last write posted wrtie enable/disable */
#define DWC_CTL_ARLEN_DIS	(0UL<<38)	/* Source Burst Length Disable */
#define DWC_CTL_ARLEN_EN	(1UL<<38)	/* Source Burst Length Enable */
#define DWC_CTL_ARLEN(n)	((n & 0xff)<<39)
#define DWC_CTL_AWLEN_DIS	(0UL<<47)	/* DST Burst Length Enable */
#define DWC_CTL_AWLEN_EN	(1UL<<47)
#define DWC_CTL_AWLEN(n)	((n & 0xff)<<48)
#define DWC_CTL_SRC_STA_DIS	(0UL<<56)
#define DWC_CTL_SRC_STA_EN	(1UL<<56)
#define DWC_CTL_DST_STA_DIS	(0UL<<57)
#define DWC_CTL_DST_STA_EN	(1UL<<57)
#define DWC_CTL_IOC_BLT_DIS	(0UL<<58)	/* Interrupt On completion of Block Transfer */
#define DWC_CTL_IOC_BLT_EN	(1UL<<58)
#define DWC_CTL_SHADOWREG_OR_LLI_LAST	(1UL<<62)	/* Last Shadow Register/Linked List Item */
#define DWC_CTL_SHADOWREG_OR_LLI_VALID	(1UL<<63)	/* Shadow Register content/Linked List Item valid */

#define DWC_CFG_SRC_MULTBLK_TYPE(x)	((x & 0x7) << 0)
#define DWC_CFG_DST_MULTBLK_TYPE(x)	((x & 0x7) << 2)
#define DWC_CFG_TT_FC(x)		((x & 0x7) << 32)
#define DWC_CFG_HS_SEL_SRC_HW		(0UL<<35)
#define DWC_CFG_HS_SEL_SRC_SW		(1UL<<35)
#define DWC_CFG_HS_SEL_DST_HW		(0UL<<36)
#define DWC_CFG_HS_SEL_DST_SW		(1UL<<36)
#define DWC_CFG_SRC_HWHS_POL_H		(0UL << 37)
#define DWC_CFG_SRC_HWHS_POL_L		(1UL << 37)
#define DWC_CFG_DST_HWHS_POL_H		(0UL << 38)
#define DWC_CFG_DST_HWHS_POL_L		(1UL << 38)
#define DWC_CFG_SRC_PER(x)		((x & 0xff) << 39)
#define DWC_CFG_DST_PER(x)		((x & 0xff) << 44)

#define DWC_CFG_CH_PRIOR_MASK		(0x7UL << 49)	/* priority mask */
#define DWC_CFG_CH_PRIOR(x)		((x & 0x7) << 49)	/* priority */
#define DWC_CFG_SRC_OSR_LMT(x)		(((x) & 0xf) << 55)	/* max request x + 1 <= 16 */
#define DWC_CFG_DST_OSR_LMT(x)		(((x) & 0xf) << 59)

/* CHx_INTSTATUS_ENABLEREG */
#define DWC_INT_EN_BLK_TFR_DONE_DIS    (0 << 0)	/*Block Transfer Done Interrupt Status Enable / Disable */
#define DWC_INT_EN_BLK_TFR_DONE_EN     (1 << 0)	/*Block Transfer Done Interrupt Status Enable / Disable */
#define DWC_INT_EN_DMA_TFR_DONE_DIS    (0 << 1)	/*DMA Transfer Done Interrupt Status Enable / Disable */
#define DWC_INT_EN_DMA_TFR_DONE_EN     (1 << 1)	/*DMA Transfer Done Interrupt Status Enable / Disable */

/*CHx_INTSTATUS*/

/*CHx_INTCLEARREG*/
#define DWC_INT_CLEAR_BLK_TFR_DONE    (1 << 0)	/*Block Transfer Done Interrupt Clear Bit, W1C */
#define DWC_INT_CLEAR_DMA_TFR_DONE    (1 << 1)	/*DMA Transfer Done Interrupt Clear Bit, W1C */

#define DWC_CHAN_CFG_OFFSET	(0x120)
#define DWC_CHAN_LLP_OFFSET	(0x128)
#define DWC_CHAN_INTSTATUS_ENABLEREG_OFFSET    (0x180)
#define DWC_CHAN_INTSTATUS_OFFSET              (0x188)
#define DWC_CHAN_INTSIGNAL_ENABLEREG_OFFSET    (0x190)
#define DWC_CHAN_INTCLEARREG_OFFSET            (0x198)

#define CH_SAR			0x100
#define CH_DAR			0x108
#define CH_BLOCK_TS		0x110
#define CH_CFG          0x120
#define CH_LLP          0x128
#define CH_INTSTATUS    0x188
#define CH_INTCLRSTATUS 0x198

#define CH_EN_WE_OFFSET		8

#define LLI_OFFSET_SAR		0x0
#define LLI_OFFSET_DAR		0x8
#define LLI_OFFSET_BTS		0x10
#define LLI_OFFSET_LLP		0x18
#define LLI_OFFSET_CTL		0x20
#define LLI_BLK_SIZE		0x40

/* porting from bmtest */
#define TOP_DMA_CH_REMAP0       (TOP_BASE+0x154)
#define TOP_DMA_CH_REMAP1       (TOP_BASE+0x158)
#define TOP_DMA_CH_REMAP2       (TOP_BASE+0x15c)
#define TOP_DMA_CH_REMAP3       (TOP_BASE+0x160)

#define DMA_REMAP_CH0_OFFSET            0
#define DMA_REMAP_CH1_OFFSET            8
#define DMA_REMAP_CH4_OFFSET            0
#define DMA_REMAP_CH5_OFFSET            8
#define DMA_REMAP_UPDATE_OFFSET		31

#define DMA_CH0	0
#define DMA_CH1	1
#define DMA_CH2	2
#define DMA_CH3	3
#define DMA_CH4	4
#define DMA_CH5	5
#define DMA_CH6	6
#define DMA_CH7	7

#define DMAC_WRITE(offset, value) \
	mmio_write_64(DMAC_BASE + offset, (uint32_t)value)

#define DMAC_READ(offset) \
	mmio_read_64(DMAC_BASE + offset)

#define DMA_CHAN_WRITE(chan, offset, value) \
	mmio_write_64((uint32_t)(DMAC_BASE + ((chan * 0x100) + offset)), (uint32_t)(value))

#define DMA_CHAN_READ(chan, offset) \
	mmio_read_64((uint32_t)(DMAC_BASE + ((chan * 0x100) + offset)))

#define LLI_WRITE(addr, offset, value) \
	*(addr + (offset >> 3)) = (uint32_t)(value)

#define LLI_READ(addr, offset) \
	*(addr + (offset >> 3))

typedef uint32_t dma_addr_t;
typedef uint32_t phys_addr_t;

enum dma_master {
	DMA0,
	DMA1
};

enum transfer_direction {
	DMA_MEM_TO_MEM,
	DMA_MEM_TO_DEV,
	DMA_DEV_TO_MEM,
	DMA_TRANS_NONE,
};

enum slave_buswidth {
	SLAVE_BUSWIDTH_1_BYTE,
	SLAVE_BUSWIDTH_2_BYTE,
	SLAVE_BUSWIDTH_4_BYTE,
};

enum dma_msize {
	DW_DMA_MSIZE_1,
	DW_DMA_MSIZE_4,
	DW_DMA_MSIZE_8,
	DW_DMA_MSIZE_16,
	DW_DMA_MSIZE_32,
	DW_DMA_MSIZE_64,
	DW_DMA_MSIZE_128,
	DW_DMA_MSIZE_256,
};

/* flow controller */
enum dw_dma_fc {
	DW_DMA_FC_D_M2M,	/* FlowControl is DMAC, mem to mem */
	DW_DMA_FC_D_M2P,	/* FlowControl is DMAC, mem to perip */
	DW_DMA_FC_D_P2M,
	DW_DMA_FC_D_P2P,
	DW_DMA_FC_SP_P2M,	/* FlowControl is Source periph, periph to mem */
	DW_DMA_FC_SP_P2P,
	DW_DMA_FC_DP_M2P,	/* FlowControl is Dst periph, periph to mem */
	DW_DMA_FC_DP_P2P,
};

enum dma_handshake_id {
	DMA_RX_REQ_I2C0 = 24,
	DMA_TX_REQ_I2C0 = 25,
	DMA_RX_REQ_I2C1 = 26,
	DMA_TX_REQ_I2C1 = 27,
	DMA_RX_REQ_I2C2 = 28,
	DMA_TX_REQ_I2C2 = 29,
	DMA_RX_REQ_I2C3 = 30,
	DMA_TX_REQ_I2C3 = 31,
	DMA_RX_REQ_I2C4 = 32,
	DMA_TX_REQ_I2C4 = 33
};

#define SYSDMA_W64(offset, lval, hval)		\
	mmio_write_32(SYSDMA_BASE + offset, lval);	\
	mmio_write_32(SYSDMA_BASE + offset + 4, hval)

/*#define SYSDMA_R64(offset) \
	mmio_read_64(SYSDMA_BASE + offset)*/

#define SYSDMA_W32(offset, value) \
	mmio_write_32(SYSDMA_BASE + offset, value)

#define SYSDMA_R32(offset) \
	mmio_read_32(SYSDMA_BASE + offset)

void memcpy_dma(unsigned long dst, unsigned long src, uint32_t len) __reentrant;

#endif

