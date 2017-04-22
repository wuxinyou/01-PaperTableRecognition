
// MFC_ExcelTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_ExcelTest.h"
#include "MFC_ExcelTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ExcelTestDlg dialog



CMFC_ExcelTestDlg::CMFC_ExcelTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_ExcelTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ExcelTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_ExcelTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFC_ExcelTestDlg message handlers

BOOL CMFC_ExcelTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	//导出
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		this->MessageBox(_T("无法创建Excel应用！"));
		return TRUE;
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFC_ExcelTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFC_ExcelTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFC_ExcelTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

