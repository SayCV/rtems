/*
 *  COPYRIGHT (c) 1989-2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <timesys.h>
#include <rtems/timerdrv.h>
#include "test_support.h"

void *POSIX_Init(
  void *argument
)
{
  long end_time;
  struct timespec sleepTime;
  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = 0;

  puts( "\n\n*** POSIX TIME TEST PSXTMNANOSLEEP01 ***" );

  benchmark_timer_initialize();    

  nanosleep(&sleepTime, (struct  timespec *) NULL);

  end_time = benchmark_timer_read();  

  put_time("nanosleep - yield X ",end_time,OPERATION_COUNT,0,0);

  puts( "*** END OF POSIX TIME TEST PSXTMNANOSLEEP01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER

#define CONFIGURE_MAXIMUM_POSIX_THREADS     1
#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */