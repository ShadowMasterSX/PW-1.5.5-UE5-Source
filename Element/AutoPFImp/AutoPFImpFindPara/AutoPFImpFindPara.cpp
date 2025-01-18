// AutoPFImpFindPara.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <io.h>

using namespace std;

int main(int argc, char* argv[])
{	
	if (argc != 8){
		printf("������������\n");
		return 0;
	}

	//	��ȡ������� prmap �� pdhmap
	string strRMapFile = argv[1];
	if (_access(strRMapFile.c_str(), 0) == -1){
		printf("�ļ������� %s\n", strRMapFile.c_str());
		return 0;
	}
	
	string strDHMapFile = argv[2];
	if (_access(strDHMapFile.c_str(), 0) == -1){
		printf("�ļ������� %s\n", strDHMapFile.c_str());
		return 0;
	}
		
	int nClusterSizeMin = atoi(argv[3]);
	int nClusterSizeMax = atoi(argv[4]);
	int nEntranceWidthMin = atoi(argv[5]);
	int nEntranceWidthMax = atoi(argv[6]);
	int nTestCase = atoi(argv[7]);

	if (nClusterSizeMin <= 0 || nClusterSizeMax < nClusterSizeMin ||
		nEntranceWidthMin <= 0 || nEntranceWidthMax < nEntranceWidthMin){
		printf("������Χ����\n");
		return 0;
	}
	
	//	��ȡԤ�����������۳���
	char szModuleFilePath[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szModuleFilePath, sizeof(szModuleFilePath)/sizeof(szModuleFilePath[0]));
	
	char drive[MAX_PATH];
	char dir[MAX_PATH];
	char ext[MAX_PATH];	
	_splitpath(szModuleFilePath, drive, dir, NULL, ext);

	string strDir = drive;
	strDir += "\\";
	strDir += dir;

	string strGenerator = strDir;
	strGenerator += "AutoPFImpGenerator.exe";
	if (_access(strGenerator.c_str(), 0) == -1){
		printf("�ļ������� %s\n", strGenerator.c_str());
		return 0;
	}
	
	string strSearch = strDir;
	strSearch += "AutoPFImpOptimize.exe";
	if (_access(strSearch.c_str(), 0) == -1){
		printf("�ļ������� %s\n", strSearch.c_str());
		return 0;
	}
	
	char fname[MAX_PATH];
	_splitpath(strRMapFile.c_str(), NULL, NULL, fname, NULL);
	string strCfgFile = strDir;
	strCfgFile += fname;
	strCfgFile += ".cfg";

	int leftCount = (nClusterSizeMax - nClusterSizeMin + 1) * (nEntranceWidthMax - nEntranceWidthMin + 1);
	DWORD lastTimeCost = 0;
	char szPara[1024] = {0};
	for (int nClusterSize = nClusterSizeMin; nClusterSize <= nClusterSizeMax; ++ nClusterSize)
	{
		for (int nEntranceWidth = nEntranceWidthMin; nEntranceWidth <= nEntranceWidthMax; ++ nEntranceWidth, -- leftCount)
		{
			if (nEntranceWidth > nClusterSize){
				continue;
			}

			printf("\nnClusterSize = %d, nEntraceWidth = %d", nClusterSize, nEntranceWidth);
			if (lastTimeCost > 0){
				printf("��Ԥ��ʣ��ʱ��");
				DWORD leftTimeCost = leftCount*lastTimeCost/1000;
				int nHour = leftTimeCost/3600;
				int nMin = leftTimeCost%3600/60;
				int nSec = leftTimeCost%3600%60;
				if (nHour > 0){
					printf(" %d Сʱ", nHour);
				}
				if (nMin > 0){
					printf(" %d ����", nMin);
				}
				if (nSec > 0){
					printf(" %d ��", nSec);
				}
			}
			
			DWORD timeBegin = timeGetTime();
			{
				printf("\n����Ԥ�����ļ�...");

				//	����Ԥ�����ļ�
				sprintf(szPara, "\"%s\" \"%s\" %d %d", strRMapFile.c_str(), strDHMapFile.c_str(), nClusterSize, nEntranceWidth);

				SHELLEXECUTEINFOA si = {0};
				si.cbSize = sizeof(si);
				si.fMask = SEE_MASK_NOCLOSEPROCESS;
				si.lpVerb = "open";
				si.lpFile = strGenerator.c_str();
				si.lpParameters = szPara;
				si.nShow = SW_HIDE;
				ShellExecuteExA(&si);
				
				// ��ɺ�ŷ���
				WaitForSingleObject(si.hProcess, INFINITE);
				CloseHandle(si.hProcess);

				if (_access(strCfgFile.c_str(), 0) == -1){
					printf("ʧ��!");
					continue;;
				}
			}
			{
				printf("\n����Ԥ�����ļ�...");

				//	����Ԥ������ļ�
				sprintf(szPara, "\"%s\" %d %d %d", strCfgFile.c_str(), nClusterSize, nEntranceWidth, nTestCase);

				SHELLEXECUTEINFOA si = {0};
				si.cbSize = sizeof(si);
				si.fMask = SEE_MASK_NOCLOSEPROCESS;
				si.lpVerb = "open";
				si.lpFile = strSearch.c_str();
				si.lpParameters = szPara;
				si.nShow = SW_HIDE;
				ShellExecuteExA(&si);
				
				// ��ɺ�ŷ���
				WaitForSingleObject(si.hProcess, INFINITE);
				CloseHandle(si.hProcess);
			}
			lastTimeCost = timeGetTime() - timeBegin;
		}
	}

	return 0;
}
