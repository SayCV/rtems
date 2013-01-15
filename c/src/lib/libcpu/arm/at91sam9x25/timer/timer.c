/*
 * Cogent CSB337 Timer driver
 *
 * This uses timer 0 for timing measurments.
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 * Notes:
 *  This file manages the benchmark timer used by the RTEMS Timing Test
 *  Suite.  Each measured time period is demarcated by calls to
 *  benchmark_timer_initialize() and benchmark_timer_read().  benchmark_timer_read() usually returns
 *  the number of microseconds since benchmark_timer_initialize() exitted.
 *
 *  It is important that the timer start/stop overhead be determined
 *  when porting or modifying this code.
 */

#include <rtems.h>
#include <bsp.h>
#include <at91sam9x5.h>
#include <at91_io.h>
#include <at91_tc.h>
#include <at91_pmc.h>
#include <at91_clk.h>

#define AT91SAM9X5_BASE_TC0		0xf8008000
//#define AT91_TC0 (AT91SAM9X5_BASE_TC0 - AT91_BASE_SYS)
#define AT91_TC0 AT91SAM9X5_BASE_TC0

uint16_t tstart;
bool benchmark_timer_find_average_overhead;
uint32_t tick_time;
/*
 * Set up TC0 -
 *   timer_clock2 (MCK/8)
 *   capture mode - this shouldn't matter
 */
void benchmark_timer_initialize( void )
{
    at91_tc_t *tc = (at91_tc_t *) AT91SAM9X5_BASE_TC0;
    uint32_t tmr_freq;

    /* since we are using timer_clock2, divide mck by 8 */
    tmr_freq = get_mck_clk_rate() / 8;

	writel(AT91_TC_TIMER_CLOCK2, &tc->cmr);
	writel(AT91_TC_CLKEN | AT91_TC_SWTRG, &tc->ccr);
	//TC_TC0_REG(TC_CMR) = TC_CMR_TCCLKS(1);   /* timer_clock2 */
    //TC_TC0_REG(TC_CCR) = (TC_CCR_CLKEN       /* enable the counter */
    //                      | TC_CCR_SWTRG);   /* start it up */

    /* tick time in nanoseconds */
    tick_time = 1000000000/tmr_freq;

}

/*
 *  The following controls the behavior of benchmark_timer_read().
 *
 *  AVG_OVEREHAD is the overhead for starting and stopping the timer.  It
 *  is usually deducted from the number returned.
 *
 *  LEAST_VALID is the lowest number this routine should trust.  Numbers
 *  below this are "noise" and zero is returned.
 */

#define AVG_OVERHEAD      0  /* It typically takes X.X microseconds */
                             /* (Y countdowns) to start/stop the timer. */
                             /* This value is in microseconds. */
#define LEAST_VALID       1  /* Don't trust a clicks value lower than this */

int benchmark_timer_read( void )
{
  at91_tc_t *tc = (at91_tc_t *) AT91SAM9X5_BASE_TC0;
  uint16_t t;
  uint32_t total;
  t = readl(&tc->cv);//TC_TC0_REG(TC_CV);

  /*
   *  Total is calculated by taking into account the number of timer overflow
   *  interrupts since the timer was initialized and clicks since the last
   *  interrupts.
   */

  total = t * tick_time;

  if ( benchmark_timer_find_average_overhead == 1 )
    return total;          /* in nanosecond units */
  else {
    if ( total < LEAST_VALID )
      return 0;            /* below timer resolution */
  /*
   *  Somehow convert total into microseconds
   */
      return (total - AVG_OVERHEAD);
    }
}

void benchmark_timer_disable_subtracting_average_overhead(bool find_flag)
{
  benchmark_timer_find_average_overhead = find_flag;
}

