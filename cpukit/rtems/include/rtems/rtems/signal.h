/**
 * @file rtems/rtems/signal.h
 *
 * @defgroup ClassicSignal Signals
 *
 * @ingroup ClassicRTEMS
 * @brief Signal Manager
 *
 * This include file contains all the constants and structures associated
 * with the Signal Manager. This manager provides capabilities required
 * for asynchronous communication between tasks via signal sets.
 *
 * Directives provided are:
 *
 * + establish an asynchronous signal routine
 * + send a signal set to a task
 */

/* COPYRIGHT (c) 1989-2008.
 * On-Line Applications Research Corporation (OAR).
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef _RTEMS_RTEMS_SIGNAL_H
#define _RTEMS_RTEMS_SIGNAL_H

/**
 *  @defgroup ClassicSignal Signals
 *
 *  @ingroup ClassicRTEMS
 *
 *  This encapsulates functionality which XXX
 */
/**@{*/

#include <rtems/rtems/asr.h>
#include <rtems/rtems/modes.h>
#include <rtems/score/object.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/types.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 *  @brief Signal Manager Initialization
 *
 *  Signal Manager
 *
 *  This routine performs the initialization necessary for this manager.
 */
void _Signal_Manager_initialization( void );

/**
 * @brief RTEMS Catch Signal
 *
 * This routine implements the rtems_signal_catch directive. This directive
 * is used to establish asr_handler as the Asynchronous Signal Routine
 * (RTEMS_ASR) for the calling task. The asr_handler will execute with a
 * mode of mode_set.
 *
 * @param[in] asr_handler is the address of asynchronous signal routine (asr)
 *            ( NULL indicates asr is invalid )
 * @param[in] mode_set is the mode value for asr
 *
 * @retval RTEMS_SUCCESSFUL
 */
rtems_status_code rtems_signal_catch(
  rtems_asr_entry   asr_handler,
  rtems_mode        mode_set
);

/**
 * @brief RTEMS Send Signal
 *
 * This routine implements the rtems_signal_send directive. This directive
 * sends the signal_set to the task specified by ID.
 *
 * @param[in] id is the thread thread id
 * @param[in] signal_set is the signal set
 *
 * @retval RTEMS_SUCCESSFUL if successful or error code if unsuccessful
 */
rtems_status_code rtems_signal_send(
  rtems_id         id,
  rtems_signal_set signal_set
);

#if defined(RTEMS_MULTIPROCESSING)
#include <rtems/rtems/signalmp.h>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
