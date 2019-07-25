#pragma once

#include "afxwin.h"
#include <iostream>
#include <afxmt.h>
#include"winioctl.h"
#include "sensor\SensorModule.h"

namespace sensor {
	class CSICKGuide : public CSensorModule {
	private:
		int m_nPort;
		int m_nBaudrate_k;
		int m_nTimeOut_ms;

		int m_nDeviceNum;
		ULONG * m_lDeviceID;
		unsigned char **cReadData_8Byte_One;

		short int nLength_one;
		int nReadCount_Max1024 = 1024;
		int npackets;	

		int CanClose();
		bool CanWrite(int *nID, unsigned char cWriteData_8byte[][8], int *nLength, int nDataCuount_Max1024);
		int ClearRxFifo();
		int CanReadOne(ULONG *nID, unsigned char *cReadData_8byteOne, short int *nLength, int nReadCount_Max1024);
		int EnterWorkMode();
		HANDLE CanOpen();
		int EnterResetMode();
		enum MSG_TYPE {
			MSG_RTR = (1 << 0),
			MSG_OVR = (1 << 1),
			MSG_EXT = (1 << 2),
			MSG_SELF = (1 << 3),
			MSG_PASSIVE = (1 << 4),
			MSG_BUSOFF = (1 << 5),
			MSG_BOVR = (1 << 7)
		};
		enum CMD {
			CMD_START = 1,
			CMD_STOP = 2,
			CMD_RESET = 3,
			CMD_CLEARBUFFERS = 4
		};
		enum ADS {
			ADS_TYPE = FILE_DEVICE_UNKNOWN,
			ADS_IOCTL_INDEX = 0x950
		};
		enum CAN_IOCTL {
			CAN_IOCTL_COMMAND = CTL_CODE(ADS_TYPE, ADS_IOCTL_INDEX, METHOD_BUFFERED, FILE_ANY_ACCESS),
			CAN_IOCTL_CONFIG = CTL_CODE(ADS_TYPE, ADS_IOCTL_INDEX + 1, METHOD_BUFFERED, FILE_ANY_ACCESS),
			CAN_IOCTL_STATUS = CTL_CODE(ADS_TYPE, ADS_IOCTL_INDEX + 5, METHOD_BUFFERED, FILE_ANY_ACCESS)
		};
		enum CAN_OPERATION_RETURN {
			SUCCESS = 0,
			OPERATION_ERROR = -1,
			TIME_OUT = -2
		};
		enum CAN_CONFIGURE {
			CONF_ACC = 0,
			CONF_ACCM = 1,
			CONF_ACCC = 2,
			CONF_TIMING = 3,
			CONF_LISTEN_ONLY_MODE = 4,
			CONF_SELF_RECEPTION = 9,
			CONF_TIMEOUT = 13,
			CONF_ACC_FILTER = 20
		};


		typedef struct {
			int                     flags;                  /* Flags, indicating or controlling special message properties */
			int                     cob;                    /* CAN object number, used in Full CAN */
			ULONG                   id;                     /* CAN message ID, 4 bytes  */
			short int               length;                 /* Number of bytes in the CAN message */
			UCHAR                   data[8];				/* Data, 0...8 bytes */
		} canmsg_t;

		struct Command_par {
			int                     cmd;                    /* special driver command */
			int                     target;                 /* special configuration target */
			ULONG                   val1;                   /* 1. parameter  */
			ULONG                   val2;                   /* 2. parameter  */
			int                     error;                  /* return value */
			ULONG                   retval;                 /* return value */

		};
		typedef struct {
			unsigned int            baud;                   /* Actual bit rate */
			unsigned int            status;                 /* CAN controller status register, address 2 */
			unsigned int            error_warning_limit;    /* The error warning limit, address 13 */
			unsigned int            rx_errors;              /* Content of RX error counter, address 14 */
			unsigned int            tx_errors;              /* Content of TX error counter, address 15 */
			unsigned int            error_code;             /* Content of error code register, address 12 */
			unsigned int            rx_buffer_size;         /* Size of rx buffer*/
			unsigned int            rx_buffer_used;         /* number of messages*/
			unsigned int            tx_buffer_size;         /* Size of tx buffer for wince, windows not use tx buffer*/
			unsigned int            tx_buffer_used;         /* Number of message for wince, windows not use tx buffer s*/
			ULONG                   retval;                 /* Return value*/
			unsigned int            type;                   /* CAN controller/driver type*/
			unsigned int            acceptancecode;         /* Acceptance code */
			unsigned int            acceptancemask;         /* Acceptance mask */
			unsigned int            acceptancemode;         /**< Acceptance Filter Mode: 1:Single 0:Dual */
			unsigned int            selfreception;          /* Self reception */
			unsigned int            readtimeout;            /* Read timeout */
			unsigned int            writetimeout;           /* Write timeout */
		} CanStatusPar_t;

		typedef struct Command_par Command_par_t;
		typedef struct Command_par  Config_par_t;

		HANDLE m_hDevice;

		int m_nFrameType;
		bool m_bSynchronousMode;

		short* guide_lcp1;
		short* guide_lcp2;
		short* guide_lcp3;
		unsigned char* guide_lcp;
		unsigned char* guide_status;
		int* guide_line_exists;
		int* guide_marker;
		bool* guide_line_good;
		int* guide_linelev;
		bool* guide_reading_code;

	public:
		CSICKGuide(std::string, int, int, int, int);
		~CSICKGuide();
		int ConnectAct() override;
		int ResetAct() override;
		int UpdateData() override;
		int DisconnectAct() override;

		// Getter & Setter
		int SetBaud();
		int SetTimeOut();
		int setDeviceID(int index, ULONG id);
		int setPort(int port); 
		int getPort();
		ULONG getDeviceID(int index);
		int getDeviceNum();
		short* getFrontData();
		short* getRearData();
		int getFrontMarker();
		int getRearMarker();
	};
}