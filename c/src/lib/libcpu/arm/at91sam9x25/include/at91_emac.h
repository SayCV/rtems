/*
 * Copyright (C) 2009 Jens Scharsig (js_at_ng@scharsoft.de)
 *
 * based on AT91RM9200 datasheet revision I (36. Ethernet MAC (EMAC))
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef AT91_H
#define AT91_H

typedef struct at91_emac {
	uint32_t	 ctl;
	uint32_t	 cfg;
	uint32_t	 sr;
	uint32_t	 reserved1[2];
	//uint32_t	 tar;
	//uint32_t	 tcr;
	uint32_t	 tsr;
	uint32_t	 rbqp;
	uint32_t	 tbqp;
	
	uint32_t	 rsr;
	uint32_t	 isr;
	uint32_t	 ier;
	uint32_t	 idr;
	uint32_t	 imr;
	uint32_t	 man;
	//uint32_t	 reserved1[2];
	uint32_t	 ptr;
	uint32_t	 ptr;
	uint32_t	 fto;
	//uint32_t	 fra;
	uint32_t	 scf;
	uint32_t	 mcf;
	uint32_t	 fro;
	uint32_t	 fcse;
	uint32_t	 ale;
	uint32_t	 dtf;
	uint32_t	 lcol;
	uint32_t	 ecol;
	uint32_t	 tund;
	uint32_t	 cse;
	uint32_t	 rre;
	uint32_t	 rov;
	uint32_t	 rse;
	uint32_t	 ele;
	uint32_t	 rja;
	uint32_t	 usf;
	uint32_t	 ste;
	uint32_t	 rle;
	uint32_t	 reserved2[1];
	uint32_t	 hsl;
	uint32_t	 hsh;
	uint32_t	 sa1l;
	uint32_t	 sa1h;
	uint32_t	 sa2l;
	uint32_t	 sa2h;
	uint32_t	 sa3l;
	uint32_t	 sa3h;
	uint32_t	 sa4l;
	uint32_t	 sa4h;
	uint32_t	 tid;
	uint32_t	 reserved3[1];
	uint32_t	 usrio;
} at91_emac_t;

#define AT91_EMAC_CTL_LB	0x0001
#define AT91_EMAC_CTL_LBL	0x0002
#define AT91_EMAC_CTL_RE	0x0004
#define AT91_EMAC_CTL_TE	0x0008
#define AT91_EMAC_CTL_MPE	0x0010
#define AT91_EMAC_CTL_CSR	0x0020
#define AT91_EMAC_CTL_ISR	0x0040
#define AT91_EMAC_CTL_WES	0x0080
#define AT91_EMAC_CTL_BP	0x1000

#define AT91_EMAC_CFG_SPD	0x0001
#define AT91_EMAC_CFG_FD	0x0002
#define AT91_EMAC_CFG_BR	0x0004
#define AT91_EMAC_CFG_CAF	0x0010
#define AT91_EMAC_CFG_NBC	0x0020
#define AT91_EMAC_CFG_MTI	0x0040
#define AT91_EMAC_CFG_UNI	0x0080
#define AT91_EMAC_CFG_BIG	0x0100
#define AT91_EMAC_CFG_EAE	0x0200
#define AT91_EMAC_CFG_CLK_MASK	0xFFFFF3FF
#define AT91_EMAC_CFG_MCLK_8	0x0000
#define AT91_EMAC_CFG_MCLK_16	0x0400
#define AT91_EMAC_CFG_MCLK_32	0x0800
#define AT91_EMAC_CFG_MCLK_64	0x0C00
#define AT91_EMAC_CFG_RTY	0x1000
#define AT91_EMAC_CFG_RMII	0x2000

#define AT91_EMAC_SR_LINK	0x0001
#define AT91_EMAC_SR_MDIO	0x0002
#define AT91_EMAC_SR_IDLE	0x0004

#define AT91_EMAC_TCR_LEN(x)	(x & 0x7FF)
#define AT91_EMAC_TCR_NCRC	0x8000

#define AT91_EMAC_TSR_OVR	0x0001
#define AT91_EMAC_TSR_COL	0x0002
#define AT91_EMAC_TSR_RLE	0x0004
#define AT91_EMAC_TSR_TXIDLE	0x0008
#define AT91_EMAC_TSR_BNQ	0x0010
#define AT91_EMAC_TSR_COMP	0x0020
#define AT91_EMAC_TSR_UND	0x0040

#define AT91_EMAC_RSR_BNA	0x0001
#define AT91_EMAC_RSR_REC	0x0002
#define AT91_EMAC_RSR_OVR	0x0004

/*  ISR, IER, IDR, IMR use the same bits */
#define AT91_EMAC_IxR_DONE	0x0001
#define AT91_EMAC_IxR_RCOM	0x0002
#define AT91_EMAC_IxR_RBNA	0x0004
#define AT91_EMAC_IxR_TOVR	0x0008
#define AT91_EMAC_IxR_TUND	0x0010
#define AT91_EMAC_IxR_RTRY	0x0020
#define AT91_EMAC_IxR_TBRE	0x0040
#define AT91_EMAC_IxR_TCOM	0x0080
#define AT91_EMAC_IxR_TIDLE	0x0100
#define AT91_EMAC_IxR_LINK	0x0200
#define AT91_EMAC_IxR_ROVR	0x0400
#define AT91_EMAC_IxR_HRESP	0x0800

#define AT91_EMAC_MAN_DATA_MASK		0xFFFF
#define AT91_EMAC_MAN_CODE_802_3	0x00020000
#define AT91_EMAC_MAN_REGA(reg)		((reg & 0x1F) << 18)
#define AT91_EMAC_MAN_PHYA(phy)		((phy & 0x1F) << 23)
#define AT91_EMAC_MAN_RW_R		0x20000000
#define AT91_EMAC_MAN_RW_W		0x10000000
#define AT91_EMAC_MAN_HIGH		0x40000000
#define AT91_EMAC_MAN_LOW		0x80000000

#endif
