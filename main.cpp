
#include <Windows.h>
#include <iostream>

BOOL SPACE()
{
	BOOL result = NULL; // TRUE = System legit | FALSE = System not legit

	int min_space_GB = 212;
	char driveNames[256];
	float totalGBs = 0;
	int res = GetLogicalDriveStringsA(sizeof(driveNames), driveNames);
	int numDrives = res / 4;

	DWORD bytePerSector, sectorPerCluster, freeClusters, totalClusters;

	for (int i = 0; i < numDrives; i++)
	{
		GetDiskFreeSpaceA(&driveNames[i * 4], &sectorPerCluster, &bytePerSector, &freeClusters, &totalClusters);
		totalGBs += (float)totalClusters * (float)sectorPerCluster * (float)bytePerSector / 1024.0 / 1024.0 / 1024.0;
	}
	totalGBs -= (float)totalClusters * (float)sectorPerCluster * (float)bytePerSector / 1024.0 / 1024.0 / 1024.0;

	//printf("%f GB\n", totalGBs);
	if (totalGBs >= min_space_GB)
		result = TRUE;
	else
		result = FALSE;

	return result;
}

int main()
{
	printf("AntiSandBox-with-Disk-Capacity\n");
	
	if (!SPACE())
		return 1;
	
	getchar();
	return 0;
}
