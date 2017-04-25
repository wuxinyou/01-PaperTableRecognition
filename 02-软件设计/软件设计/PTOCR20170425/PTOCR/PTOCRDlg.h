
// PTOCRDlg.h : header file
//

#pragma once

#include "ExcelOpera.h"
#include "fileOpera.h"
#include "recognizeBar.h"
#include "ProcessImage.h"
#include "readXML.h"


// CPTOCRDlg dialog
class CPTOCRDlg : public CDialogEx
{
// Construction
public:
	CPTOCRDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PTOCR_DIALOG };

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
	FileOpera fileOpera;
	ExcelOpera excelOpera;
	RecBar bar;
	ProcessImage processImage;
	ReadXML sheetXML;




private:
	void MyInit();





};
