// Bookings.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "Bookings.h"
#include "afxdialogex.h"
#include "NewReservation.h"
#include "Guest.h"
#include "afxwin.h"
#include "UpdateReservation.h"
#include "resource.h"
#include "SortColumns.h"
// Bookings dialog

IMPLEMENT_DYNAMIC(Bookings, CDialogEx)

Bookings::Bookings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKING_DIALOG, pParent)
	, bookingDate()
	, totalGuests()
{

}

Bookings::~Bookings()
{
}

void Bookings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, bookingList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_GetReservationsByDate);
	DDX_Text(pDX, IDC_STATIC_BOOKINGDATE, bookingDate);
	DDX_Text(pDX, IDC_STATIC_NUMOFGUESTS, totalGuests);
}


BEGIN_MESSAGE_MAP(Bookings, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_RESERVATION, &Bookings::OnAddReservationClicked)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Bookings::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_PRINT, &Bookings::OnBnClickedPrint)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Bookings::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_REMOVE_RESERVATION, &Bookings::OnBnClickedRemoveReservation)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &Bookings::OnBnClickedUpdateBtn)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &Bookings::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// Bookings message handlers


BOOL Bookings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	bookingList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 130);
	bookingList.InsertColumn(1, _T("Surname"), LVCFMT_LEFT, 170);
	bookingList.InsertColumn(2, _T("Pax"), LVCFMT_LEFT, 50);
	bookingList.InsertColumn(3, _T("Time"), LVCFMT_LEFT, 100);
	bookingList.InsertColumn(4, _T("Date"), LVCFMT_LEFT, 100);
	bookingList.InsertColumn(5, _T("Occasion"), LVCFMT_LEFT, 120);
	bookingList.InsertColumn(6, _T("Contact"), LVCFMT_LEFT, 150);
	bookingList.SetExtendedStyle(bookingList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	bookingList.ModifyStyle(NULL, LVS_SINGLESEL, 0);
	SYSTEMTIME st;
	GetSystemTime(&st);
	int day = st.wDay;
	int month = st.wMonth;
	int year = st.wYear;
	DisplayReservations(day, month, year);
	bookingDate = _T("TODAY'S");
	SetDlgItemText(IDC_STATIC_BOOKINGDATE, bookingDate);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void Bookings::OnAddReservationClicked()
{
	NewReservation reservation;
	
	if (reservation.DoModal() == IDOK) {
		DisplayReservations(reservation.d.GetDay(), reservation.d.GetMonth(), reservation.d.GetYear());
	}
}



void Bookings::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	CTime t1 = pDTChange->st;
	SYSTEMTIME st;
	GetSystemTime(&st);
	int day = t1.GetDay();
	int month = t1.GetMonth();
	int year = t1.GetYear();
	DisplayReservations(day, month, year);
	if (day - st.wDay == 0 && month - st.wMonth == 0 && year - st.wYear == 0) {
		bookingDate = _T("TODAY'S");
	}
	else {
		bookingDate = t1.Format(_T("%d.%m.%y"));
	}
	SetDlgItemText(IDC_STATIC_BOOKINGDATE, bookingDate);
	*pResult = 0;
}

void Bookings::DisplayReservations(int d, int m, int y) {
	Guest guest;
	CString id;
	bookingList.DeleteAllItems();
	totalGuestNum = 0;
	guest.Open();
	while (!guest.IsEOF()) {
		if (guest.m_Date.GetDay() - d == 0 && guest.m_Date.GetMonth() - m == 0 && guest.m_Date.GetYear() - y == 0) {
			int elementAtIndex = bookingList.InsertItem(0, guest.m_Name);
			bookingList.SetItemData(elementAtIndex, guest.m_Id);
			bookingList.SetItemText(elementAtIndex, 1, guest.m_Surname);
			bookingList.SetItemText(elementAtIndex, 2, guest.m_Pax);
			bookingList.SetItemText(elementAtIndex, 3, guest.m_Time.Format(_T("%H:%M")));
			bookingList.SetItemText(elementAtIndex, 4, guest.m_Date.Format(_T("%d.%m.%Y")));
			bookingList.SetItemText(elementAtIndex, 5, guest.m_Occasion);
			bookingList.SetItemText(elementAtIndex, 6, guest.m_Contact);
			totalGuestNum += _tstoi(guest.m_Pax);
		}
		guest.MoveNext();
	}
	guest.Close();
	totalGuests.Format(_T("%d"), totalGuestNum);
	SetDlgItemText(IDC_STATIC_NUMOFGUESTS, totalGuests);
	
}
bool Bookings::SortByColumn(int columnIndex, bool order)
{
	bool time = columnIndex == 3 ? false : true;
	sortbytime::SORTPARAM sortparam(bookingList, columnIndex, order, time);
	ListView_SortItemsEx(bookingList, sortbytime::Sort, &sortparam);
	return true;
}


void Bookings::OnPrint(CDC* pDC, CPrintInfo* info)
{
	int const a4size = 21;
	int paper_width = pDC->GetDeviceCaps(HORZRES);
	int paper_heigth = pDC->GetDeviceCaps(VERTRES);
	float start_point = paper_width / a4size;

	CSize cs = pDC->GetTextExtent(_T("A"));
	int row = 0;
	pDC->TextOut(start_point, row, bookingList.GetItemText(0, 4) + _T(" RESERVATIONS:"));
	row += cs.cy*1.5;
	pDC->TextOut(start_point * 1, row, _T("Name"));
	pDC->TextOut(start_point * 5, row, _T("Surname"));
	pDC->TextOut(start_point * 9, row, _T("Pax"));
	pDC->TextOut(start_point * 13, row, _T("Time"));
	pDC->TextOut(start_point * 17, row, _T("Occasion"));
	
	row += cs.cy;
	pDC->MoveTo(start_point, row);
	pDC->LineTo(paper_width/1.1, row);

	for (int r = 0; r <= bookingList.GetItemCount(); ++r) {
		row += cs.cy;
		pDC->TextOut(start_point * 1, row, bookingList.GetItemText(r,0));
		pDC->TextOut(start_point * 5, row, bookingList.GetItemText(r,1));
		pDC->TextOut(start_point * 9, row, bookingList.GetItemText(r,2));
		pDC->TextOut(start_point * 13, row, bookingList.GetItemText(r,3));
		pDC->TextOut(start_point * 17, row, bookingList.GetItemText(r,5));
	}
}

void Bookings::OnBnClickedPrint()
{
	Print();
}
void Bookings::Print()
{
// get the default printer
   CPrintDialog dlg(FALSE);
   dlg.GetDefaults();


   // is a default printer set up?
   HDC hdcPrinter = dlg.GetPrinterDC();
   if (hdcPrinter == NULL)
   {
      MessageBox(_T("Buy a printer!"));
   }
   else
   {
      // create a CDC and attach it to the default printer
      CDC dcPrinter;
      dcPrinter.Attach(hdcPrinter);

      // call StartDoc() to begin printing
      DOCINFO docinfo;
      memset(&docinfo, 0, sizeof(docinfo));
      docinfo.cbSize = sizeof(docinfo);
      docinfo.lpszDocName = _T("CDC::StartDoc() Code Fragment");

	  CPrintInfo Info;

      if (dcPrinter.StartDoc(&docinfo) < 0)
      {
         MessageBox(_T("Printer wouldn't initialize"));
      }
      else
      {
			// start a page
			if (dcPrinter.StartPage() < 0)
			{
				MessageBox(_T("Could not start page"));
				dcPrinter.AbortDoc();
			}
			else
			{
			OnPrint(&dcPrinter, &Info);
			dcPrinter.EndPage();
			dcPrinter.EndDoc();
			}
		  
      }
   }
}



void Bookings::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool isSelected = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_REMOVE_RESERVATION)->EnableWindow(isSelected);
	GetDlgItem(IDC_UPDATE_BTN)->EnableWindow(isSelected);
	*pResult = 0;
}


void Bookings::OnBnClickedRemoveReservation()
{
	int reservationIndex = bookingList.GetNextItem(-1, LVNI_SELECTED);
	int id = bookingList.GetItemData(reservationIndex);
	Guest guest;
	guest.m_strFilter.Format(_T("[BookingID] = %d"), id);
	guest.Open();
	guest.Delete();
	bookingList.DeleteItem(reservationIndex);
	guest.Close();
}


void Bookings::OnBnClickedUpdateBtn()
{
	int reservationIndex = bookingList.GetNextItem(-1, LVNI_SELECTED);
	int id = bookingList.GetItemData(reservationIndex);
	Guest guest;
	guest.m_strFilter.Format(_T("[BookingID] = %d"), id);
	guest.Open();
	UpdateReservation update(id, guest.m_Time, guest.m_Date, guest.m_Pax, guest.m_Occasion);
	if(update.DoModal() == IDOK)
		DisplayReservations(guest.m_Date.GetDay(), guest.m_Date.GetMonth(), guest.m_Date.GetYear());
}


void Bookings::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	order = pNMLV->iSubItem == column ? !order : false;
	column = pNMLV->iSubItem;
	SortByColumn(column, order);
	*pResult = 0;
}
