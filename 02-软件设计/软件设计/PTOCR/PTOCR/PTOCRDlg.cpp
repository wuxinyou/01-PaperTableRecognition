
// PTOCRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PTOCR.h"
#include "PTOCRDlg.h"
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


// CPTOCRDlg dialog



CPTOCRDlg::CPTOCRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPTOCRDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPTOCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPTOCRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CPTOCRDlg message handlers

BOOL CPTOCRDlg::OnInitDialog()
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

	ShowWindow(SW_NORMAL);


	MyInit();
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*************************************************************
说明：我的初始化函数
**************************************************************/
void CPTOCRDlg::MyInit()
{
	Mat image = imread("zBarSample.jpg");
	if (!image.data)
	{
		cout << "请确认图片" << endl;
		system("pause");
		return ;
	}
	//识别条形码
	bar.recBar(image);

	TRACE(bar.getTypeName().c_str());
	TRACE(bar.getData().c_str());


	CString test = CString((bar.getData().c_str()));

	imshow("Source Image", image);

	//查找定位边框，并返回坐标
	processImage.ReadImage(image);
	processImage.FindOutBorder();

	//擦除所有表格边框
	processImage.WipeSheetBorder();
	
	imshow("AfterWipeBorder", image);



	CString strDir = _T("E:\\12-MyOpenSourceProject\\01-PaperTableRecognition\\02-软件设计\\方案验证\\_MFC_File\\FileDataBase");
	
	CString fileName = CString(bar.getData().c_str());
	fileName += _T(".xlsx");
	CString findFilePath=NULL; 

	string xmlFile = "E:\\12-MyOpenSourceProject\\01-PaperTableRecognition\\02-软件设计\\方案验证\\_MFC_File\\FileDataBase\\1521611168303.xml";
	//读取XML
	sheetXML.readXMLFile(xmlFile);
	TRACE(_T("sheetXML = %d,%d,%d,%d\r\n"), sheetXML.border.x, sheetXML.border.y, sheetXML.border.width, sheetXML.border.height);

	//查找文件
	findFilePath = fileOpera.FindFilePath(strDir, fileName, 0);   //查找文件

	TRACE(_T("findFilePath = %s\r\n"), findFilePath);
	if (findFilePath)
	{		
		CString copyFile = strDir + _T("\\") + _T("CopyFile.xlsx");
		CopyFile(findFilePath, copyFile, false);                //拷贝文件
		excelOpera.OpenExistExcelFile(copyFile);                //打开Excel，并操作
	}

}



void CPTOCRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPTOCRDlg::OnPaint()
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
HCURSOR CPTOCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

