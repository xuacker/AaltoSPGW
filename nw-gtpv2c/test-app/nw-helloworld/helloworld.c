/*----------------------------------------------------------------------------*
 *                                                                            *
 *                              n w - g t p v 2 c                             *
 *    G P R S   T u n n e l i n g    P r o t o c o l   v 2 c    S t a c k     *
 *                                                                            *
 *           M I N I M A L I S T I C     D E M O N S T R A T I O N            *
 *                                                                            *
 *                    Copyright (C) 2010 Amit Chawre.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*/


/**
 * @file hello-world.c
 * @brief This is a test program demostrating usage of nw-gtpv2c library.
*/

#include <stdio.h>
#include <assert.h>
#include "NwEvt.h"
#include "NwLog.h"
#include "NwGtpv2c.h"

#include "NwMiniLogMgrEntity.h"
#include "NwMiniTmrMgrEntity.h"
#include "NwMiniUdpEntity.h"
#include "NwMiniUlpEntity.h"

#ifndef NW_ASSERT
#define NW_ASSERT assert
#endif

static
NwCharT* gLogLevelStr[] = {"EMER", "ALER", "CRIT",  "ERRO", "WARN", "NOTI", "INFO", "DEBG"};

/*---------------------------------------------------------------------------
 *                T H E      M A I N      F U N C T I O N
 *--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  NwGtpv2cRcT                         rc;
  NwU32T                        logLevel;
  NwU8T*                        logLevelStr;

  NwGtpv2cStackHandleT          hGtpv2cStack = 0;

  NwGtpv2cNodeUlpT              ulpObj;
  NwGtpv2cNodeUdpT              udpObj;


  NwGtpv2cUlpEntityT            ulp;
  NwGtpv2cUdpEntityT            udp;
  NwGtpv2cTimerMgrEntityT       tmrMgr;
  NwGtpv2cLogMgrEntityT         logMgr;

  if(argc != 3)
  {
    printf("Usage: %s <local-ip> <peer-ip>\n", argv[0]);
    exit(0);
  }

  logLevelStr = getenv ("NW_LOG_LEVEL");

  if(logLevelStr == NULL)
  {
    logLevel = NW_LOG_LEVEL_INFO;
  }
  else
  {
    if(strncmp(logLevelStr, "EMER",4) == 0)
      logLevel = NW_LOG_LEVEL_EMER;
    else if(strncmp(logLevelStr, "ALER",4) == 0)
      logLevel = NW_LOG_LEVEL_ALER;
    else if(strncmp(logLevelStr, "CRIT",4) == 0)
      logLevel = NW_LOG_LEVEL_CRIT;
    else if(strncmp(logLevelStr, "ERRO",4) == 0)
      logLevel = NW_LOG_LEVEL_ERRO ;
    else if(strncmp(logLevelStr, "WARN",4) == 0)
      logLevel = NW_LOG_LEVEL_WARN;
    else if(strncmp(logLevelStr, "NOTI",4) == 0)
      logLevel = NW_LOG_LEVEL_NOTI;
    else if(strncmp(logLevelStr, "INFO",4) == 0)
      logLevel = NW_LOG_LEVEL_INFO;
    else if(strncmp(logLevelStr, "DEBG",4) == 0)
      logLevel = NW_LOG_LEVEL_DEBG;
  }

  /*---------------------------------------------------------------------------
   *  Initialize event library
   *--------------------------------------------------------------------------*/

  NW_EVT_INIT();

  /*---------------------------------------------------------------------------
   *  Initialize Log Manager
   *--------------------------------------------------------------------------*/
  nwMiniLogMgrInit(nwMiniLogMgrGetInstance(), logLevel);

  /*---------------------------------------------------------------------------
   *  Initialize Gtpv2c Stack Instance
   *--------------------------------------------------------------------------*/
  rc = nwGtpv2cInitialize(&hGtpv2cStack);

  if(rc != NW_GTPV2C_OK)
  {
    NW_LOG(NW_LOG_LEVEL_ERRO, "Failed to create gtpv2c stack instance. Error '%u' occured", rc);
    exit(1);
  }
  NW_LOG(NW_LOG_LEVEL_INFO, "Gtpv2c Stack Handle '%X' Creation Successful!", hGtpv2cStack);

  rc = nwGtpv2cSetLogLevel(hGtpv2cStack, logLevel);

  /*---------------------------------------------------------------------------
   * Set up Ulp Entity
   *--------------------------------------------------------------------------*/
  rc = nwGtpv2cUlpInit(&ulpObj, hGtpv2cStack, argv[2]);
  NW_ASSERT(NW_GTPV2C_OK == rc);

  ulp.hUlp = (NwGtpv2cUlpHandleT) &ulpObj;
  ulp.ulpReqCallback = nwGtpv2cUlpProcessStackReqCallback;

  rc = nwGtpv2cSetUlpEntity(hGtpv2cStack, &ulp);
  NW_ASSERT(NW_GTPV2C_OK == rc);

  /*---------------------------------------------------------------------------
   * Set up Udp Entity
   *--------------------------------------------------------------------------*/
  rc = nwGtpv2cUdpInit(&udpObj, hGtpv2cStack, (argv[1]));
  NW_ASSERT(NW_GTPV2C_OK == rc);

  udp.hUdp = (NwGtpv2cUdpHandleT) &udpObj;
  udp.udpDataReqCallback = nwGtpv2cUdpDataReq;

  rc = nwGtpv2cSetUdpEntity(hGtpv2cStack, &udp);
  NW_ASSERT(NW_GTPV2C_OK == rc);

  /*---------------------------------------------------------------------------
   * Set up Log Entity
   *--------------------------------------------------------------------------*/
  tmrMgr.tmrMgrHandle = 0;
  tmrMgr.tmrStartCallback = nwTimerStart;
  tmrMgr.tmrStopCallback = nwTimerStop;

  rc = nwGtpv2cSetTimerMgrEntity(hGtpv2cStack, &tmrMgr);
  NW_ASSERT(NW_GTPV2C_OK == rc);

  /*---------------------------------------------------------------------------
   * Set up Log Entity
   *--------------------------------------------------------------------------*/
  logMgr.logMgrHandle   = (NwGtpv2cLogMgrHandleT) nwMiniLogMgrGetInstance();
  logMgr.logReqCallback  = nwMiniLogMgrLogRequest;

  rc = nwGtpv2cSetLogMgrEntity(hGtpv2cStack, &logMgr);
  NW_ASSERT(NW_GTPV2C_OK == rc);

  /*---------------------------------------------------------------------------
   *  Send Message Request to Gtpv2c Stack Instance
   *--------------------------------------------------------------------------*/
  //rc = nwGtpv2cUlpCreateSessionRequestToPeer(&ulpObj);
  rc = nwGtpv2cUlpSenEchoRequestToPeer(&ulpObj, inet_addr(argv[2]));
  NW_ASSERT(NW_GTPV2C_OK == rc);

  /*---------------------------------------------------------------------------
   * Event loop
   *--------------------------------------------------------------------------*/

  NW_EVT_LOOP();
  NW_LOG(NW_LOG_LEVEL_ERRO, "Exit from eventloop, no events to process!");

  /*---------------------------------------------------------------------------
   *  Destroy Gtpv2c Stack Instance
   *--------------------------------------------------------------------------*/
  rc = nwGtpv2cFinalize(hGtpv2cStack);
  if(rc != NW_GTPV2C_OK)
  {
    NW_LOG(NW_LOG_LEVEL_ERRO, "Failed to finalize gtpv2c stack instance. Error '%u' occured", rc);
  }
  else
  {
    NW_LOG(NW_LOG_LEVEL_INFO, "Gtpv2c Stack Handle '%X' Finalize Successful!", hGtpv2cStack);
  }

  return rc;
}
