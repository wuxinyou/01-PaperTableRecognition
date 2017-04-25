

/*************************************************************

概述：使用MFC文件进行操作
	包含目录文件遍历
	目录文件查找

作者：吴新有
日期：20170425
版本：v1.0
**************************************************************/

#include "stdafx.h"
#include "fileOpera.h"

/*********************************************************
遍历目录中的文件
输入：strDir：待遍历的目录
nDepth ：遍历目录的深度
返回：无

***********************************************************/
void FileOpera::TravelFolder(CString strDir, int nDepth)
{
	CFileFind filefind;                                         //声明CFileFind类型变量
	CString strWildpath = strDir + _T("\\*.*");     //所有文件都列出。
	vector<CString> fileNameVec;

	if (filefind.FindFile(strWildpath, 0))                    //开始检索文件
	{
		BOOL bRet = TRUE;

		while (bRet)
		{
			bRet = filefind.FindNextFile();                 //枚举一个文件

			if (filefind.IsDots())                                 //如果是. 或 .. 做下一个
				continue;

			for (int i = 0; i < nDepth; i++)                 //层次空格打印
			{
				TRACE(_T("    "));
			}

			if (!filefind.IsDirectory())                          //不是子目录，把文件名打印出来
			{
				CString strTextOut = strDir + CString(_T("\\")) + filefind.GetFileName();
				//TRACE(_T("file = %s\r\n"), strTextOut);
				fileNameVec.push_back(strTextOut);
			}
			else                                                    //如果是子目录，递归调用该函数
			{
				CString strTextOut = strDir + CString(_T("\\")) + filefind.GetFileName();
				TRACE(_T("dir = %s\r\n"), strTextOut);
				TravelFolder(strTextOut, nDepth + 1);//递归调用该函数打印子目录里的文件
			}
		}
		filefind.Close();
	}
	//在output窗口 打印输出findfile
	for (auto i : fileNameVec)
	{
		TRACE(_T("file = %s\r\n"), i);
	}
}

/*****************************************************************
说明：找到指定的文件名
输入：strDir：待查找的目录
fileName:待查找的文件名（含后缀）
nDepth:查找目录的深度
返回：CString 找到文件的全路径名
******************************************************************/
CString FileOpera::FindFilePath(CString strDir, CString fileName, int nDepth)
{
	CFileFind filefind;                                         //声明CFileFind类型变量
	CString strWildpath = strDir + _T("\\*.*");     //所有文件都列出。

	if (filefind.FindFile(strWildpath, 0))                    //开始检索文件
	{
		BOOL bRet = TRUE;

		while (bRet)
		{
			bRet = filefind.FindNextFile();                 //枚举一个文件

			if (filefind.IsDots())                                 //如果是. 或 .. 做下一个
				continue;

			for (int i = 0; i < nDepth; i++)                 //层次空格打印
			{
				TRACE(_T("    "));
			}

			if (!filefind.IsDirectory())                          //不是子目录，把文件名打印出来
			{
				CString findFileName = filefind.GetFileName();
				TRACE(_T("GetFileName = %s\r\n"), findFileName);
				if (findFileName == fileName)
				{
					CString strTextOut = strDir + CString(_T("\\")) + findFileName;
					return strTextOut;         //找到指定文件后即退出
				}

			}
			else                                                    //如果是子目录，递归调用该函数
			{
				CString strTextOut = strDir + CString(_T("\\")) + filefind.GetFileName();
				TRACE(_T("dir = %s\r\n"), strTextOut);
				FindFilePath(strTextOut, fileName, nDepth + 1);//递归调用该函数打印子目录里的文件
			}
		}
		filefind.Close();
	}
	return NULL;

}