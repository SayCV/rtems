/*
 *  AT91RM9200 clock specific using the System Timer
 *
 *  Copyright (c) 2003 by Cogent Computer Systems
 *  Written by Mike Kelly <mike@cogcomp.com>
 *         and Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <rtems.h>
#include <rtems/clockdrv.h>
#include <rtems/libio.h>

#include <stdlib.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <csp.h>

static unsigned long st_pimr_reload;

/**
 * Enables clock interrupt.
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_on(const rtems_irq_connect_data *unused)
{
  /* enable timer interrupt */
  //ST_REG(ST_IER) = ST_SR_PITS;
  CPU_REG_PIT_MR |= CPU_REG_PIT_MR_PITIEN;
}

/**
 * Disables clock interrupts
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_off(const rtems_irq_connect_data *unused)
{
  /* disable timer interrupt */
  //ST_REG(ST_IDR) = ST_SR_PITS;
  CPU_REG_PIT_MR &= ~CPU_REG_PIT_MR_PITIEN;
}

/**
 * Tests to see if clock interrupt is enabled, and returns 1 if so.
 * If interrupt is not enabled, returns 0.
 *
 * If the interrupt is always on, this always returns 1.
 */
static int clock_isr_is_on(const rtems_irq_connect_data *irq)
{
  /* check timer interrupt */
  //return ST_REG(ST_IMR) & ST_SR_PITS;
  return CPU_REG_PIT_MR & CPU_REG_PIT_MR_PITIEN;
}

void Clock_isr(rtems_irq_hdl_param arg);

/* Replace the first value with the clock's interrupt name. */
rtems_irq_connect_data clock_isr_data = {
  .name   = CSP_INT_SRC_NBR_SYS,
  .hdl    = Clock_isr,
  .handle = NULL,
  .on     = clock_isr_on,
  .off    = clock_isr_off,
  .isOn   = clock_isr_is_on,
};


#define Clock_driver_support_install_isr( _new, _old ) \
  do {                                                 \
      (_old) = NULL;                                   \
      BSP_install_rtems_irq_handler(&clock_isr_data);  \
  } while(0)

uint16_t st_pimr_value;
void Clock_driver_support_initialize_hardware(void)
{
  uint32_t st_str;
  int mclk;

  /* the system timer is driven from SLCK */
  mclk = CSP_PMC_get_mclk();
  st_pimr_value = (((rtems_configuration_get_microseconds_per_tick() * mclk / 16) +
                      (1000000/2))/ 1000000);
  st_pimr_reload = st_pimr_value;

  /* read the status to clear the int */
  st_str = CPU_REG_PIT_PIVR;

  /* set priority */
  //AIC_SMR_REG(AIC_SMR_SYSIRQ) = AIC_SMR_PRIOR(0x7);
	//CSP_INT_AIC_SMR(CSP_INT_SRC_NBR_SYS) = (src_prio) | (aic_scr_type << 5);
	
  /* set the timer value */
  //ST_REG(ST_PIMR) = st_pimr_reload;
	CPU_REG_PIT_MR = CPU_REG_PIT_MR_PITEN
                  | CPU_REG_PIT_MR_PITIEN
                  | (st_pimr_value - 1u);
}

uint32_t bsp_clock_nanoseconds_since_last_tick(void)
{
  uint16_t slck_counts;

  slck_counts = st_pimr_value - st_pimr_reload;
  return (rtems_configuration_get_microseconds_per_tick() * slck_counts * 1000)
     / st_pimr_value;
}

#define Clock_driver_nanoseconds_since_last_tick \
  bsp_clock_nanoseconds_since_last_tick

#define Clock_driver_support_at_tick() \
  do { \
    uint32_t st_str; \
    \
    /* read the status to clear the int */ \
    st_str = CPU_REG_PIT_PIVR; \
  } while (0)

void Clock_driver_support_shutdown_hardware( void )
{
  BSP_remove_rtems_irq_handler(&clock_isr_data);
}

#include "../../../../libbsp/shared/clockdrv_shell.h"
