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
//double A, B, C, D;
//double alpha, beta, gamma, delta, epsi, mu;
//int N;
//int RX1 = 50, RY1 = 20, RX2 = 800, RY2 = 800;

//CRect GraficRect(RX1, RY1, RX2, RY2);
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
	, m_MainFunc(TRUE)
	, m_Poly(TRUE)
    , m_Raznost(FALSE)
	, m_DiffMainFunc(FALSE)
	, m_DiffPoly(FALSE)
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
	DDX_Check(pDX, IDC_CHECKMainFunc, m_MainFunc);
	DDX_Check(pDX, IDC_CHECKDiffMainFunc, m_DiffMainFunc);
	DDX_Check(pDX, IDC_CHECKPoly, m_Poly);
	DDX_Check(pDX, IDC_CHECKDiffPoly, m_DiffPoly);
	DDX_Check(pDX, IDC_CHECKRaznost, m_Raznost);
	DDX_Control(pDX, IDC_EDITNUMKNOTS, m_NumKnoots);
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
	ON_BN_CLICKED(IDC_CHECKPoly, &CInterpolMetodGDlg::OnBnClickedCheckpoly)
	ON_BN_CLICKED(IDC_CHECKRaznost, &CInterpolMetodGDlg::OnBnClickedCheckraznost)
	ON_BN_CLICKED(IDC_CHECKDiffMainFunc, &CInterpolMetodGDlg::OnBnClickedCheckdiffmainfunc)
	ON_BN_CLICKED(IDC_CHECKDiffPoly, &CInterpolMetodGDlg::OnBnClickedCheckdiffpoly)
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
	m_ControlBorderA.SetWindowTextW(L"-4");		// 1.55
	m_ControlBorderB.SetWindowTextW(L"4");	// 1.58
	m_ControlBorderC.SetWindowTextW(L"-2");	// -0.1
	m_ControlBorderD.SetWindowTextW(L"2");	// 2.1

	m_ControlParamAlpha.SetWindowTextW(L"1");
	m_ControlParamBeta.SetWindowTextW(L"1");
	m_ControlParamGamma.SetWindowTextW(L"1");
	m_ControlParamDelta.SetWindowTextW(L"1");
	m_ControlParamEpsi.SetWindowTextW(L"1");
	m_ControlParamMu.SetWindowTextW(L"1");

	m_NumKnoots.SetWindowTextW(L"3");
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
double CInterpolMetodGDlg::Function(double x) {
	return sin(x);
	return alpha * sin(pow(x, beta)) + gamma * cos(tan(delta * x));
}

double InterPoly[2][101], Values[2][101];
double deltsY[101][101];

void CInterpolMetodGDlg::calculateValues() {
	Values[0][0] = A;
	Values[1][0] = Function(A);
	for (int i = 1; i <= 2*N+1; i++) {
		Values[0][i] = Values[0][i-1] + logicalStep;
		Values[1][i] = -Function(Values[0][i]);
	}	
}

void CInterpolMetodGDlg::CalculateDeltaY() {
	InterPoly[0][0] = Function(A);
		
	for (int i = 0; i < 2 * N + 1; i++) {
		deltsY[0][i] = Values[1][i];
	}

	for (int step = 1; step < 2 * N + 1; step++)
		for (int i = 0; i < 2 * N + 1 - step; i++)
			deltsY[step][i] = deltsY[step - 1][i + 1] - deltsY[step - 1][i];
}

void CInterpolMetodGDlg::OnPaint()
{
	CPaintDC ClientDC(this);
	ClientDC.Rectangle(RX1, RY1, RX2, RY2);

	if (m_MainFunc) {
		double x0 = RX1, y0 = RY2 - ((RY2 - RY1) * ((Function(A) - C) / (D - C)));
		CPoint pStart(x0, y0), pCur;
		CPen m_NormalPen;
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(0, 200, 0));

		ClientDC.SelectObject(&m_NormalPen);
		ClientDC.IntersectClipRect(RX1, RY1, RX2, RY2);

		ClientDC.MoveTo(pStart);
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1) {
			pCur.x = RX1 + ((RX2 - RX1) * ((x - A) / (B - A)));
			pCur.y = RY2 - ((RY2 - RY1) * ((Function(x) - C) / (D - C)));

			ClientDC.LineTo(pCur);			
		}
	}
	if (m_Poly) {
		logicalCentralPoint = (A + B) / 2;
		logicalStep = (B - A) / (2 * N + 1);
		calculateValues();
		CalculateDeltaY();
	}
	if (m_Raznost) {

	}
	if (m_DiffMainFunc) {

	}
	if (m_DiffPoly) {

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
	CRect GraficRect(RX1, RY1, RX2, RY2);
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

/*----------------------	УПРАВЛЕНИЕ ПОЛЯМИ ВЫВОДОВ ФУНКЦИИ	------------------------*/
void CInterpolMetodGDlg::OnBnClickedCheckmainfunc()
{
	m_MainFunc = IsDlgButtonChecked(IDC_CHECKMainFunc);
}
void CInterpolMetodGDlg::OnBnClickedCheckpoly()
{
	m_Poly = IsDlgButtonChecked(IDC_CHECKPoly);
}
void CInterpolMetodGDlg::OnBnClickedCheckraznost()
{
	m_Raznost = IsDlgButtonChecked(IDC_CHECKRaznost);
}
void CInterpolMetodGDlg::OnBnClickedCheckdiffmainfunc()
{
	m_DiffMainFunc = IsDlgButtonChecked(IDC_CHECKDiffMainFunc);
}
void CInterpolMetodGDlg::OnBnClickedCheckdiffpoly()
{
	m_DiffPoly = IsDlgButtonChecked(IDC_CHECKDiffPoly);
}


void CInterpolMetodGDlg::OnEnChangeEditnumknots()
{
	m_NumKnoots.GetWindowTextW(tmp);
	N = _wtof(tmp);
}