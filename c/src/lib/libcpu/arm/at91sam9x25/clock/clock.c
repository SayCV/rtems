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
#include <at91sam9x5.h>
#include <at91_pit.h>
#include <at91_pmc.h>
#include <at91_clk.h>


static unsigned long pit_mr_reload;

/**
 * Enables clock interrupt.
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_on(const rtems_irq_connect_data *unused)
{
  /* enable timer interrupt */
  //ST_REG(ST_IER) = ST_SR_PITS;
  uint32_t pit_mr_str;
  pit_mr_str = at91_sys_read(AT91_PIT_MR);
  at91_sys_write(AT91_PIT_MR, pit_mr_str | AT91_PIT_PITIEN);
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
  uint32_t pit_mr_str;
  pit_mr_str = at91_sys_read(AT91_PIT_MR);
  at91_sys_write(AT91_PIT_MR, pit_mr_str & (~AT91_PIT_PITIEN));
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
  return at91_sys_read(AT91_PIT_MR) & AT91_PIT_PITS;//ST_REG(ST_IMR) & ST_SR_PITS;
}

void Clock_isr(rtems_irq_hdl_param arg);

/* Replace the first value with the clock's interrupt name. */
rtems_irq_connect_data clock_isr_data = {
  .name   = AT91_ID_SYS,
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

uint16_t pit_mr_value;
void Clock_driver_support_initialize_hardware(void)
{
  uint32_t pit_pivr_str;
  int mclk_freq;

  /* the system timer is driven from SLCK */
  mclk_freq = get_mck_clk_rate();
  //pit_mr_value = (((rtems_configuration_get_microseconds_per_tick() * slck) +
  //                    (1000000/2))/ 1000000);
  pit_mr_value      = (mclk_freq) / 16 / rtems_configuration_get_microseconds_per_tick() - 1;			/* 1 ticks = 1000us */
  pit_mr_reload = pit_mr_value;

  /* read the status to clear the int */
  //st_str = ST_REG(ST_SR);
  pit_pivr_str = at91_sys_read(AT91_PIT_PIVR);

  /* set priority */
  //AIC_SMR_REG(AIC_SMR_SYSIRQ) = AIC_SMR_PRIOR(0x7);
  at91_sys_write(AT91_AIC_SMR(AT91_ID_SYS), 0x7);

  /* set the timer value */
  //ST_REG(ST_PIMR) = st_pimr_reload;
  at91_sys_write(AT91_PIT_MR, pit_mr_reload | AT91_PIT_PITEN);
}

uint32_t bsp_clock_nanoseconds_since_last_tick(void)
{
  uint16_t tick_counts;

  tick_counts = pit_mr_value - pit_mr_reload;//return 0;
  return (rtems_configuration_get_microseconds_per_tick() * tick_counts * 1000)
     / pit_mr_value;
}

#define Clock_driver_nanoseconds_since_last_tick \
  bsp_clock_nanoseconds_since_last_tick

#define Clock_driver_support_at_tick() \
  do { \
    uint32_t pit_pivr_str; \
    \
    /* read the status to clear the int */ \
    pit_pivr_str = at91_sys_read(AT91_PIT_PIVR); \
  } while (0)

void Clock_driver_support_shutdown_hardware( void )
{
  BSP_remove_rtems_irq_handler(&clock_isr_data);
}

#include "../../../../libbsp/shared/clockdrv_shell.h"
