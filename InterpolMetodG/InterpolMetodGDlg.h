﻿
// InterpolMetodGDlg.h : header file
//

#pragma once


// CInterpolMetodGDlg dialog
class CInterpolMetodGDlg : public CDialog
{
// Construction
public:
	CInterpolMetodGDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INTERPOLMETODG_DIALOG };
#endif

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
public:
	afx_msg void OnEnChangeEditA();

	CEdit m_ControlBorderA;
	CEdit m_ControlBorderB;
	CEdit m_ControlBorderD;
	CEdit m_ControlBorderC;
	CEdit m_ControlParamAlpha;
	CEdit m_ControlParamBeta;
	CEdit m_ControlParamGamma;
	CEdit m_ControlParamDelta;
	CEdit m_ContolParamEpsi;
	CEdit m_ControlParamMu;
	afx_msg void OnEnChangeEditB();
	afx_msg void OnEnChangeEditC();
	afx_msg void OnEnChangeEditD();
};
