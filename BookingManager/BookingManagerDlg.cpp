
// BookingManagerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BookingManager.h"
#include "BookingManagerDlg.h"
#include "afxdialogex.h"
#include "CUser.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBookingManagerDlg dialog



CBookingManagerDlg::CBookingManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKINGMANAGER_DIALOG, pParent)
	, m_User(_T(""))
	, m_Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookingManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER, m_User);
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
}

BEGIN_MESSAGE_MAP(CBookingManagerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBookingManagerDlg::OnLoginClicked)
END_MESSAGE_MAP()


// CBookingManagerDlg message handlers

BOOL CBookingManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBookingManagerDlg::OnPaint()
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
HCURSOR CBookingManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CBookingManagerDlg::OnLoginClicked()
{
	UpdateData(TRUE);
	CUser userLogin;
	CString s;
	userLogin.m_strFilter.Format(_T("[Username] = '%s' AND [Password] = '%s'"), m_User, m_Password);
	userLogin.Open();
	if (!userLogin.IsEOF()) {
		MainDlg App(m_User, this);
		CDialogEx::OnOK();
		App.DoModal();
	}
	else {
		s.LoadString(AFX_IDS_USER_EXCEPTION);
		AfxMessageBox(s);
	}
	userLogin.Close();

	UpdateData(FALSE);
}
