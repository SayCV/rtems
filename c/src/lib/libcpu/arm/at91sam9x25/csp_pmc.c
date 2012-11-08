/*
 * Atmel CSP_PMC PMC functions
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <rtems.h>
#include <bsp.h>
#include <csp.h>

int CSP_PMC_get_mainclk(void)
{
    return BSP_MAIN_FREQ;
}

int CSP_PMC_get_slck(void)
{
    return BSP_SLCK_FREQ;
}

CPU_INT32U  CSP_PMC_get_pllclk (CPU_INT08U  pll_id)
{
    CPU_INT08U  pll_div;
    CPU_INT16U  pll_mul;
    CPU_INT32U  pll_freq;
  CPU_INT32U cpu_plladiv2;
                                                                /* ---------------- ARGUMENTS CHECKING -------------- */    
    if ((pll_id != CSP_PMC_PLL_ID_PLLA) &&
        (pll_id != CSP_PMC_PLL_ID_PLLB)) {
        return (0);
    }
    
    if (pll_id == CSP_PMC_PLL_ID_PLLA) {
        pll_div = ((CSP_PMC_REG->CKGR_PLLAR >>  0) & 0x0FF);
        pll_mul = ((CSP_PMC_REG->CKGR_PLLAR >> 16) & 0x7FF);       
    }     
    if (pll_id == CSP_PMC_PLL_ID_PLLB) {
      pll_div = ((CSP_PMC_REG->PMC_USB >>  8) & 0x0F);
      if( ((CSP_PMC_REG->PMC_USB >>  0) & 0x01) ) {
        pll_freq = CSP_PMC_get_pllclk(CSP_PMC_PLL_ID_PLLA) / ( pll_div + 1);
      } else {
        pll_freq = AT91C_MASTER_CLOCK / ( pll_div + 1);
      }
      return (pll_freq); 
    }
               
    if (pll_div != 0) {
        pll_freq  = ((CSP_CFG_PMC_MAIN_XTAL_FREQ_HZ / 100) * (pll_mul + 1)) / pll_div;    
        pll_freq *= 100;
    }
    cpu_plladiv2  = (CSP_PMC_REG->PMC_MCKR >> 12) & 0x00000001;
    cpu_plladiv2  = (1<<cpu_plladiv2);
    pll_freq /= cpu_plladiv2;
    return (pll_freq);        
}

CPU_INT32U  CSP_PMC_get_cpuclk (void)
{
    CPU_INT32U  cpu_css;
    CPU_INT32U  cpu_pres;
    CPU_INT32U  cpu_mdiv;
    CPU_INT32U  cpu_plladiv2;
    CPU_INT32U  cpu_freq;
    
    (void)&cpu_mdiv;
    
    cpu_css  = (CSP_PMC_REG->PMC_MCKR     ) & 0x00000003;    /* Get the master clk source                          */
    cpu_pres = (CSP_PMC_REG->PMC_MCKR >> 4) & 0x00000007;
    cpu_mdiv  = (CSP_PMC_REG->PMC_MCKR >> 8) & 0x00000003;    /* Get the cpu clk preescaler                         */
    cpu_plladiv2  = (CSP_PMC_REG->PMC_MCKR >> 12) & 0x00000001;
    cpu_pres  = (1<<cpu_pres);                                  /* Convert the Processor clk pres (1, 2, 4, 8, etc)   */
    cpu_plladiv2  = (1<<cpu_plladiv2);
      
    switch (cpu_css) {
        case 0x00:                             
             cpu_freq = BSP_SLCK_FREQ;                /* Slow clock                                         */
             break;

        case 0x01:                                               
             cpu_freq = BSP_MAIN_FREQ;                /* Main clock                                         */
             break;

        case 0x02:                                                /* PLL A clock                                        */
             cpu_freq = CSP_PMC_get_pllclk(CSP_PMC_PLL_ID_PLLA);
             break;

        case 0x03:                                                /* UPLL clock                                      */
             cpu_freq = CSP_PMC_get_pllclk(CSP_PMC_PLL_ID_PLLB);
             break;

        default:
             cpu_freq = 0;
             break;             
    }
    //cpu_freq /= cpu_plladiv2;cpu_plladiv2  = DEF_BIT(cpu_plladiv2);cpu_plladiv2  = (CSP_PMC_REG->PMC_MCKR >> 12) & 0x00000001;
    cpu_freq /= cpu_pres;
    

    return (cpu_freq);
    //return 
}

int CSP_PMC_get_mclk(void)
{
    CPU_INT32U  mclk_freq;
    CPU_INT08U  mclk_div;

    
    mclk_freq = CSP_PMC_get_cpuclk();
    mclk_div  = ((CSP_PMC_REG->PMC_MCKR >> 8) & 0x03);     /* Read the Master Clock divider                      */
#if defined(CONFIG_AT91SAM9260) || 0
    mclk_div  = (1<<mclk_div);
    mclk_freq /= mclk_div;
#elif defined(CONFIG_AT91SAM9X5) || 1
    mclk_freq = mclk_div == ( 1 | 2 ) 
      ? mclk_freq / 3
      : mclk_freq / (1<<mclk_div);
#endif
    return mclk_freq;
}

