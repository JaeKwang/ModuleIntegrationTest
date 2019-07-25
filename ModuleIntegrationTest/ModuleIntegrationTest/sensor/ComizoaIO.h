#pragma once

#include "sensor\SensorModule.h"
#include "robot\IOList.h"
#include "util\PINIReadWriter.h"

namespace sensor {
	class CComizoaIO : public CSensorModule {
	private:
		int ConnectAct() override;
		int ResetAct() override;
		int UpdateData() override;
		int DisconnectAct() override;

		int initialization();
		bool m_bInitialized;

		IO_List::DIOModule* m_DIOModule;
		int m_nDIONum;
		long m_lNodeID;

		long* m_ReadData = {};
		long* m_WriteData = {};

	public:
		CComizoaIO(std::string, long, IO_List::DIOModule*, int);
		~CComizoaIO();

		int bitSet(int, int, bool);
		bool bitRead(int, int, int*);

		
		// Getter & Setter
		long getNodeID();
		int setNodeID(long);
	};
}