#pragma once

typedef struct _LaserScanData {
	int nAngleResolution = 0;
	int nStart_angle = 0;
	int nEnd_angle = 0;
	int nData_len = 0;

	UINT16 *dist;
	UINT16 *rssi;
} LaserScanData;