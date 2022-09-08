// UpdateReservation.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "UpdateReservation.h"
#include "afxdialogex.h"
#include "Guest.h"
#include "resource.h"
// UpdateReservation dialog

IMPLEMENT_DYNAMIC(UpdateReservation, CDialogEx)

UpdateReservation::UpdateReservation(int bookingId, CTime t, CTime d, CString pax, CString occasion, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_RES_DLG, pParent)
	,bookingId(bookingId)
	, pax(pax)
	, occasion(occasion)
	, time(t)
	, date(d)
{

}

UpdateReservation::~UpdateReservation()
{
}
BOOL UpdateReservation::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_EDIT_UP_PAX, pax);
	VERIFY(m_Time.SetTime(&time));
	VERIFY(m_Date.SetTime(&date));
	SetDlgItemText(IDC_UP_OCCASION, occasion);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void UpdateReservation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UP_PAX, m_Pax);
	DDX_Text(pDX, IDC_UP_OCCASION, m_Occasion);
	DDX_Control(pDX, IDC_UP_DATE, m_Date);
	DDX_Control(pDX, IDC_UP_TIME, m_Time);
}


BEGIN_MESSAGE_MAP(UpdateReservation, CDialogEx)
	ON_BN_CLICKED(IDOK, &UpdateReservation::OnBnClickedUpdate)
	ON_EN_CHANGE(IDC_EDIT_UP_PAX, &UpdateReservation::OnEnChangeEditUpPax)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_UP_DATE, &UpdateReservation::OnDtnDatetimechangeUpDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_UP_TIME, &UpdateReservation::OnDtnDatetimechangeUpTime)
	ON_EN_CHANGE(IDC_UP_OCCASION, &UpdateReservation::OnEnChangeUpOccasion)
END_MESSAGE_MAP()


// UpdateReservation message handlers


void UpdateReservation::OnBnClickedUpdate()
{
	DWORD dwResult = m_Date.GetTime(date);
	DWORD dwResult1 = m_Time.GetTime(time);
	UpdateData(TRUE);
	Guest guest;
	guest.m_strFilter.Format(_T("[BookingID] = %d"), bookingId);
	guest.Open();
	guest.Edit();
	guest.m_Pax = m_Pax;
	guest.m_Date = date;
	guest.m_Time = time;
	guest.m_Occasion = m_Occasion;
	guest.Update();
	guest.Close();

	CDialogEx::OnOK();
}


void UpdateReservation::OnEnChangeEditUpPax()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void UpdateReservation::OnDtnDatetimechangeUpDate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	SYSTEMTIME st;
	GetSystemTime(&st);
	CTime t = pDTChange->st;
	if (t.GetDay() - st.wDay < 0 || t.GetMonth() - st.wMonth < 0 || t.GetYear() - st.wYear < 0) {
		AfxMessageBox(_T("Invalid date"));
		VERIFY(m_Date.SetTime(&st));
	}
	else {
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	
	*pResult = 0;
}


void UpdateReservation::OnDtnDatetimechangeUpTime(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	*pResult = 0;
}


void UpdateReservation::OnEnChangeUpOccasion()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}
