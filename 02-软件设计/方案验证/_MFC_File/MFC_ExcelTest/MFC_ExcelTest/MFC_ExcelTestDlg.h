
// MFC_ExcelTestDlg.h : header file

#include"CApplication.h"
#include"CFont0.h"
#include"CRange.h"
#include"CRanges.h"
#include"CWorkbook.h"
#include"CWorkbooks.h"
#include"CWorksheet.h"
#include"CWorksheets.h"
//

#pragma once


// CMFC_ExcelTestDlg dialog
class CMFC_ExcelTestDlg : public CDialogEx
{
// Construction
public:
	CMFC_ExcelTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFC_EXCELTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

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
