include $(top_srcdir)/automake/compile.am

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = rtems/asm.h

include_rtems_scoredir = $(includedir)/rtems/score
include_rtems_score_HEADERS  = rtems/score/cpu.h
include_rtems_score_HEADERS += rtems/score/v850.h
include_rtems_score_HEADERS += rtems/score/cpu_asm.h rtems/score/types.h

noinst_LIBRARIES = libscorecpu.a
libscorecpu_a_SOURCES  = cpu.c
libscorecpu_a_SOURCES += cpu_asm.S
libscorecpu_a_SOURCES += v850-exception-frame-print.c
libscorecpu_a_CPPFLAGS = $(AM_CPPFLAGS)

include $(srcdir)/preinstall.am
include $(top_srcdir)/automake/local.am
