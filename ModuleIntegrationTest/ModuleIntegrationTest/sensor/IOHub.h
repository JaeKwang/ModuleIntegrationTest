#pragma once

#include "sensor\SensorModule.h"
#include "robot\IOList.h"
#include "util\PINIReadWriter.h"

namespace sensor {
	class CIOHub {
	private:
		long m_lNodeID;
		std::string m_strIniFileName;
		PINIReadWriter* m_pINIReaderWriter;
		sensor::CSensorModule * m_ComizoaIO;

		IO_List::DIOModule* m_DIOModule;
		IO_List::IOPinType* m_DIPinType;
		IO_List::IOPinType* m_DOPinType;
		IO_List::IOPinType* m_AIPinType;
		IO_List::IOPinType* m_AOPinType;
		int m_nDIOModuleSize;
		int m_nDIpinTypeSize;
		int m_nDOpinTypeSize;
		int m_nAIpinTypeSize;
		int m_nAOpinTypeSize;

		int Initialize();

	public:
		CIOHub(std::string);
		~CIOHub();

		int bitSet(IO_List::eDO_Code IOPin, bool value);
		int bitSet(int , int , int , bool);
		bool bitRead(int dioNum, int base, int offset, int * nErrorCode);
		bool bitRead(IO_List::eDI_Code IOPin, int * nErrorCode);
		bool bitRead(IO_List::eDO_Code IOPin, int * nErrorCode);
		int getStatus();

		// Getter & Setter
		IO_List::DIOModule* getDIOModule();
		int getDIOModuleNumber();
		IO_List::IOPinType* getDIModule();
		IO_List::IOPinType* getDOModule();
		int findPin(int dioNum, int offset, IO_List::IOPinType * ret);
		long getComizoaID();
		int setComizoaID(long id);

		void OccurError();
		void Connect();
		void Reset();
		void Disconnect();
	};
}