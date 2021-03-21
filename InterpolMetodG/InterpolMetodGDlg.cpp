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

#include "InfInt.h"
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
	m_ControlBorderA.SetWindowTextW(L"-1");		// 1.55
	m_ControlBorderB.SetWindowTextW(L"0");	// 1.58
	m_ControlBorderC.SetWindowTextW(L"-2");	// -0.1
	m_ControlBorderD.SetWindowTextW(L"2");	// 2.1

	m_ControlParamAlpha.SetWindowTextW(L"1");
	m_ControlParamBeta.SetWindowTextW(L"1");
	m_ControlParamGamma.SetWindowTextW(L"1");
	m_ControlParamDelta.SetWindowTextW(L"1");
	m_ControlParamEpsi.SetWindowTextW(L"1");
	m_ControlParamMu.SetWindowTextW(L"1");

	m_NumKnoots.SetWindowTextW(L"50");
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


double InterPoly[2][101], Values[2][101];
double deltsY[101][101];
int CurrentNomKnoots;

double CInterpolMetodGDlg::PolynomFunction(double x) {
	double Result = 0;
	Result += InterPoly[0][0]; //первое слогаемое: y0
	InterPoly[1][0] = 1;
	for (int i = 1; i <= CurrentNomKnoots; i++){		
		InterPoly[1][i] = (InterPoly[1][i - 1] * (((x - logicalCentralPoint) / logicalStep) + (int)(i % 2 == 0 ? -i / 2 : i / 2))) / i;
		Result += InterPoly[1][i] * InterPoly[0][i];
	}
	return Result;
}

// return sin(x) + cos(tan(x))
double CInterpolMetodGDlg::Function(double x) {
	//return sin(x);
	return alpha * sin(pow(x, beta)) + gamma * cos(tan(delta * x));
}

void CInterpolMetodGDlg::calculateValues() {
	Values[0][0] = A;
	Values[1][0] = Function(A);
	for (int i = 1; i < CurrentNomKnoots; i++) {
		Values[0][i] = Values[0][i-1] + logicalStep;
		Values[1][i] = Function(Values[0][i]);
	}	
}
void CInterpolMetodGDlg::CalculateDeltaY() {		
	for (int i = 0; i < CurrentNomKnoots; i++) { //ДОВЕРЯТЬ МОЖНО! ;)
		deltsY[0][i] = Values[1][i];
	}

	for (int step = 1; step < CurrentNomKnoots; step++)
		for (int i = 0; i < CurrentNomKnoots - step; i++)
			deltsY[step][i] = deltsY[step - 1][i + 1] - deltsY[step - 1][i];

	
	for (int i = 0; i < CurrentNomKnoots; i++) {
		InterPoly[0][i] = deltsY[i][(CurrentNomKnoots - i) / 2];
	}
}

void CInterpolMetodGDlg::OnPaint()
{
	CurrentNomKnoots = 2 * N + 1;
	logicalCentralPoint = (A + B) / 2;
	logicalStep = (B - A) / (CurrentNomKnoots-1);
	

	CPaintDC ClientDC(this);
	ClientDC.Rectangle(RX1, RY1, RX2, RY2);
	ClientDC.IntersectClipRect(RX1, RY1, RX2, RY2);

	CPen m_LinePen;

	
	/*--- ЛИНИИ ----*/
	m_LinePen.CreatePen(PS_DEFAULT, 1, RGB(200, 200, 200));
	ClientDC.SelectObject(&m_LinePen);
	for (int pos = RY1; pos < RY2; pos+=(RY2-RY1)/6){
		ClientDC.MoveTo(RX1, pos);
		ClientDC.LineTo(RX2, pos);
	}
	ClientDC.TextOutW(RX1 + 10, RY1 + 40, L"Привет;)");


	calculateValues();
	CalculateDeltaY();
	
	if (m_MainFunc) {
		double x0 = RX1, y0 = RY2 - ((RY2 - RY1) * ((Function(A) - C) / (D - C)));
		CPoint pStart(x0, y0), pCur;
		CPen m_NormalPen;
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(10, 184, 10));

		ClientDC.SelectObject(&m_NormalPen);
		

		ClientDC.MoveTo(pStart);
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1) {
			pCur.x = RX1 + ((RX2 - RX1) * ((x - A) / (B - A)));
			pCur.y = RY2 - ((RY2 - RY1) * ((Function(x) - C) / (D - C)));

			ClientDC.LineTo(pCur);			
		}
	}
	if (m_Poly) {
		double x0 = RX1, y0 = RY2 - ((RY2 - RY1) * ((PolynomFunction(A) - C) / (D - C)));
		CPoint pStart(x0, y0), pCur;
		CPen m_NormalPen;
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(252, 132, 6));

		ClientDC.SelectObject(&m_NormalPen);

		ClientDC.MoveTo(pStart);
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1) {
			pCur.x = RX1 + ((RX2 - RX1) * ((x - A) / (B - A)));
			pCur.y = RY2 - ((RY2 - RY1) * ((PolynomFunction(x) - C) / (D - C)));

			ClientDC.LineTo(pCur);
		}
	}
	if (m_Raznost) {
		double x0 = RX1, y0 = RY2 - ((RY2 - RY1) * ((PolynomFunction(A) - C) / (D - C)));
		CPoint pStart(x0, y0), pCur;
		CPen m_NormalPen;
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(18, 83, 166));

		ClientDC.SelectObject(&m_NormalPen);

		ClientDC.MoveTo(pStart);
		double MaxY = 0, MaxX=0;
		for (double x = A; x <= B; x += (B - A) / (RX2 - RX1) * 0.1) {
			pCur.x = RX1 + ((RX2 - RX1) * ((x - A) / (B - A)));
			
			pCur.y = RY2 - ((RY2 - RY1) * (abs(Function(x) - PolynomFunction(x)) - C) / (D - C));
			if (MaxY < pCur.y) MaxX = pCur.x;
			ClientDC.LineTo(pCur);
		}
		
		CPen m_NewLinePen;
		m_NewLinePen.CreatePen(PS_DEFAULT, 3, RGB(250, 0, 0));

		ClientDC.SelectObject(&m_NewLinePen);
		ClientDC.MoveTo(MaxX,RY1);
		ClientDC.LineTo(MaxX, RY2);
	}
	if (m_DiffMainFunc) {
		CPen m_NormalPen;
		m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(120, 0, 220));
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