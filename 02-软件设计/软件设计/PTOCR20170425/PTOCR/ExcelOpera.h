
/*************************************************************

概述：使用MFC操作Excel文件，
	包含文件创建，文件打开，文件编辑，文件保存，进程关闭，后台运行
作者：吴新有
日期：20170425
版本：v1.0
**************************************************************/

#pragma once

#include"CApplication.h"
#include"CFont0.h"
#include"CRange.h"
#include"CRanges.h"
#include"CWorkbook.h"
#include"CWorkbooks.h"
#include"CWorksheet.h"
#include"CWorksheets.h"

#include<iostream>
#include<string>

using namespace std;

class ExcelOpera
{
public:
	ExcelOpera();
	~ExcelOpera();

	void CreateExcelFile();
	void OpenExistExcelFile(CString filePath);
	void ExitExcel();
	void ShowExcel();
	void EditExcel(const string cellNum, const string str);

private:
	//定义接口类变量 
	CApplication app;
	CWorkbook book;
	CWorkbooks books;
	CWorksheet sheet;
	CWorksheets sheets;
	CRange range;
	CFont0 font;
	CRange cols;
	LPDISPATCH lpDisp;

	bool isOpened;


};

