#ifndef CLS_TIMEDOMAIN_H
#define CLS_TIMEDOMAIN_H


#include <stdio.h>
#include "time_domain/rcmIf.h"
#include "time_domain/rcm.h"


class TimeDomainCLS
{
public:
  TimeDomainCLS();
  ~TimeDomainCLS();

  int     init(char* PORT_RECV);
  double  get_range(int Node_id_transmitter);
  void    get_range2(int Node_id_transmitter, double& Range_out, double& RangeErr_out);


private:
  rcmIfType                   m_rcmIf;
  rcmConfiguration            m_config;
  rcmMsg_GetStatusInfoConfirm m_statusInfo;
  rcmMsg_FullRangeInfo        m_rangeInfo;
  rcmMsg_DataInfo             m_dataInfo;
  rcmMsg_ScanInfo             m_scanInfo;
  rcmMsg_FullScanInfo         m_fullScanInfo;



};

#endif // CLS_TIMEDOMAIN_H
