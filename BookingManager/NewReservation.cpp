// NewReservation.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "NewReservation.h"
#include "afxdialogex.h"
#include "Guest.h"
#include "resource.h"

// NewReservation dialog

IMPLEMENT_DYNAMIC(NewReservation, CDialogEx)

NewReservation::NewReservation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_RESERVATION, pParent)
	, m_Name(_T(""))
	, m_LastName(_T(""))
	, m_Pax(_T(""))
	, m_Occasion(_T(""))
	, m_Contact(_T(""))
{

}

NewReservation::~NewReservation()
{
}

void NewReservation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_LASTNAME, m_LastName);
	DDX_Text(pDX, IDC_PAX, m_Pax);
	DDX_Control(pDX, IDC_TIME, m_Time);
	DDX_Control(pDX, IDC_DATE, m_Date);
	DDX_Text(pDX, IDC_OCCASION, m_Occasion);
	DDX_Text(pDX, IDC_CONTACT, m_Contact);
}


BEGIN_MESSAGE_MAP(NewReservation, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewReservation::OnAddCliked)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE, &NewReservation::OnDtnDatetimechangeDate)
END_MESSAGE_MAP()


// NewReservation message handlers

void NewReservation::OnAddCliked()
{
	DWORD dwResult = m_Time.GetTime(t);
	DWORD dwResult1 = m_Date.GetTime(d);
	UpdateData(TRUE);
	Guest guest;
	guest.Open();
	guest.AddNew();
	guest.m_Name = m_Name;
	guest.m_Surname = m_LastName;
	guest.m_Pax = m_Pax;
	guest.m_Time = t;
	guest.m_Date = d;
	guest.m_Occasion = m_Occasion;
	guest.m_Contact = m_Contact;
	if (!guest.Update()) {
		AfxMessageBox(_T("Unsuccessful attempt"));
	}
	guest.Close();
	CDialogEx::OnOK();
}


void NewReservation::OnDtnDatetimechangeDate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	SYSTEMTIME st;
	GetSystemTime(&st);
	CTime t = pDTChange->st;
	if (t.GetDay() - st.wDay < 0 || t.GetMonth() - st.wMonth < 0 || t.GetYear() - st.wYear < 0) {
		AfxMessageBox(_T("Invalid date"));
		VERIFY(m_Date.SetTime(&st));
	}
	*pResult = 0;
}
