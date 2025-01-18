// AutoPFImpGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../include/moveagent.h"
#include "../include/movemap.h"
#include "../include/layermap.h"
#include "../include/multiclugraph.h"

#include <string>

#include <io.h>

using namespace AutoMove;
using namespace std;

CMoveAgent	g_AutoMoveAgent;

int main(int argc, char* argv[])
{
	if (argc != 5){
		printf("������������\n");
		return 0;
	}
	
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
	
	int nClusterSize = atoi(argv[3]);
	int nEntranceWidth = atoi(argv[4]);
	if (nClusterSize < 0 || nEntranceWidth < 0 || nClusterSize < nEntranceWidth){
		printf("Ԥ�����������\n");
		return 0;
	}

	g_AutoMoveAgent.GetMoveMap()->CreateJointList();
	CLayerMap * pCurLayer = g_AutoMoveAgent.GetMoveMap()->CreateLayer();

	printf("nClusterSize=%d, nEntraceWidth=%d\n", nClusterSize, nEntranceWidth);

	if (!pCurLayer->LoadRMap(strRMapFile.c_str())){
		printf("���� %s ʧ��\n", strRMapFile.c_str());
		return 0;
	}
	if (!pCurLayer->LoadDHMap(strDHMapFile.c_str())){
		printf("���� %s ʧ��\n", strDHMapFile.c_str());
		return 0;
	}
	g_AutoMoveAgent.GetMoveMap()->CalcOrigin();
	pCurLayer->CreateClu(g_AutoMoveAgent.GetPfAlg(), nClusterSize, nEntranceWidth);
	if (!g_AutoMoveAgent.GetMoveMap()->CreateMultiCluGraph(g_AutoMoveAgent.GetPfAlg())){
		printf("���� MultiCluGrph ʧ��\n");
		return 0;
	}

	//	�����ļ�	
	char drive[MAX_PATH];
	char dir[MAX_PATH];
	char fname[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath(strRMapFile.c_str(), drive, dir, fname, ext);
	
	AString path;
	path += drive;
	path += dir;
	path += fname;
	path += ".cfg";
	
	vector<AString> layerNames;
	layerNames.push_back(fname);

	AString mluName = fname;

	AString  mluPath;
	mluPath += drive;
	mluPath += dir;
	mluPath += mluName;
	mluPath += ".mlu";
	g_AutoMoveAgent.GetMoveMap()->GetMultiCluGraph()->Save(mluPath);	
	g_AutoMoveAgent.GetMoveMap()->Save(path, layerNames, mluName);
	return 0;
}
