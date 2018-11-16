#include "cls_timedomain.h"

TimeDomainCLS::TimeDomainCLS()
{

}

TimeDomainCLS::~TimeDomainCLS()
{
    //// perform cleanup
    rcmIfClose();
}

int TimeDomainCLS::init(char* PORT_RECV)
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    //// init uwb receiver
    ////////////////////////////////////////////////////////////////////////////////////////////

    // note that we don't need to specify node id of uwb receiver.
    // just connecting uwb receiver with a computer is needed.

    //// temp
    //char* PORT_RECV   = "/dev/ttyACM0";
    //char PORT_RECV[]   = "/dev/ttyACM0";


    int status;


    //// set connection type
    m_rcmIf = rcmIfUsb;

    //// initialize the interface to the RCM
    if( rcmIfInit(m_rcmIf, PORT_RECV) != OK )
    {
        printf("Initialization failed.\n");
        return -1;
    }

    //// Make sure RCM is awake
    if( rcmSleepModeSet(RCM_SLEEP_MODE_ACTIVE) != 0 )
    {
        printf("Time out waiting for sleep mode set.\n");
        return -1;
    }

    //// Make sure opmode is RCM
    if( rcmOpModeSet(RCM_OPMODE_RCM) != 0 )
    {
        printf("Time out waiting for opmode set.\n");
        return -1;
    }

    //// execute Built-In Test - verify that radio is healthy
    if( rcmBit(&status) != 0 )
    {
        printf("Time out waiting for BIT.\n");
        return -1;
    }

    if( status != OK )
    {
        printf("Built-in test failed - status %d.\n", status);
        return -1;
    }
    else
    {
        printf("Radio passes built-in test.\n\n");
    }

    //// retrieve config from RCM
    if( rcmConfigGet(&m_config) != 0 )
    {
        printf("Time out waiting for config confirm.\n");
        return -1;
    }

    //// print out configuration
    printf("Message from TimeDomainCLS::init()...\n");
    printf("Configuration:\n");
    printf("\tnodeId: %d\n", m_config.nodeId);
    printf("\tintegrationIndex: %d\n", m_config.integrationIndex);
    printf("\tantennaMode: %d\n", m_config.antennaMode);
    printf("\tcodeChannel: %d\n", m_config.codeChannel);
    printf("\telectricalDelayPsA: %d\n", m_config.electricalDelayPsA);
    printf("\telectricalDelayPsB: %d\n", m_config.electricalDelayPsB);
    printf("\tflags: 0x%X\n", m_config.flags);
    printf("\ttxGain: %d\n", m_config.txGain);

    //// retrieve status/info from RCM
    if( rcmStatusInfoGet(&m_statusInfo) != 0 )
    {
        printf("Time out waiting for status info confirm.\n");
        return -1;
    }

    //// print out status/info
    printf("\nStatus/Info:\n");
    printf("\tPackage version: %s\n", m_statusInfo.packageVersionStr);
    printf("\tRCM version: %d.%d build %d\n", m_statusInfo.appVersionMajor,
            m_statusInfo.appVersionMinor, m_statusInfo.appVersionBuild);
    printf("\tUWB Kernel version: %d.%d build %d\n", m_statusInfo.uwbKernelVersionMajor,
            m_statusInfo.uwbKernelVersionMinor, m_statusInfo.uwbKernelVersionBuild);
    printf("\tFirmware version: %x/%x/%x ver %X\n", m_statusInfo.firmwareMonth,
            m_statusInfo.firmwareDay, m_statusInfo.firmwareYear,
            m_statusInfo.firmwareVersion);
    printf("\tSerial number: %08X\n", m_statusInfo.serialNum);
    printf("\tBoard revision: %c\n", m_statusInfo.boardRev);
    printf("\tTemperature: %.2f degC\n\n", m_statusInfo.temperature/4.0);


    return 1;

}


double TimeDomainCLS::get_range(int Node_id_transmitter)
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    //// get range between (Node receiver <-> Node_id_transmitter)
    ////////////////////////////////////////////////////////////////////////////////////////////

    // return < 0.0 if not available


    double range_get = -1.0;


    //// Determine range to a radio. May also get data and scan packets.
    if( rcmRangeTo(Node_id_transmitter, RCM_ANTENNAMODE_TXA_RXA, 0, NULL,
            &m_rangeInfo, &m_dataInfo, &m_scanInfo, &m_fullScanInfo) == 0 )
    {
        /*
        // we always get a range info packet
        printf("RANGE_INFO: responder %d, msg ID %u, range status %d, "
                "stopwatch %d ms, noise %d, vPeak %d, measurement type %d\n",
                rangeInfo.responderId, rangeInfo.msgId, rangeInfo.rangeStatus,
                rangeInfo.stopwatchTime, rangeInfo.noise, rangeInfo.vPeak,
                rangeInfo.rangeMeasurementType);

        // The RANGE_INFO can provide multiple types of ranges
        if (rangeInfo.rangeMeasurementType & RCM_RANGE_TYPE_PRECISION)
        {
            printf("Precision range: %d mm, error estimate %d mm\n",
                    rangeInfo.precisionRangeMm, rangeInfo.precisionRangeErrEst);
        }

        if (rangeInfo.rangeMeasurementType & RCM_RANGE_TYPE_COARSE)
        {
            printf("Coarse range: %d mm, error estimate %d mm\n",
                    rangeInfo.coarseRangeMm, rangeInfo.coarseRangeErrEst);
        }

        if (rangeInfo.rangeMeasurementType & RCM_RANGE_TYPE_FILTERED)
        {
            printf("Filtered range: %d mm, error estimate %d mm\n",
                    rangeInfo.filteredRangeMm, rangeInfo.filteredRangeErrEst);
            printf("Filtered velocity: %d mm/s, error estimate %d mm/s\n",
                    rangeInfo.filteredRangeVel, rangeInfo.filteredRangeVelErrEst);
        }


        // only get a data info packet if the responder sent data
        // dataSize will be non-zero if we there is data
        if (dataInfo.dataSize)
            printf("DATA_INFO from node %d: msg ID %u, noise %d, vPeak %d, %d bytes\ndata: %*s\n",
                    dataInfo.sourceId, dataInfo.msgId, dataInfo.noise, dataInfo.vPeak,
                    dataInfo.dataSize, dataInfo.dataSize, dataInfo.data);

        // only get a scan info packet if the SEND_SCAN bit is set in the config
        // numSamples will be non-zero if there is scan data
        // we don't do anything with the scan data itself here
        if (scanInfo.numSamples)
            printf("SCAN_INFO from node %d: msg ID %u, %d samples, noise %d, vPeak %d\n",
                    scanInfo.sourceId, scanInfo.msgId, scanInfo.numSamples,
                    scanInfo.noise, scanInfo.vPeak);

        // only get a full scan info packet if the FULL_SCAN bit is set in the config
        // numSamplesInMessage will be non-zero if there is scan data
        // we don't do anything with the scan data itself here
        if (fullScanInfo.numSamplesInMessage)
            printf("FULL_SCAN_INFO from node %d: msg ID %u, %d samples, noise %d, vPeak %d\n",
                    fullScanInfo.sourceId, fullScanInfo.msgId, fullScanInfo.numSamplesInMessage,
                    fullScanInfo.noise, fullScanInfo.vPeak);

        // a rangeStatus of 0 means the range was calculated successfully
        if (rangeInfo.rangeStatus == 0)
        {
            // now broadcast the range in a data packet
            sprintf(str, "The range from %d to %d is %d mm.",
                    config.nodeId, destNodeId,
                    rangeInfo.precisionRangeMm);
            rcmDataSend(RCM_ANTENNAMODE_TXA_RXA, strlen(str), str);
        }
        */


        //// get range(unit: m)
        range_get = ((double)m_rangeInfo.precisionRangeMm)/1000.0;
    }

    // completed to set
    //    range_get(unit: m)


    return range_get;

}


void TimeDomainCLS::get_range2(int Node_id_transmitter, double& Range_out, double& RangeErr_out)
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    //// get range between (Node receiver <-> Node_id_transmitter)
    ////////////////////////////////////////////////////////////////////////////////////////////

    // return < 0.0 if not available


    double range_get = -1.0;
    double range_err_get = -1.0;


    //// Determine range to a radio. May also get data and scan packets.
    if( rcmRangeTo(Node_id_transmitter, RCM_ANTENNAMODE_TXA_RXA, 0, NULL, &m_rangeInfo, &m_dataInfo, &m_scanInfo, &m_fullScanInfo) == 0 )
    {
        /*
        // we always get a range info packet
        printf("RANGE_INFO: responder %d, msg ID %u, range status %d, "
                "stopwatch %d ms, noise %d, vPeak %d, measurement type %d\n",
                rangeInfo.responderId, rangeInfo.msgId, rangeInfo.rangeStatus,
                rangeInfo.stopwatchTime, rangeInfo.noise, rangeInfo.vPeak,
                rangeInfo.rangeMeasurementType);

        // The RANGE_INFO can provide multiple types of ranges
        if (rangeInfo.rangeMeasurementType & RCM_RANGE_TYPE_PRECISION)
        {
            printf("Precision range: %d mm, error estimate %d mm\n",
                    rangeInfo.precisionRangeMm, rangeInfo.precisionRangeErrEst);
        }

        if (rangeInfo.rangeMeasurementType & RCM_RANGE_TYPE_COARSE)
        {
            printf("Coarse range: %d mm, error estimate %d mm\n",
                    rangeInfo.coarseRangeMm, rangeInfo.coarseRangeErrEst);
        }

        if (rangeInfo.rangeMeasurementType & RCM_RANGE_TYPE_FILTERED)
        {
            printf("Filtered range: %d mm, error estimate %d mm\n",
                    rangeInfo.filteredRangeMm, rangeInfo.filteredRangeErrEst);
            printf("Filtered velocity: %d mm/s, error estimate %d mm/s\n",
                    rangeInfo.filteredRangeVel, rangeInfo.filteredRangeVelErrEst);
        }


        // only get a data info packet if the responder sent data
        // dataSize will be non-zero if we there is data
        if (dataInfo.dataSize)
            printf("DATA_INFO from node %d: msg ID %u, noise %d, vPeak %d, %d bytes\ndata: %*s\n",
                    dataInfo.sourceId, dataInfo.msgId, dataInfo.noise, dataInfo.vPeak,
                    dataInfo.dataSize, dataInfo.dataSize, dataInfo.data);

        // only get a scan info packet if the SEND_SCAN bit is set in the config
        // numSamples will be non-zero if there is scan data
        // we don't do anything with the scan data itself here
        if (scanInfo.numSamples)
            printf("SCAN_INFO from node %d: msg ID %u, %d samples, noise %d, vPeak %d\n",
                    scanInfo.sourceId, scanInfo.msgId, scanInfo.numSamples,
                    scanInfo.noise, scanInfo.vPeak);

        // only get a full scan info packet if the FULL_SCAN bit is set in the config
        // numSamplesInMessage will be non-zero if there is scan data
        // we don't do anything with the scan data itself here
        if (fullScanInfo.numSamplesInMessage)
            printf("FULL_SCAN_INFO from node %d: msg ID %u, %d samples, noise %d, vPeak %d\n",
                    fullScanInfo.sourceId, fullScanInfo.msgId, fullScanInfo.numSamplesInMessage,
                    fullScanInfo.noise, fullScanInfo.vPeak);

        // a rangeStatus of 0 means the range was calculated successfully
        if (rangeInfo.rangeStatus == 0)
        {
            // now broadcast the range in a data packet
            sprintf(str, "The range from %d to %d is %d mm.",
                    config.nodeId, destNodeId,
                    rangeInfo.precisionRangeMm);
            rcmDataSend(RCM_ANTENNAMODE_TXA_RXA, strlen(str), str);
        }
        */


        //// get range(unit: m)
        range_get = ((double)m_rangeInfo.precisionRangeMm)/1000.0;
        range_err_get = ((double)m_rangeInfo.precisionRangeErrEst)/1000.0;
    }

    // completed to set
    //    range_get (unit: m)
    //    range_err_get (unit: m)

    //// set output
    Range_out = range_get;
    RangeErr_out = range_err_get;


}
