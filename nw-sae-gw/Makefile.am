# this is example-file: src/bin/Makefile.am
AUTOMAKE_OPTIONS = subdir-objects

# additional include paths necessary to compile the C++ programs
AM_CFLAGS = -DNW_LOG_TO_FILE -Wall -I$(top_srcdir)/nw-gtpv2c/shared -I$(top_srcdir)/nw-gtpv1u/shared -I$(top_srcdir)/nw-sdp/shared -I$(top_srcdir)/common -I$(top_srcdir)/nw-gre/shared -I$(top_srcdir)/nw-ipv4/shared -I$(top_srcdir)/include -I$(top_srcdir)/utils/nw-ipv4-if -I$(top_srcdir)/utils/nw-gtpv2c-if -I$(top_srcdir)/utils/nw-gtpu-if  -I$(top_srcdir)/utils/nw-log -I$(top_srcdir)/utils/nw-tmr -I$(top_srcdir)/utils/nw-ippool -I$(top_srcdir)/nw-event/include @AM_CFLAGS@

###############################################################################
# THE PROGRAMS TO BUILD
###############################################################################

# the program to build (the names of the final binaries)
bin_PROGRAMS = nwLteSaeGw

# list of sources for the 'NwWimaxBsEmu' binary
nwLteSaeGw_SOURCES =    \
						../common/tree.h\
						../common/queue.h\
						../common/NwTypes.h\
						../common/NwError.h\
						../common/NwLog.h\
						../common/NwUtils.h\
						../common/NwMem.h\
						../common/NwEvt.h\
						../utils/nw-tmr/NwTmrMgr.h\
						../utils/nw-log/NwLogMgr.h\
						../utils/nw-ipv4-if/NwIpv4IfLog.h\
						../utils/nw-ipv4-if/NwIpv4If.h\
						../utils/nw-gtpv2c-if/NwGtpv2cIfLog.h\
						../utils/nw-gtpv2c-if/NwGtpv2cIf.h\
						../utils/nw-gtpu-if/NwGtpv1uIfLog.h\
						../utils/nw-gtpu-if/NwGtpv1uIf.h\
						../utils/nw-ippool/NwIpv4PoolMgr.h\
						../utils/nw-ippool/NwIpv4PoolMgrLog.h\
						../utils/nw-tmr/NwTmrMgr.c\
						../utils/nw-log/NwLogMgr.c\
						../utils/nw-ipv4-if/NwIpv4If.c\
						../utils/nw-gtpv2c-if/NwGtpv2cIf.c\
						../utils/nw-gtpu-if/NwGtpv1uIf.c\
						../utils/nw-ippool/NwIpv4PoolMgr.c\
						../nw-gtpv2c/shared/NwGtpv2c.h\
						../nw-gtpv2c/shared/NwGtpv2cIe.h\
						../nw-gtpv2c/shared/NwGtpv2cMsg.h\
						../nw-gtpv2c/shared/NwGtpv2cMsgParser.h\
						../nw-gtpv1u/shared/NwGtpv1u.h\
			../nw-sdp/shared/NwSdp.h\
						../common/NwMem.c\
						NwSaeGwLog.h\
						NwSaeGwUeLog.h\
			NwSaeGwUlp.h\
			NwSaeGwDpe.h\
						NwSaeGwUe.h\
						NwSaeGwUeFsm.h\
						NwSaeGwUeState.h\
						NwSaeGwUeStateInit.h\
						NwSaeGwUeStateSaeSessionCreated.h\
						NwSaeGwUeStateSgwSessionCreated.h\
						NwSaeGwUeStatePgwSessionCreated.h\
						NwSaeGwUeStateSaeSessionEstablished.h\
						NwSaeGwUeStateSgwSessionEstablished.h\
						NwSaeGwUeStateAwaitPgwCreateSessionRsp.h\
						NwSaeGwUeStateAwaitPgwDeleteSessionRsp.h\
						NwSaeGwUeStateAwaitPgwModifyBearerRsp.h\
						NwSaeGwUeStateAwaitPgwModifyBearerRsp2.h\
						NwSaeGwUeStateAwaitMmeDownlinkDataNt.h\
			NwSaeGwUlp.c\
			NwSaeGwDpe.c\
						NwSaeGwUeFsm.c\
						NwSaeGwUeState.c\
						NwSaeGwUeStateInit.c\
						NwSaeGwUeStateSaeSessionCreated.c\
						NwSaeGwUeStateSgwSessionCreated.c\
						NwSaeGwUeStatePgwSessionCreated.c\
						NwSaeGwUeStateSaeSessionEstablished.c\
						NwSaeGwUeStateSgwSessionEstablished.c\
						NwSaeGwUeStateAwaitPgwCreateSessionRsp.c\
						NwSaeGwUeStateAwaitPgwDeleteSessionRsp.c\
						NwSaeGwUeStateAwaitPgwModifyBearerRsp.c\
						NwSaeGwUeStateAwaitPgwModifyBearerRsp2.c\
						NwSaeGwUeStateAwaitMmeDownlinkDataNt.c\
						NwSaeGwMain.c\
						NwSaeGwUe.c

# the additional libraries needed to link nwWimaxBsEmu
nwLteSaeGw_LDADD =  $(top_builddir)/nw-gtpv2c/src/libNwGtpv2c.a $(top_builddir)/nw-sdp/src/libNwSdp.a $(top_builddir)/nw-gtpv1u/src/libNwGtpv1u.a $(top_builddir)/nw-gre/src/libNwGre.a  $(top_builddir)/nw-ipv4/src/libNwIpv4.a $(top_builddir)/nw-event/src/libNwEvent.a  $(AM_LDFLAGS)

###############################################################################

systemddir = /lib/systemd/system
systemd_DATA = ../init/sgw.service ../init/pgw.service ../init/spgw.service

systemdnetdir = /etc/systemd/network
systemdnet_DATA = ../init/sgi0.network ../init/sgi0.netdev

iproutedir = /etc/conf.d/iproute2/
iproute_DATA = ../init/pgw.iproute2.start ../init/pgw.iproute2.stop

confdir = /etc/aalto
conf_DATA = ../init/sgw.cfg.template ../init/pgw.cfg.template ../init/spgw.cfg.template

EXTRA_DIST = $(systemd_DATA) $(systemdnet_DATA) $(iproute_DATA) $(conf_DATA)

#install-exec-hook:
#	echo 100 rt_lte_ue >> /etc/iproute2/rt_tables

#uninstall-local:
#	sed -i -e '/rt_lte_ue/d' /etc/iproute2/rt_tables
