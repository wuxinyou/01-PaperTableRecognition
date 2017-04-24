
#include "stdafx.h"
#include "ExcelOpera.h"


ExcelOpera::ExcelOpera()
{
	//初始化OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("初始化Ole出错！"));
		return ;
	}

}


ExcelOpera::~ExcelOpera()
{
}


/*********************************************************
说明：创建Excel文件
输入：无

返回：无
***********************************************************/
void ExcelOpera::CreateExcelFile()
{
	//导出
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		//this->MessageBox(_T("无法创建Excel应用！"));
		return;
	}
	books = app.get_Workbooks();
	//打开Excel，其中pathname为Excel表的路径名  

	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	//获得坐标为（A，1）和（B，1）的两个单元格 
	range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));
	//设置单元格类容为Hello Exce
	range.put_Value2(COleVariant(_T("Hello Excel")));
	//选择整列，并设置宽度为自适应 
	cols = range.get_EntireColumn();
	cols.AutoFit();
	//设置字体为粗体 
	font = range.get_Font();
	font.put_Bold(COleVariant((short)TRUE));
	//获得坐标为（C，2）单元格 
	range = sheet.get_Range(COleVariant(_T("C2")), COleVariant(_T("C5")));
	//设置公式“=RAND()*100000”
	range.put_Formula(COleVariant(_T("=RAND()*100000")));
	//设置数字格式为货币型  
	range.put_NumberFormat(COleVariant(_T("$0.00")));
	//选择整列，并设置宽度为自适应  
	cols = range.get_EntireColumn();
	cols.AutoFit();


	//显示Excel表
	//app.put_Visible(TRUE);
	//app.put_UserControl(TRUE);


	TCHAR FilePath[MAX_PATH];
	GetModuleFileName(NULL, FilePath, MAX_PATH);
	(_tcsrchr(FilePath, '\\'))[1] = 0;
	lstrcat(FilePath, _T("MFC_ExcelTest.xlsx"));

	//CString szFilePath;
	//szFilePath.Format(_T("%s"), FilePath);


	//保存Excel
	//book.SaveAs(_T("./MFC_ExcelTest"));
	book.SaveAs(COleVariant(FilePath), covOptional,
		covOptional, covOptional,
		covOptional, covOptional, (long)0,
		covOptional, covOptional, covOptional,
		covOptional, covOptional); //与的不同，是个参数的，直接在后面加了两个covOptional成功了



	app.Quit();
	//m_ExlApp一定要释放，否则程序结束后还会有一个Excel进程驻留在内存中，而且程序重复运行的时候会出错   
	app.ReleaseDispatch();
}

/*********************************************************
说明：打开指定Excel文件
输入：filePath：文件全路径

返回：无
***********************************************************/
void ExcelOpera::OpenExistExcelFile(CString filePath)
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		//this->MessageBox(_T("无法创建Excel应用！"));
		return;
	}
	books = app.get_Workbooks();

	LPDISPATCH lpDisp;  //接口指针  
	//books = app.get_Workbooks();
	lpDisp = books.Open(filePath,
		covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional
		);                  //与的不同，是个参数的，直接在后面加了两个covOptional成功了  
	book.AttachDispatch(lpDisp);

	//下面进行写操作
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));
	//获得坐标为（A，1）和（B，1）的两个单元格 
	range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));
	//设置单元格类容为Hello Exce
	range.put_Value2(COleVariant(_T("Hello OpenExistExcelFile")));

	book.Save();



	app.Quit();
	//m_ExlApp一定要释放，否则程序结束后还会有一个Excel进程驻留在内存中，而且程序重复运行的时候会出错   
	app.ReleaseDispatch();

}