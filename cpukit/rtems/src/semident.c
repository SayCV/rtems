/**
 *  @file
 *
 *  @brief RTEMS Semaphore Name to Id
 *  @ingroup ClassicSem
 */

/*
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>
#include <rtems/rtems/attr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/rtems/options.h>
#include <rtems/rtems/sem.h>
#include <rtems/score/coremutex.h>
#include <rtems/score/coresem.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/threadq.h>
#if defined(RTEMS_MULTIPROCESSING)
#include <rtems/score/mpci.h>
#endif
#include <rtems/score/sysstate.h>

#include <rtems/score/interr.h>

rtems_status_code rtems_semaphore_ident(
  rtems_name  name,
  uint32_t    node,
  rtems_id   *id
)
{
  Objects_Name_or_id_lookup_errors  status;

  status = _Objects_Name_to_id_u32( &_Semaphore_Information, name, node, id );

  return _Status_Object_name_errors_to_status[ status ];
}
