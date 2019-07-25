#pragma once

typedef struct _LaserScanData {
	int start_angle = 0;
	int end_angle = 0;

	int data_len = 0;

	UINT16 *dist;
	UINT16 *rssi;
} LaserScanData;