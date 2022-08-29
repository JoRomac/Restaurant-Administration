// Bookings.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "Bookings.h"
#include "afxdialogex.h"
#include "NewReservation.h"
#include "Guest.h"
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
	DDX_Control(pDX, IDC_LIST1, bookingList);
}


BEGIN_MESSAGE_MAP(Bookings, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_RESERVATION, &Bookings::OnAddReservationClicked)
	ON_BN_CLICKED(IDC_DISPLAY_ALL, &Bookings::OnDisplayAllClicked)
END_MESSAGE_MAP()


// Bookings message handlers




BOOL Bookings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	bookingList.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 30);
	bookingList.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 130);
	bookingList.InsertColumn(2, _T("Surname"), LVCFMT_LEFT, 170);
	bookingList.InsertColumn(3, _T("Pax"), LVCFMT_LEFT, 50);
	bookingList.InsertColumn(4, _T("Time"), LVCFMT_LEFT, 100);
	bookingList.InsertColumn(5, _T("Date"), LVCFMT_LEFT, 100);
	bookingList.InsertColumn(6, _T("Occasion"), LVCFMT_LEFT, 120);
	bookingList.InsertColumn(7, _T("Contact"), LVCFMT_LEFT, 120);
	bookingList.SetExtendedStyle(bookingList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void Bookings::OnAddReservationClicked()
{
	NewReservation reservation;
	reservation.DoModal();
}



void Bookings::OnDisplayAllClicked()
{
	Guest guest;
	bookingList.DeleteAllItems();
	guest.Open();
	while (!guest.IsEOF()) {
		CString id;
		id.Format(_T("%ld"), guest.m_Id);
		int elementAtIndex = bookingList.InsertItem(0, id);
		bookingList.SetItemText(elementAtIndex, 1, guest.m_Name);
		bookingList.SetItemText(elementAtIndex, 2, guest.m_Surname);
		bookingList.SetItemText(elementAtIndex, 3, guest.m_Pax);
		bookingList.SetItemText(elementAtIndex, 4, guest.m_Time.Format(_T("%H:%M")));//"%H:%M:%S"
		bookingList.SetItemText(elementAtIndex, 5, guest.m_Date.Format(_T("%m:%d:%Y")));//"%m:%d:%Y"
		bookingList.SetItemText(elementAtIndex, 6, guest.m_Occasion);
		bookingList.SetItemText(elementAtIndex, 7, guest.m_Contact);
		guest.MoveNext();
	}
	guest.Close();
}
