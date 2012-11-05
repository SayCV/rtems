ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

###############################################################################
#                  Data                                                       #
###############################################################################

dist_project_lib_DATA = bsp_specs

noinst_LIBRARIES = libbspstart.a

libbspstart_a_SOURCES = start/start.S

project_lib_DATA =
project_lib_DATA += start.$(OBJEXT)
project_lib_DATA += startup/linkcmds

EXTRA_DIST = startup/linkcmds.SayCV_SAM9X25
EXTRA_DIST += README

###############################################################################
#                  Header                                                     #
###############################################################################

include_HEADERS =
include_HEADERS += ../../shared/include/tm27.h
include_HEADERS += include/bsp.h
if ENABLE_LCD
include_HEADERS += include/sed1356.h
endif

nodist_include_HEADERS =
nodist_include_HEADERS += ../../shared/include/coverhd.h
nodist_include_HEADERS += include/bspopts.h
if ENABLE_LCD
nodist_include_HEADERS += console/sed1356_16bit.h
nodist_include_HEADERS += console/font8x16.h
endif

if ENABLE_UMON
include_umondir = $(includedir)/umon
include_umon_HEADERS  = ../../shared/umon/cli.h
include_umon_HEADERS += ../../shared/umon/monlib.h
include_umon_HEADERS += ../../shared/umon/tfs.h

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS  = ../../shared/umon/umon.h
endif

nodist_include_bsp_HEADERS =
nodist_include_bsp_HEADERS += ../../shared/include/bootcard.h

include_bsp_HEADERS =
include_bsp_HEADERS += ../../shared/include/utility.h
include_bsp_HEADERS += ../../shared/include/irq-generic.h
include_bsp_HEADERS += ../../shared/include/irq-info.h
include_bsp_HEADERS += ../../shared/include/stackalloc.h
include_bsp_HEADERS += ../../shared/tod.h
include_bsp_HEADERS += ../shared/include/start.h

noinst_PROGRAMS =

###############################################################################
#                  LibBSP                                                     #
###############################################################################

noinst_LIBRARIES += libbsp.a

libbsp_a_SOURCES =
libbsp_a_CPPFLAGS =
libbsp_a_LIBADD =

# Shared
libbsp_a_SOURCES += ../../shared/bootcard.c
libbsp_a_SOURCES += ../../shared/bspclean.c
libbsp_a_SOURCES += ../../shared/bspgetworkarea.c
libbsp_a_SOURCES += ../../shared/bsplibc.c
libbsp_a_SOURCES += ../../shared/bsppost.c
libbsp_a_SOURCES += ../../shared/bsppredriverhook.c
libbsp_a_SOURCES += ../../shared/bsppretaskinghook.c
libbsp_a_SOURCES += ../../shared/gnatinstallhandler.c
libbsp_a_SOURCES += ../../shared/sbrk.c
libbsp_a_SOURCES += ../../shared/src/stackalloc.c

# Startup
libbsp_a_SOURCES += startup/bspstart.c
libbsp_a_SOURCES += startup/bspreset.c
libbsp_a_SOURCES += startup/memmap.c

# Console
libbsp_a_SOURCES += ../../shared/console.c
libbsp_a_SOURCES += console/uarts.c
libbsp_a_SOURCES += ../../shared/console_select.c
libbsp_a_SOURCES += ../../shared/console_control.c
libbsp_a_SOURCES += ../../shared/console_read.c
libbsp_a_SOURCES += ../../shared/console_write.c

# IRQ
libbsp_a_SOURCES += ../../shared/src/irq-default-handler.c
libbsp_a_SOURCES += ../../shared/src/irq-generic.c
libbsp_a_SOURCES += ../../shared/src/irq-info.c
libbsp_a_SOURCES += ../../shared/src/irq-legacy.c
libbsp_a_SOURCES += ../../shared/src/irq-server.c
libbsp_a_SOURCES += ../../shared/src/irq-shell.c

if ENABLE_LCD
libbsp_a_SOURCES += console/sed1356.c console/fbcons.c
endif

# Abort
libbsp_a_SOURCES += ../shared/abort/abort.c

# UMON
if ENABLE_UMON
libbsp_a_SOURCES += ../../shared/umon/umonrtemsglue.c  \
    ../../shared/umon/monlib.c ../../shared/umon/tfsDriver.c \
    ../../shared/umon/umoncons.c startup/umonsupp.c
endif
if ENABLE_UMON_CONSOLE
libbsp_a_SOURCES += ../../shared/umon/umoncons.c
endif

# Network
if HAS_NETWORKING
network_CPPFLAGS = -D__INSIDE_RTEMS_BSD_TCPIP_STACK__
noinst_PROGRAMS += network.rel
network_rel_SOURCES = network/network.c
network_rel_CPPFLAGS = $(AM_CPPFLAGS) $(network_CPPFLAGS)
network_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

libbsp_a_LIBADD = ../../../libcpu/@RTEMS_CPU@/shared/arm920.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/clock.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/dbgu.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/usart.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/timer.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/pmc.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/irq.rel
if HAS_NETWORKING
libbsp_a_LIBADD += network.rel
endif


###############################################################################
#                  Special Rules                                              #
###############################################################################

DISTCLEANFILES = include/bspopts.h

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
