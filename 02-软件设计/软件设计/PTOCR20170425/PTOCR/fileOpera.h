/*************************************************************

概述：使用MFC文件进行操作
	包含目录文件遍历
	目录文件查找

作者：吴新有
日期：20170425
版本：v1.0
**************************************************************/

#ifndef FILEOPERA_H
#define FILEOPERA_H


#include<iostream>
#include<vector>
using namespace std;



class FileOpera
{

public:
	CString FindFilePath(CString strDir, CString fileName, int nDepth);
	void TravelFolder(CString strDir, int nDepth);

};



#endif