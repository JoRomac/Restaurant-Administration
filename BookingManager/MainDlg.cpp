// MainDlg.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Bookings.h"

// MainDlg dialog

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(const CString name, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DLG, pParent)
{

}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MainDlg::OnBookingClicked)
END_MESSAGE_MAP()


// MainDlg message handlers


BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();




	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void MainDlg::OnBookingClicked()
{
	Bookings book;
	book.DoModal();
	// TODO: Add your control notification handler code here
}
