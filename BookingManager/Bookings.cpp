// Bookings.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "Bookings.h"
#include "afxdialogex.h"


// Bookings dialog

IMPLEMENT_DYNAMIC(Bookings, CDialogEx)

Bookings::Bookings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKING_DIALOG, pParent)
{

}

Bookings::~Bookings()
{
}

void Bookings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, bookingList);
	DDX_Control(pDX, IDC_LIST1, bookingList);
}


BEGIN_MESSAGE_MAP(Bookings, CDialogEx)
END_MESSAGE_MAP()


// Bookings message handlers


//BOOL Bookings::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//	bookingList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 50);
//	bookingList.InsertColumn(1, _T("Surname"), LVCFMT_LEFT, 90);
//	bookingList.InsertColumn(2, _T("Pax"), LVCFMT_LEFT, 30);
//	bookingList.InsertColumn(3, _T("Time"), LVCFMT_LEFT, 50);
//	bookingList.InsertColumn(4, _T("Date"), LVCFMT_LEFT, 50);
//	bookingList.InsertColumn(5, _T("Occasion"), LVCFMT_LEFT, 50);
//	bookingList.InsertColumn(6, _T("Contact"), LVCFMT_LEFT, 50);
//	bookingList.SetExtendedStyle(bookingList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
//
//	//IspisRezervacija();
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // EXCEPTION: OCX Property Pages should return FALSE
//}


BOOL Bookings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	bookingList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 150);
	bookingList.InsertColumn(1, _T("Surname"), LVCFMT_LEFT, 150);
	bookingList.InsertColumn(2, _T("Pax"), LVCFMT_LEFT, 50);
	bookingList.InsertColumn(3, _T("Time"), LVCFMT_LEFT, 100);
	bookingList.InsertColumn(4, _T("Date"), LVCFMT_LEFT, 100);
	bookingList.InsertColumn(5, _T("Occasion"), LVCFMT_LEFT, 120);
	bookingList.InsertColumn(6, _T("Contact"), LVCFMT_LEFT, 150);
	bookingList.SetExtendedStyle(bookingList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
