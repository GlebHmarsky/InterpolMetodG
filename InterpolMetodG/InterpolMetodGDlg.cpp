
// InterpolMetodGDlg.cpp : implementation file
//
#define _USE_MATH_DEFINES

#include "pch.h"
#include "framework.h"
#include "InterpolMetodG.h"
#include "InterpolMetodGDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//			Глобальные переменные!
double A, B, C, D;
double RX1 = 50, RY1 = 20, RX2 = 800, RY2 = 800;
double alpha, beta, gamma, delta, epsi, mu;
CRect GraficRect(RX1, RY1, RX2, RY2);
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CInterpolMetodGDlg dialog



CInterpolMetodGDlg::CInterpolMetodGDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_INTERPOLMETODG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterpolMetodGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_A, m_ControlBorderA);
	DDX_Control(pDX, IDC_EDIT_B, m_ControlBorderB);
	DDX_Control(pDX, IDC_EDIT_C, m_ControlBorderC);
	DDX_Control(pDX, IDC_EDIT_D, m_ControlBorderD);

	DDX_Control(pDX, IDC_alpha, m_ControlParamAlpha);
	DDX_Control(pDX, IDC_beta, m_ControlParamBeta);
	DDX_Control(pDX, IDC_gamma, m_ControlParamGamma);
	DDX_Control(pDX, IDC_delta, m_ControlParamDelta);
	DDX_Control(pDX, IDC_epsi, m_ControlParamEpsi);
	DDX_Control(pDX, IDC_mu, m_ControlParamMu);
}

BEGIN_MESSAGE_MAP(CInterpolMetodGDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDITNUMKNOTS, &CInterpolMetodGDlg::OnEnChangeEditnumknots)
	ON_BN_CLICKED(IDC_CHECKMainFunc, &CInterpolMetodGDlg::OnBnClickedCheckmainfunc)
	ON_BN_CLICKED(IDC_BUTTONPAINT, &CInterpolMetodGDlg::OnBnClickedButtonpaint)
	ON_EN_CHANGE(IDC_mu, &CInterpolMetodGDlg::OnEnChangemu)
	ON_EN_CHANGE(IDC_epsi, &CInterpolMetodGDlg::OnEnChangeepsi)
	ON_EN_CHANGE(IDC_delta, &CInterpolMetodGDlg::OnEnChangedelta)
	ON_EN_CHANGE(IDC_gamma, &CInterpolMetodGDlg::OnEnChangegamma)
	ON_EN_CHANGE(IDC_beta, &CInterpolMetodGDlg::OnEnChangebeta)
	ON_EN_CHANGE(IDC_alpha, &CInterpolMetodGDlg::OnEnChangealpha)
	ON_EN_CHANGE(IDC_EDIT_A, &CInterpolMetodGDlg::OnEnChangeEditA)
	ON_EN_CHANGE(IDC_EDIT_D, &CInterpolMetodGDlg::OnEnChangeEditD)
	ON_EN_CHANGE(IDC_EDIT_C, &CInterpolMetodGDlg::OnEnChangeEditC)
	ON_EN_CHANGE(IDC_EDIT_B, &CInterpolMetodGDlg::OnEnChangeEditB)
END_MESSAGE_MAP()


// CInterpolMetodGDlg message handlers

BOOL CInterpolMetodGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	m_ControlBorderA.SetWindowTextW(L"1.55");
	m_ControlBorderB.SetWindowTextW(L"1.58");
	m_ControlBorderC.SetWindowTextW(L"-0.1");
	m_ControlBorderD.SetWindowTextW(L"2.1");

	m_ControlParamAlpha.SetWindowTextW(L"1");
	m_ControlParamBeta.SetWindowTextW(L"1");
	m_ControlParamGamma.SetWindowTextW(L"1");
	m_ControlParamDelta.SetWindowTextW(L"1");
	m_ControlParamEpsi.SetWindowTextW(L"1");
	m_ControlParamMu.SetWindowTextW(L"1");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterpolMetodGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

// return sin(x) + cos(tan(x))
double Function(double x) {
	return alpha * sin(pow(x, beta)) + gamma * cos(tan(delta * x));
}

double Perer(double x) {
	return RY2 - ((RY2 - RY1) * ((Function(x) - C) / (D - C)));
}

void CInterpolMetodGDlg::OnPaint()
{
	double x0 = RX1, y0 = Perer(A);
	CPoint pStart(x0, y0), pCur, pPrev;
	CPen m_NormalPen;
	m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(0, 200, 0));

	CPaintDC ClientDC(this);
	ClientDC.Rectangle(RX1, RY1, RX2, RY2);
	ClientDC.SelectObject(&m_NormalPen);
	ClientDC.IntersectClipRect(RX1, RY1, RX2, RY2);
	
	pPrev = pStart;
	ClientDC.MoveTo(pPrev);
	for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1) {

		pCur.x = RX1 + ((RX2 - RX1) * ((x - A) / (B - A)));
		pCur.y = Perer(x);

		ClientDC.LineTo(pCur);
		//::Sleep(1);
	}

	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // device context for painting
	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
	//	// Center icon in client rectangle
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;
	//	// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{		
	//	CDialog::OnPaint();
	//}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterpolMetodGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CInterpolMetodGDlg::OnBnClickedButtonpaint()
{
	InvalidateRect(GraficRect);
	UpdateWindow();
	CInterpolMetodGDlg::OnPaint();
}

CString tmp;
/*----------------------	УПРАВЛЕНИЕ ГРАНИЦАМИ	------------------------*/
void CInterpolMetodGDlg::OnEnChangeEditA()
{	
	m_ControlBorderA.GetWindowTextW(tmp);
	A = _wtof(tmp); 
}
void CInterpolMetodGDlg::OnEnChangeEditB()
{
	m_ControlBorderB.GetWindowTextW(tmp);
	B = _wtof(tmp);
}
void CInterpolMetodGDlg::OnEnChangeEditC()
{
	m_ControlBorderC.GetWindowTextW(tmp);
	C = _wtof(tmp);
}
void CInterpolMetodGDlg::OnEnChangeEditD()
{
	m_ControlBorderD.GetWindowTextW(tmp);
	D = _wtof(tmp);	
}

/*----------------------	УПРАВЛЕНИЕ ПАРАМЕТРАМИ ФУНКЦИИ	------------------------*/
void CInterpolMetodGDlg::OnEnChangealpha()
{
	m_ControlParamAlpha.GetWindowTextW(tmp);
	alpha = _wtof(tmp);
	
}
void CInterpolMetodGDlg::OnEnChangebeta()
{
	m_ControlParamBeta.GetWindowTextW(tmp);
	beta = _wtof(tmp);	
}
void CInterpolMetodGDlg::OnEnChangegamma()
{
	m_ControlParamGamma.GetWindowTextW(tmp);
	gamma = _wtof(tmp);
	
}
void CInterpolMetodGDlg::OnEnChangedelta()
{
	m_ControlParamDelta.GetWindowTextW(tmp);
	delta = _wtof(tmp);	
}
void CInterpolMetodGDlg::OnEnChangeepsi()
{
	m_ControlParamEpsi.GetWindowTextW(tmp);
	epsi = _wtof(tmp);	
}
void CInterpolMetodGDlg::OnEnChangemu()
{
	m_ControlParamMu.GetWindowTextW(tmp);
	mu = _wtof(tmp);
}







void CInterpolMetodGDlg::OnBnClickedCheckmainfunc()
{
	// TODO: Add your control notification handler code here
}


void CInterpolMetodGDlg::OnEnChangeEditnumknots()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
