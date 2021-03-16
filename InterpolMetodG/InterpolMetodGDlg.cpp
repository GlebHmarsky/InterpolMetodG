
// InterpolMetodGDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "InterpolMetodG.h"
#include "InterpolMetodGDlg.h"
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
}

BEGIN_MESSAGE_MAP(CInterpolMetodGDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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

#define _USE_MATH_DEFINES
#include<math.h>
double A = -M_PI * 5, B = M_PI / 2, C = -0.5, D = 1;
double RX1 = 50, RY1 = 20, RX2 = 800, RY2 = 800;
double Function(double x) {
	return exp(x);
}

double Perer(double x) {
	return RY2 - ((RY2 - RY1) * ((Function(x) - C) / (D - C)));
}

void CInterpolMetodGDlg::OnPaint()
{

	double x0 = RX1,
		y0 = Perer(A),
		scale = 15;

	CPoint pStart(x0, y0), pCur, pPrev;
	CPaintDC ClientDC(this);
	ClientDC.Rectangle(RX1, RY1, RX2, RY2);
	CPen m_NormalPen;
	m_NormalPen.CreatePen(PS_DEFAULT, 1, RGB(0, 200, 0));
	ClientDC.SelectObject(&m_NormalPen);


	CRect ClipRect;
	CRect DimRect;
	CRect IntRect;


	//ClientDC.GetClipBox(&ClipRect); // Получить недейств. область

	//
	//	
	//	DimRect = ClientDC.Line->GetDimRect();
	//	if (IntRect.IntersectRect(DimRect, ClipRect))
	//		PFigure->Draw(pDC);


	ClientDC.IntersectClipRect(RX1, RY1, RX2, RY2);
	pPrev = pStart;
	ClientDC.MoveTo(pPrev);
	for (double x = A; x <= B; x += 0.01) {

		pCur.x = (RX1 + ((RX2 - RX1) * ((x - A) / (B - A))));
		pCur.y = Perer(x);

		ClientDC.LineTo(pCur);


		//::Sleep(2);
	}


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
		//RECT ellipse;
		//CPaintDC dc(this);
		//ellipse.top = 1;
		//ellipse.left = 3;
		//ellipse.bottom = 1 + 5;
		//ellipse.right = 3 + 5;
		//dc.Ellipse(&ellipse);

		////Рисуем квадратик с красным бордюром (сменим перо)
		//// и зеленой закрашенной областью (сменим кисть).
		//CPen aPen;
		//aPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//CPen* pOldPen = dc.SelectObject(&aPen);
		//CBrush aBrush;
		//aBrush.CreateSolidBrush(RGB(0, 255, 0));
		//CBrush* pOldBrush = dc.SelectObject(&aBrush);
		//dc.Rectangle(50, 100, 60, 110);
		////Восстанавливаем старые перо и кисть.
		//dc.SelectObject(pOldPen);
		//dc.SelectObject(pOldBrush);
		CDialog::OnPaint();
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterpolMetodGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

