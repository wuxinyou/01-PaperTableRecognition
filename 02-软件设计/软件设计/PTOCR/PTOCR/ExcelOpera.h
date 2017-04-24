

#pragma once

#include"CApplication.h"
#include"CFont0.h"
#include"CRange.h"
#include"CRanges.h"
#include"CWorkbook.h"
#include"CWorkbooks.h"
#include"CWorksheet.h"
#include"CWorksheets.h"


class ExcelOpera
{
public:
	ExcelOpera();
	~ExcelOpera();

	void CreateExcelFile();
	void OpenExistExcelFile(CString filePath);

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


};

