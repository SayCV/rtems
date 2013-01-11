/*
 *  AT91SAM9X25 ethernet driver
 *
 */
#if 1
#include <rtems.h>
#include <rtems/rtems_bsdnet.h>
#include <at91sam9x5.h>
#include <at91_aic.h>
#include <at91_emac.h>
#include <at91_gpio.h>
#include <at91_pmc.h>

#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <rtems/error.h>

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/sockio.h>

#include <net/if.h>

#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <bsp/irq.h>
#include <bspopts.h>

#include <dev/mii/mii.h>
//#undef MII_DEBUG
//#undef ET_DEBUG

#define AT91C_EMAC_RMII		((unsigned int) 0x1 << 13) /* (EMAC) */

/*
 * Bit assignments for Receive Buffer Descriptor
 * Address - Word 0
 */
#define RXBUF_ADD_BASE_MASK     0xfffffffc    /* Base addr of the rx buf */
#define RXBUF_ADD_WRAP          0x1<<1          /* set indicates last buf  */
#define RXBUF_ADD_OWNED         0x1<<0          /* 1 = SW owns the pointer */

/* Status - Word 1 */
#define RXBUF_STAT_BCAST        0x1<<31         /* Global bcast addr detected */
#define RXBUF_STAT_MULTI        0x1<<30         /* Multicast hash match */
#define RXBUF_STAT_UNI          0x1<<29         /* Unicast hash match */
#define RXBUF_STAT_EXT          0x1<<28         /* External address (optional) */
#define RXBUF_STAT_UNK          0x1<<27         /* Unknown source address  */
#define RXBUF_STAT_LOC1         0x1<<26         /* Local address 1 match */
#define RXBUF_STAT_LOC2         0x1<<25         /* Local address 2 match */
#define RXBUF_STAT_LOC3         0x1<<24         /* Local address 3 match */
#define RXBUF_STAT_LOC4         0x1<<23         /* Local address 4 match  */
#define RXBUF_STAT_LEN_MASK     0x7ff         /* Len of frame including FCS */

/* enable debugging of the PHY code */
#define PHY_DBG

#if (CONFIG_SYS_RX_ETH_BUFFER > 1024)
#error AT91 EMAC supports max 1024 RX buffers. \
	Please decrease the CONFIG_SYS_RX_ETH_BUFFER value
#endif

/* MDIO clock must not exceed 2.5 MHz, so enable MCK divider */
#if (AT91C_MASTER_CLOCK > 80000000)
	#define HCLK_DIV	AT91_EMAC_CFG_MCLK_64
#elif (AT91C_MASTER_CLOCK > 40000000)
	#define HCLK_DIV	AT91_EMAC_CFG_MCLK_32
#elif (AT91C_MASTER_CLOCK > 20000000)
	#define HCLK_DIV	AT91_EMAC_CFG_MCLK_16
#else
	#define HCLK_DIV	AT91_EMAC_CFG_MCLK_8
#endif

/* enable debugging of the EMAC code */
/* #define EMAC_DBG */

#if defined(CONFIG_AT91SAM9X5)
  /* Bit defines for the PHY Status Register #1 (phy address 0x01) */
  /* 1 = PHY able to perform 100BASE-T4 */
  #define PHY_STAT_100BASE_T4     0x1<<15
  /* 1 = PHY able to perform full-duplex 100BASE-X */
  #define PHY_STAT_100BASE_X_FDX  0x1<<14
  /* 1 = PHY able to perform half-duplex 100BASE-X */
  #define PHY_STAT_100BASE_X_HDX  0x1<<13
  /* 1 = PHY able to operate at 10 Mbps in full-duplex mode */
  #define PHY_STAT_10BASE_FDX     0x1<<12
  /* 1 = PHY able to operate at 10 Mbps in half-duplex mode */
  #define PHY_STAT_10BASE_HDX     0x1<<11
  /* 1 = PHY will accept management frames with preamble suppressed */
  #define PHY_STAT_MF_PREAMBLE    0x1<<6
  /* 1 = Auto-negotiation complete */
  #define PHY_STAT_AUTO_NEG_DONE  0x1<<5
  /* 1 = Remote fault condition detected */
  #define PHY_STAT_REM_FLT        0x1<<4
  /* 1 = PHY is able to perform Auto-Negotiation */
  #define PHY_STAT_AUTO_NEG_ABLE  0x1<<3
  /* 1 = Link is up */
  #define PHY_STAT_LINK_UP        0x1<<2
  /* 1 = Jabber condition detected */
  #define PHY_STAT_JABBER         0x1<<1
  /* 1 = Extended register capabilities */
  #define PHY_STAT_EXT_REG        0x1<<0

  /* Bit defines for the Auxillary Mode 3 register */
  #define PHY_AUX_MODE2_TRAFFIC_LED   0x1<<6
#endif

  /* interrupt stuff */
  #define AT91_EMAC_IxR_PRIORITY       0       /* lowest priority */

  /*  RTEMS event used by interrupt handler to start receive daemon. */
  #define START_RECEIVE_EVENT  RTEMS_EVENT_1

  /* RTEMS event used to start transmit daemon. */
  #define START_TRANSMIT_EVENT    RTEMS_EVENT_2

static void at91sam9x25_emac_isr (rtems_irq_hdl_param unused);
static void at91sam9x25_emac_isr_on(const rtems_irq_connect_data *unused);
static void at91sam9x25_emac_isr_off(const rtems_irq_connect_data *unused);
static int at91sam9x25_emac_isr_is_on(const rtems_irq_connect_data *irq);

/* Replace the first value with the clock's interrupt name. */
rtems_irq_connect_data at91sam9x25_emac_isr_data = {
    AT91SAM9X5_ID_EMAC0,
    at91sam9x25_emac_isr,
    NULL,
    at91sam9x25_emac_isr_on,
    at91sam9x25_emac_isr_off,
    at91sam9x25_emac_isr_is_on
};


/* use the values defined in linkcmds for our use of SRAM */
extern void * at91sam9x25_emac_rxbuf_hdrs;
extern void * at91sam9x25_emac_txbuf;
extern void * at91sam9x25_emac_rxbufs;

/* Set up EMAC hardware */
/* Number of Receive and Transmit Buffers and Buffer Descriptors */
#define NUM_RXBDS 8
#define NUM_TXBDS 1
#define RX_BUFFER_SIZE 0x600

/* use internal SRAM for buffers and descriptors
 * also insure that the receive descriptors
 * start on a 64byte boundary
 * Receive Buffer Descriptor Header
 */

typedef struct
{
    unsigned long address;
    unsigned long status;
} RXBUF_HDR;

RXBUF_HDR       *rxbuf_hdrs;
unsigned char   *txbuf;
unsigned char   *rxbuf;

int delay_cnt;

/*
 * Hardware-specific storage
 */
typedef struct
{
    /*
     * Connection to networking code
     * This entry *must* be the first in the sonic_softc structure.
     */
    struct arpcom                    arpcom;

    /*
     * Interrupt vector
     */
    rtems_vector_number             vector;

    /*
     *  Indicates configuration
     */
    int                             acceptBroadcast;

    /*
     * Task waiting for interrupts
     */
    rtems_id                        rxDaemonTid;
    rtems_id                        txDaemonTid;

    /*
     * current receive header
     */
    int                rx_buf_idx;



    /*
     * Statistics
     */
    unsigned long                   Interrupts;
    unsigned long                   rxInterrupts;
    unsigned long                   rxMissed;
    unsigned long                   rxGiant;
    unsigned long                   rxNonOctet;
    unsigned long                   rxBadCRC;
    unsigned long                   rxCollision;

    unsigned long                   txInterrupts;
    unsigned long                   txSingleCollision;
    unsigned long                   txMultipleCollision;
    unsigned long                   txCollision;
    unsigned long                   txDeferred;
    unsigned long                   txUnderrun;
    unsigned long                   txLateCollision;
    unsigned long                   txExcessiveCollision;
    unsigned long                   txExcessiveDeferral;
    unsigned long                   txLostCarrier;
    unsigned long                   txRawWait;
} at91sam9x25_emac_softc_t;

static at91sam9x25_emac_softc_t softc;


/* The at91sam9x25 ethernet fifos are very undersized. Therefore
 * we use the internal SRAM to hold 4 receive packets and one
 * transmit packet.  Note that the at91sam9x25 can only queue
 * one transmit packet at a time.
 */

/* function prototypes */
int rtems_at91sam9x25_emac_attach (struct rtems_bsdnet_ifconfig *config,
                                  void *chip);
void at91sam9x25_emac_init(void *arg);
void at91sam9x25_emac_init_hw(at91sam9x25_emac_softc_t *sc);
void at91sam9x25_emac_start(struct ifnet *ifp);
void at91sam9x25_emac_stop (at91sam9x25_emac_softc_t *sc);
void at91sam9x25_emac_txDaemon (void *arg);
void at91sam9x25_emac_sendpacket (struct ifnet *ifp, struct mbuf *m);
void at91sam9x25_emac_rxDaemon(void *arg);
void at91sam9x25_emac_stats (at91sam9x25_emac_softc_t *sc);
static int at91sam9x25_emac_ioctl (struct ifnet *ifp,
                                  ioctl_command_t command,
                                  caddr_t data);

void at91emac_EnableMDIO(at91_emac_t *at91mac);
void at91emac_DisableMDIO(at91_emac_t *at91mac);
int  at91emac_read(at91_emac_t *at91mac, unsigned char addr,
		unsigned char reg, unsigned short *value);
int  at91emac_write(at91_emac_t *at91mac, unsigned char addr,
		unsigned char reg, unsigned short value);

void at91emac_EnableMDIO(at91_emac_t *at91mac)
{
	/* Mac CTRL reg set for MDIO enable */
	writel(readl(&at91mac->ctl) | AT91_EMAC_CTL_MPE, &at91mac->ctl);
}

void at91emac_DisableMDIO(at91_emac_t *at91mac)
{
	/* Mac CTRL reg set for MDIO disable */
	writel(readl(&at91mac->ctl) & ~AT91_EMAC_CTL_MPE, &at91mac->ctl);
}

int  at91emac_read(at91_emac_t *at91mac, unsigned char addr,
		unsigned char reg, unsigned short *value)
{
	at91emac_EnableMDIO(at91mac);

	writel(AT91_EMAC_MAN_HIGH | AT91_EMAC_MAN_RW_R |
		AT91_EMAC_MAN_REGA(reg) | AT91_EMAC_MAN_CODE_802_3 |
		AT91_EMAC_MAN_PHYA(addr),
		&at91mac->man);
	rtems_task_wake_after(2);
	*value = readl(&at91mac->man) & AT91_EMAC_MAN_DATA_MASK;

	at91emac_DisableMDIO(at91mac);

	printk("AT91PHY read %x REG(%d)=%x\n", at91mac, reg, *value);

	return 0;
}

int  at91emac_write(at91_emac_t *at91mac, unsigned char addr,
		unsigned char reg, unsigned short value)
{
	printk("AT91PHY write %x REG(%d)=%x\n", at91mac, reg, &value);

	at91emac_EnableMDIO(at91mac);

	writel(AT91_EMAC_MAN_HIGH | AT91_EMAC_MAN_RW_W |
		AT91_EMAC_MAN_REGA(reg) | AT91_EMAC_MAN_CODE_802_3 |
		AT91_EMAC_MAN_PHYA(addr) | (value & AT91_EMAC_MAN_DATA_MASK),
		&at91mac->man);
	rtems_task_wake_after(2);

	at91emac_DisableMDIO(at91mac);
	return 0;
}

/*
 * phyread(): Read the PHY
 */
uint32_t phyread(uint8_t reg)
{
	at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
#if 1
	unsigned short data;
	at91emac_read(emac, 0, reg, &data);
	return data;
#else
  emac->man = (0x01 << 30  /* Start of Frame Delimiter */
            | 0x02 << 28            /* Operation, 0x01 = Write, 0x02 = Read */
            | 0x00 << 23            /* Phy Number, 0 as we only have one */
            | reg << 18             /* Phy Register */
            | 0x02 << 16);          /* must be 0x02 for turn around field */

  /* wait for phy read to complete (was udelay(5000)) */
  rtems_task_wake_after(1);

  #if defined(EMAC_DBG)
    printk(
      "EMAC: Phy 0, Reg %d, Read 0x%04lx.\n",
       reg,
       (emac->man & 0xffff)
    );
  #endif

  return emac->man & 0xffff;
#endif
}

/*
 * phywrite(): Write the PHY
 */
void phywrite(uint8_t reg, uint16_t data)
{
	at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
#if 1
	at91emac_write(emac, 0, reg, &data);
#else
  emac->man = (0x01 << 30 /* Start of Frame Delimiter */
             | 0x01 << 28          /* Operation, 0x01 = Write, 0x02 = Read */
             | 0x00 << 23          /* Phy Number, BCM5221 is address 0 */
             | reg << 18           /* Phy Register */
             | 0x02 << 16          /* must be 0x02 for turn around field */
             | data);
  #if defined(EMAC_DBG)
    printk("EMAC: Phy 0, Reg %d, Write 0x%04x.\n", reg, data);
  #endif

  /* wait for phy write to complete (was udelay(5000)) */
  rtems_task_wake_after(1);
#endif
}


int rtems_at91sam9x25_emac_attach (
    struct rtems_bsdnet_ifconfig *config,
    void *chip  /* only one ethernet, so no chip number */
    )
{
		at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    struct ifnet *ifp;
    int mtu;
    int unitnumber;
    char *unitname;
    void *p;

    /* an array of receive buffer descriptors -- avoid type punned warning */
    p = (void *)&at91sam9x25_emac_rxbuf_hdrs;
    rxbuf_hdrs = (RXBUF_HDR *)p;

    /* one transmit buffer, 1536 bytes maximum */
    txbuf = (unsigned char *)&at91sam9x25_emac_txbuf;

    /* receive buffers starting address */
    rxbuf = (unsigned char *)&at91sam9x25_emac_rxbufs;
    /*
     * Parse driver name
     */
    if ((unitnumber = rtems_bsdnet_parse_driver_name (config, &unitname)) < 0)
        return 0;

    /*
     * Is driver free?
     */
    if (unitnumber != 0) {
        printk ("Bad at91sam9x25 EMAC unit number.\n");
        return 0;
    }
    ifp = &softc.arpcom.ac_if;
    if (ifp->if_softc != NULL) {
        printk ("Driver already in use.\n");
        return 0;
    }

    /*
     *  zero out the control structure
     */

    memset( &softc, 0, sizeof(softc) );


    /* get the MAC address from the chip */
    softc.arpcom.ac_enaddr[0] = (readl(&emac->sh1l) >> 0) & 0xff;
    softc.arpcom.ac_enaddr[1] = (readl(&emac->sh1l) >> 8) & 0xff;
    softc.arpcom.ac_enaddr[2] = (readl(&emac->sh1l) >> 16) & 0xff;
    softc.arpcom.ac_enaddr[3] = (readl(&emac->sh1l) >> 24) & 0xff;
    softc.arpcom.ac_enaddr[4] = (readl(&emac->sa1h) >> 0) & 0xff;
    softc.arpcom.ac_enaddr[5] = (readl(&emac->sa1h) >> 8) & 0xff;

    #if 0
      printk( "MAC=%02x:%02x:%02x:%02x:%02x:%02x\n",
        softc.arpcom.ac_enaddr[0],
        softc.arpcom.ac_enaddr[1],
        softc.arpcom.ac_enaddr[2],
        softc.arpcom.ac_enaddr[3],
        softc.arpcom.ac_enaddr[4],
        softc.arpcom.ac_enaddr[5]
      );
    #endif

    if (config->mtu) {
        mtu = config->mtu;
    } else {
        mtu = ETHERMTU;
    }

    softc.acceptBroadcast = !config->ignore_broadcast;

    /*
     * Set up network interface values
     */
    ifp->if_softc = &softc;
    ifp->if_unit = unitnumber;
    ifp->if_name = unitname;
    ifp->if_mtu = mtu;
    ifp->if_init = at91sam9x25_emac_init;
    ifp->if_ioctl = at91sam9x25_emac_ioctl;
    ifp->if_start = at91sam9x25_emac_start;
    ifp->if_output = ether_output;
    ifp->if_flags = IFF_BROADCAST;
    if (ifp->if_snd.ifq_maxlen == 0) {
        ifp->if_snd.ifq_maxlen = ifqmaxlen;
    }

    softc.rx_buf_idx = 0;

    /*
     * Attach the interface
     */
    if_attach (ifp);
    ether_ifattach (ifp);
    return 1;
}

void at91sam9x25_emac_init(void *arg)
{
		at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    at91sam9x25_emac_softc_t     *sc = arg;
    struct ifnet *ifp = &sc->arpcom.ac_if;
		uint32_t value;
    /*
     *This is for stuff that only gets done once (at91sam9x25_emac_init()
     * gets called multiple times
     */
    if (sc->txDaemonTid == 0) {
        /* Set up EMAC hardware */
        at91sam9x25_emac_init_hw(sc);

        /*      Start driver tasks */
        sc->rxDaemonTid = rtems_bsdnet_newproc("ENrx",
                                               4096,
                                               at91sam9x25_emac_rxDaemon,
                                               sc);
        sc->txDaemonTid = rtems_bsdnet_newproc("ENtx",
                                               4096,
                                               at91sam9x25_emac_txDaemon,
                                               sc);
    } /* if txDaemonTid */

    /* set our priority in the AIC */
    //AT91_AIC_SMR(AT91SAM9X5_ID_EMAC0) = (0);
    at91_sys_write(AT91_AIC_SMR(AT91SAM9X5_ID_EMAC0), 0);

    /* install the interrupt handler */
    BSP_install_rtems_irq_handler(&at91sam9x25_emac_isr_data);

    /* EMAC doesn't support promiscuous, so ignore requests */
    if (ifp->if_flags & IFF_PROMISC) {
        printk ("Warning - at91sam9x25 Ethernet driver"
                " doesn't support Promiscuous Mode!\n");
    }

    /*
     * Tell the world that we're running.
     */
    ifp->if_flags |= IFF_RUNNING;

    /* Enable TX/RX and clear the statistics counters */
    //emac->ctl = (AT91_EMAC_CTL_TE | AT91_EMAC_CTL_RE | AT91_EMAC_CTL_CSR);
		writel(AT91_EMAC_CTL_TE | AT91_EMAC_CTL_RE | AT91_EMAC_CTL_CSR,
			&emac->ctl);
    /* clear any pending interrupts */
    //emac->tsr = 0xffffffff;
    //emac->rsr = 0xffffffff;
    writel(0xffffffff, &emac->tsr);
    writel(0xffffffff, &emac->rsr);

} /* at91sam9x25_emac_init() */

void  at91sam9x25_emac_init_hw(at91sam9x25_emac_softc_t *sc)
{
	at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
	at91_pmc_t	*pmc		= (at91_pmc_t *) AT91_BASE_PMC;
	uint32_t value;
    int i;
#if 1
		/* Pins used for MII and RMII */
		at91_set_A_periph(AT91_PIN_PB4,  0);	/* ETXCK_EREFCK */
		at91_set_A_periph(AT91_PIN_PB3,  0);	/* ERXDV */
		at91_set_A_periph(AT91_PIN_PB0,  0);	/* ERX0 */
		at91_set_A_periph(AT91_PIN_PB1,  0);	/* ERX1 */
		at91_set_A_periph(AT91_PIN_PB2,  0);	/* ERXER */
		at91_set_A_periph(AT91_PIN_PB7,  0);	/* ETXEN */
		at91_set_A_periph(AT91_PIN_PB9,  0);	/* ETX0 */
		at91_set_A_periph(AT91_PIN_PB10, 0);	/* ETX1 */
		at91_set_A_periph(AT91_PIN_PB5,  0);	/* EMDIO */
		at91_set_A_periph(AT91_PIN_PB6,  0);	/* EMDC */
	#if 0
		if (!data->is_rmii) {
			at91_set_A_periph(AT91_PIN_PB16, 0);	/* ECRS */
			at91_set_A_periph(AT91_PIN_PB17, 0);	/* ECOL */
			at91_set_A_periph(AT91_PIN_PB13, 0);	/* ERX2 */
			at91_set_A_periph(AT91_PIN_PB14, 0);	/* ERX3 */
			at91_set_A_periph(AT91_PIN_PB15, 0);	/* ERXCK */
			at91_set_A_periph(AT91_PIN_PB11, 0);	/* ETX2 */
			at91_set_A_periph(AT91_PIN_PB12, 0);	/* ETX3 */
			at91_set_A_periph(AT91_PIN_PB8,  0);	/* ETXER */
		}
	#endif
	#if 0	
	//"AT91: Only RMII available on interface %s %d.\n"
		/* Pins used for RMII */
		at91_set_B_periph(AT91_PIN_PC29,  0);	/* ETXCK_EREFCK */
		at91_set_B_periph(AT91_PIN_PC28,  0);	/* ECRSDV */
		at91_set_B_periph(AT91_PIN_PC20,  0);	/* ERX0 */
		at91_set_B_periph(AT91_PIN_PC21,  0);	/* ERX1 */
		at91_set_B_periph(AT91_PIN_PC16,  0);	/* ERXER */
		at91_set_B_periph(AT91_PIN_PC27,  0);	/* ETXEN */
		at91_set_B_periph(AT91_PIN_PC18,  0);	/* ETX0 */
		at91_set_B_periph(AT91_PIN_PC19,  0);	/* ETX1 */
		at91_set_B_periph(AT91_PIN_PC31,  0);	/* EMDIO */
		at91_set_B_periph(AT91_PIN_PC30,  0);	/* EMDC */
	#endif
#endif

    /* Enable the clock to the EMAC */
    //PMC_REG(PMC_PCER) |= PMC_PCR_PID_EMAC;
    //at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9X5_ID_EMAC0);
    //at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9X5_ID_EMAC1);
    writel(1 << AT91SAM9X5_ID_EMAC0, &pmc->pcer); //pmc->pcer = 1 << AT91SAM9X5_ID_EMAC0;
		writel(readl(&emac->ctl) | AT91_EMAC_CTL_CSR, &emac->ctl);
		
    /* initialize our receive buffer descriptors */
    for (i = 0; i < NUM_RXBDS-1; i++) {
        rxbuf_hdrs[i].address = (unsigned long)(&rxbuf[i * RX_BUFFER_SIZE]);
        rxbuf_hdrs[i].status = 0x00000000;
    }

    /* last one needs the wrapbit set as well  */
    rxbuf_hdrs[i].address = ((unsigned long)(&rxbuf[i * RX_BUFFER_SIZE]) |
                             RXBUF_ADD_WRAP);
    rxbuf_hdrs[i].status = 0x00000000;

    /* point to our receive buffer queue */
    //EMAC_REG(EMAC_RBQP) = (unsigned long)rxbuf_hdrs;
		writel((unsigned long)rxbuf_hdrs, &emac->rbqp); //emac->rbqp = (unsigned long)rxbuf_hdrs;
		
    /* clear any left over status bits */
    //EMAC_REG(EMAC_RSR)  &= ~(EMAC_RSR_OVR | EMAC_RSR_REC | EMAC_RSR_BNA);
		writel(readl(&emac->rsr) &
			~(AT91_EMAC_RSR_OVR | AT91_EMAC_RSR_REC | AT91_EMAC_RSR_BNA),
			&emac->rsr);
		//emac->rsr &= ~(AT91_EMAC_RSR_OVR | AT91_EMAC_RSR_REC | AT91_EMAC_RSR_BNA);
    /* set the MII clock divder to MCK/64 */
    //EMAC_REG(EMAC_CFG) &= EMAC_CFG_CLK_MASK;
    //EMAC_REG(EMAC_CFG) = (EMAC_CFG_CLK_64 | EMAC_CFG_BIG | EMAC_CFG_FD);
		value = AT91_EMAC_CFG_CAF |	AT91_EMAC_CFG_NBC | AT91_EMAC_CFG_MCLK_64;
			//HCLK_DIV;
//#ifdef CONFIG_RMII
#if 1
		value |= AT91_EMAC_CFG_RMII;
#endif
		writel(value, &emac->cfg);
    /* enable the MII interface */
    //EMAC_REG(AT91_EMAC_CTL) = AT91_EMAC_CTL_MPE;
		//emac->ctl &= AT91_EMAC_CTL_MPE;
		writel(readl(&emac->ctl) | AT91_EMAC_CTL_TE | AT91_EMAC_CTL_RE,
			&emac->ctl);
		
    #if 1
    {
      int      timeout;
      uint32_t emac_link_status;

      #if defined(PHY_DBG)
        printk("EMAC: Getting Link Status.\n");
      #endif
      /* read the PHY ID registers */
      emac_link_status = phyread(0x02);
      emac_link_status = phyread(0x03);

      /* Get the link status - wait for done with a timeout */
      for (timeout = 10000 ; timeout ; ) {
	for (i = 0; i < 100; i++)
          ;
        emac_link_status = phyread(0x01);
        if (!(emac_link_status & PHY_STAT_AUTO_NEG_ABLE)) {
	  #if defined(PHY_DBG)
            printk("EMAC: PHY is unable to Auto-Negotatiate!\n");
          #endif
          timeout = 0;
          break;
        }
        if (emac_link_status & PHY_STAT_AUTO_NEG_DONE) {
	  #if defined(PHY_DBG)
	    printk("EMAC: Auto-Negotiate Complete, Link = ");
          #endif
          break;
        }
        timeout-- ;
      }
      if (!timeout) {
	#if defined(PHY_DBG)
	  printk(
           "EMAC: Auto-Negotatiate Failed, Status = 0x%04lx!\n"
	   "EMAC: Initialization Halted.\n",
           emac_link_status
          );
        #endif
        /* if autonegotiation fails, just force to 10HD... */
        emac_link_status = PHY_STAT_10BASE_HDX;
      }

      /* Set SPD and FD based on the return link status */
      if (emac_link_status & (PHY_STAT_100BASE_X_FDX | PHY_STAT_100BASE_X_HDX)){
        //EMAC_REG(EMAC_CFG) |= EMAC_CFG_SPD;
        writel(readl(&emac->cfg) | AT91_EMAC_CFG_SPD, &emac->cfg);
	#if defined(PHY_DBG)
          printk("100MBIT, ");
        #endif
      } else {
        //EMAC_REG(EMAC_CFG) &= ~EMAC_CFG_SPD;
        writel(readl(&emac->cfg) & ~AT91_EMAC_CFG_SPD, &emac->cfg);
	#if defined(PHY_DBG)
          printk("10MBIT, ");
        #endif
      }

      if (emac_link_status & (PHY_STAT_100BASE_X_FDX | PHY_STAT_10BASE_FDX)) {
        //EMAC_REG(EMAC_CFG) |= EMAC_CFG_FD;
        writel(readl(&emac->cfg) | AT91_EMAC_CFG_FD, &emac->cfg);
	#if defined(PHY_DBG)
          printk("Full Duplex.\n");
        #endif
      } else {
        //EMAC_REG(EMAC_CFG) &= ~EMAC_CFG_FD;
        writel(readl(&emac->cfg) & ~AT91_EMAC_CFG_FD, &emac->cfg);
	#if defined(PHY_DBG)
          printk("Half Duplex.\n");
        #endif
      }

      /* Set PHY LED modes.  Traffic Meter Mode for ACTLED
       * Set Bit 6 - Traffic Mode on
       */
      phywrite(0x1b, PHY_AUX_MODE2_TRAFFIC_LED);
    }
    #else
      /* must be csb337 */
      /* Set PHY LED2 to combined Link/Activity and enable pulse stretching */
      phywrite( 18, 0x0d0a );
    #endif

    #if 0
    emac->man = (0x01 << 30 |   /* Start of Frame Delimiter */
                          0x01 << 28 |   /* Operation, 0x01 = Write */
                          0x00 << 23 |   /* Phy Number */
                          0x14 << 18 |   /* Phy Register */
                          0x02 << 16 |   /* must be 0x02 */
                          0x0D0A);       /* Write data (0x0000 if read) */
   #endif

} /* at91sam9x25_emac_init_hw() */

void at91sam9x25_emac_start(struct ifnet *ifp)
{
    at91sam9x25_emac_softc_t *sc = ifp->if_softc;

    rtems_bsdnet_event_send(sc->txDaemonTid, START_TRANSMIT_EVENT);
    ifp->if_flags |= IFF_OACTIVE;
}

void at91sam9x25_emac_stop (at91sam9x25_emac_softc_t *sc)
{
		at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    struct ifnet *ifp = &sc->arpcom.ac_if;

    ifp->if_flags &= ~IFF_RUNNING;

    /*
     * Stop the transmitter and receiver.
     */
    //EMAC_REG(AT91_EMAC_CTL) &= ~(AT91_EMAC_CTL_TE | AT91_EMAC_CTL_RE);
    writel(readl(&emac->ctl) & ~(AT91_EMAC_CTL_TE | AT91_EMAC_CTL_RE), &emac->ctl);
}

/*
 * Driver transmit daemon
 */
void at91sam9x25_emac_txDaemon (void *arg)
{
		at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    at91sam9x25_emac_softc_t *sc = (at91sam9x25_emac_softc_t *)arg;
    struct ifnet *ifp = &sc->arpcom.ac_if;
    struct mbuf *m;
    rtems_event_set events;

    for (;;)
    {
        /* turn on TX interrupt, then wait for one */
        //EMAC_REG(EMAC_IER) = AT91_EMAC_IxR_TCOM;     /* Transmit complete */
        writel(AT91_EMAC_IxR_TCOM, &emac->ier);

        rtems_bsdnet_event_receive(
            START_TRANSMIT_EVENT,
            RTEMS_EVENT_ANY | RTEMS_WAIT,
            RTEMS_NO_TIMEOUT,
            &events);

        /* Send packets till queue is empty */
        for (;;)
        {
            /* Get the next mbuf chain to transmit. */
            IF_DEQUEUE(&ifp->if_snd, m);
            if (!m)
                break;
            at91sam9x25_emac_sendpacket (ifp, m);
        }
        ifp->if_flags &= ~IFF_OACTIVE;
    }
}

/* Send packet */
void at91sam9x25_emac_sendpacket (struct ifnet *ifp, struct mbuf *m)
{
    at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    struct mbuf *l = NULL;
    unsigned int pkt_offset = 0;
    delay_cnt = 0;
    /* printk("at91sam9x25_emac_sendpacket %p\n", m); */

    /* Wait for EMAC Transmit Queue to become available. */
    //while (!(readl(&emac->tsr) & AT91_EMAC_TSR_BNQ));
		
    while (((readl(&emac->tsr) & AT91_EMAC_TSR_COMP) == 0) &&
           ((readl(&emac->tsr) & AT91_EMAC_TSR_TXIDLE) == 0))

    {
        delay_cnt++;
/*        sleep(0);       make sure we don't hog the cpu */
        continue;
    }

    /* copy the mbuf chain into the transmit buffer */
    l = m;
    while (l != NULL) {
        memcpy(((char *)txbuf + pkt_offset),  /* offset into pkt for mbuf */
               (char *)mtod(l, void *),       /* cast to void */
               l->m_len);                     /* length of this mbuf */

        pkt_offset += l->m_len;               /* update offset */
        l = l->m_next;                        /* get next mbuf, if any */
    }

    /* free the mbuf chain we just copied */
    m_freem(m);

    /* clear any pending status */
    writel((AT91_EMAC_TSR_OVR | AT91_EMAC_TSR_COL | AT91_EMAC_TSR_RLE
                          | AT91_EMAC_TSR_COMP | AT91_EMAC_TSR_UND), &emac->tsr);

    /* tell the EMAC about our buffer */
    writel((unsigned long)txbuf, &emac->tar);
    writel((unsigned long)pkt_offset, &emac->tcr);
} /* at91sam9x25_emac_sendpacket () */


/* SONIC reader task */
void at91sam9x25_emac_rxDaemon(void *arg)
{
    at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    at91sam9x25_emac_softc_t *sc = (at91sam9x25_emac_softc_t *)arg;
    struct ifnet *ifp = &sc->arpcom.ac_if;
    struct mbuf *m;
    struct ether_header *eh;
    rtems_event_set events;
    int pktlen;

    /* Input packet handling loop */
    for (;;) {
        /* turn on RX interrupts, then wait for one */
        writel((AT91_EMAC_IxR_RCOM |   /* Receive complete */
                              AT91_EMAC_IxR_RBNA |   /* Receive buf not available */
                              AT91_EMAC_IxR_ROVR)   /* Receive overrun */
                              , &emac->ier);

        rtems_bsdnet_event_receive(
            START_RECEIVE_EVENT,
            RTEMS_EVENT_ANY | RTEMS_WAIT,
            RTEMS_NO_TIMEOUT,
            &events);

        if (readl(&emac->rsr) & AT91_EMAC_RSR_BNA) {
            printk("1: EMAC_BNA\n");
        }

        if (readl(&emac->rsr) & AT91_EMAC_RSR_OVR) {
            printk("1: EMAC_OVR\n");
        }

        /* clear the receive status as we do not use it anyway */
        writel((AT91_EMAC_RSR_REC | AT91_EMAC_RSR_OVR | AT91_EMAC_RSR_BNA)
        	, &emac->rsr);

        /* scan the buffer descriptors looking for any with data in them */
        while (rxbuf_hdrs[sc->rx_buf_idx].address & RXBUF_ADD_OWNED) {
            pktlen = rxbuf_hdrs[sc->rx_buf_idx].status & RXBUF_STAT_LEN_MASK;

            /* get an mbuf this packet */
            MGETHDR(m, M_WAIT, MT_DATA);

            /* now get a cluster pointed to by the mbuf */
            /* since an mbuf by itself is too small */
            MCLGET(m, M_WAIT);

            /* set the type of mbuf to ifp (ethernet I/F) */
            m->m_pkthdr.rcvif = ifp;
            m->m_nextpkt = 0;

            /* copy the packet into the cluster pointed to by the mbuf */
            memcpy((char *)m->m_ext.ext_buf,
                   (char *)(rxbuf_hdrs[sc->rx_buf_idx].address & 0xfffffffc),
                   pktlen);

            /* Release the buffer ASAP back to the EMAC */
            rxbuf_hdrs[sc->rx_buf_idx].address &= ~RXBUF_ADD_OWNED;

            /* set the length of the mbuf */
            m->m_len = pktlen - (sizeof(struct ether_header) + 4);
            m->m_pkthdr.len = m->m_len;

            /* strip off the ethernet header from the mbuf */
            /* but save the pointer to it */
            eh = mtod (m, struct ether_header *);
            m->m_data += sizeof(struct ether_header);

            /* increment the buffer index */
            sc->rx_buf_idx++;
            if (sc->rx_buf_idx >= NUM_RXBDS) {
                sc->rx_buf_idx = 0;
            }

            /* give all this stuff to the stack */
            ether_input(ifp, eh, m);

        } /* while ADD_OWNED = 0 */

        if (readl(&emac->rsr) & AT91_EMAC_RSR_BNA) {
            printk("2:EMAC_BNA\n");
        }
        if (readl(&emac->rsr) & AT91_EMAC_RSR_OVR) {
            printk("2:EMAC_OVR\n");
        }


    } /* for (;;) */
} /* at91sam9x25_emac_rxDaemon() */


/* Show interface statistics */
void at91sam9x25_emac_stats (at91sam9x25_emac_softc_t *sc)
{
    printf (" Total Interrupts:%-8lu",          sc->Interrupts);
    printf ("    Rx Interrupts:%-8lu",          sc->rxInterrupts);
    printf ("            Giant:%-8lu",          sc->rxGiant);
    printf ("        Non-octet:%-8lu\n",                sc->rxNonOctet);
    printf ("          Bad CRC:%-8lu",          sc->rxBadCRC);
    printf ("        Collision:%-8lu",          sc->rxCollision);
    printf ("           Missed:%-8lu\n",                sc->rxMissed);

    printf (    "    Tx Interrupts:%-8lu",      sc->txInterrupts);
    printf (  "           Deferred:%-8lu",      sc->txDeferred);
    printf ("        Lost Carrier:%-8lu\n",     sc->txLostCarrier);
    printf (   "Single Collisions:%-8lu",       sc->txSingleCollision);
    printf ( "Multiple Collisions:%-8lu",       sc->txMultipleCollision);
    printf ("Excessive Collisions:%-8lu\n",     sc->txExcessiveCollision);
    printf (   " Total Collisions:%-8lu",       sc->txCollision);
    printf ( "     Late Collision:%-8lu",       sc->txLateCollision);
    printf ("            Underrun:%-8lu\n",     sc->txUnderrun);
    printf (   "  Raw output wait:%-8lu\n",     sc->txRawWait);
}


/* Enables at91sam9x25_emac interrupts. */
static void at91sam9x25_emac_isr_on(const rtems_irq_connect_data *unused)
{
		at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    /* Enable various TX/RX interrupts */
    writel((AT91_EMAC_IxR_RCOM | /* Receive complete */
                          AT91_EMAC_IxR_RBNA | /* Receive buffer not available */
                          AT91_EMAC_IxR_TCOM | /* Transmit complete */
                          AT91_EMAC_IxR_ROVR | /* Receive overrun */
                          AT91_EMAC_IxR_HRESP)  /* Abort on DMA transfer */
                          , &emac->ier);

    return;
}

/* Disables at91sam9x25_emac interrupts */
static void at91sam9x25_emac_isr_off(const rtems_irq_connect_data *unused)
{
		at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    /* disable all various TX/RX interrupts */
    //EMAC_REG(EMAC_IDR) = 0xffffffff;
    writel(0xffffffff, &emac->idr); 
    return;
}

/* Tests to see if at91sam9x25_emac interrupts are enabled, and
 * returns non-0 if so.
 * If interrupt is not enabled, returns 0.
 */
static int at91sam9x25_emac_isr_is_on(const rtems_irq_connect_data *irq)
{
    at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    return readl(&emac->imr);  /* any interrupts enabled? */
}

/*  Driver ioctl handler */
static int
at91sam9x25_emac_ioctl (struct ifnet *ifp, ioctl_command_t command, caddr_t data)
{
    at91sam9x25_emac_softc_t *sc = ifp->if_softc;
    int error = 0;

    switch (command) {
    case SIOCGIFADDR:
    case SIOCSIFADDR:
        ether_ioctl (ifp, command, data);
        break;

    case SIOCSIFFLAGS:
        switch (ifp->if_flags & (IFF_UP | IFF_RUNNING))
        {
        case IFF_RUNNING:
            at91sam9x25_emac_stop (sc);
            break;

        case IFF_UP:
            at91sam9x25_emac_init (sc);
            break;

        case IFF_UP | IFF_RUNNING:
            at91sam9x25_emac_stop (sc);
            at91sam9x25_emac_init (sc);
            break;

        default:
            break;
        } /* switch (if_flags) */
        break;

    case SIO_RTEMS_SHOW_STATS:
        at91sam9x25_emac_stats (sc);
        break;

        /*
         * FIXME: All sorts of multicast commands need to be added here!
         */
    default:
        error = EINVAL;
        break;
    } /* switch (command) */
    return error;
}

/* interrupt handler */
static void at91sam9x25_emac_isr (rtems_irq_hdl_param unused)
{
    at91_emac_t	*emac		= (at91_emac_t *) AT91_BASE_EMAC0;
    unsigned long status32;

    /* get the ISR status and determine RX or TX */
    status32 = readl(&emac->isr);

    if (status32 & AT91_EMAC_IxR_HRESP) {
        writel(AT91_EMAC_IxR_HRESP, &emac->idr); /* disable it */
        //rtems_panic("at91sam9x25 Ethernet MAC has received an Abort.\n");
        rtems_panic("at91sam9x25 Ethernet MAC - DMA bus error: HRESP not OK.\n");
    }

    if (status32 & (AT91_EMAC_IxR_RCOM |    /* Receive complete */
                    AT91_EMAC_IxR_RBNA |    /* Receive buffer not available */
                    AT91_EMAC_IxR_ROVR)) {  /* Receive overrun */

        /* disable the RX interrupts */
        writel((AT91_EMAC_IxR_RCOM |  /* Receive complete */
                              AT91_EMAC_IxR_RBNA |  /* Receive buf not available */
                              AT91_EMAC_IxR_ROVR)  /* Receive overrun */
                              , &emac->idr);

        rtems_bsdnet_event_send (softc.rxDaemonTid, START_RECEIVE_EVENT);
    }

    if (status32 & AT91_EMAC_IxR_TCOM) {      /* Transmit buffer register empty */

        /* disable the TX interrupts */
        //EMAC_REG(EMAC_IDR) = AT91_EMAC_IxR_TCOM;
        writel(AT91_EMAC_IxR_TCOM, &emac->idr);

        rtems_bsdnet_event_send (softc.txDaemonTid, START_TRANSMIT_EVENT);
    }
}
#endif
