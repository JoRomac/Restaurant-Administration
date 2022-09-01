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
	//  DDX_MonthCalCtrl(pDX, IDC_DISPLAY_BY_MONTH, m_displayByMonth);
	//  DDX_Control(pDX, IDC_DISPLAY_BY_MONTH, m_getResrvationsByDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_GetReservationsByDate);
}


BEGIN_MESSAGE_MAP(Bookings, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_RESERVATION, &Bookings::OnAddReservationClicked)
	ON_BN_CLICKED(IDC_DISPLAY_ALL, &Bookings::OnDisplayAllClicked)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Bookings::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_PRINT, &Bookings::OnBnClickedPrint)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Bookings::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_REMOVE_RESERVATION, &Bookings::OnBnClickedRemoveReservation)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &Bookings::OnBnClickedUpdateBtn)
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
	bookingList.SetExtendedStyle(bookingList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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
		bookingList.SetItemText(elementAtIndex, 5, guest.m_Date.Format(_T("%d:%m:%Y")));//"%m:%d:%Y"
		bookingList.SetItemText(elementAtIndex, 6, guest.m_Occasion);
		bookingList.SetItemText(elementAtIndex, 7, guest.m_Contact);
		guest.MoveNext();
	}
	guest.Close();
}



void Bookings::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	CTime t1 = pDTChange->st;
	//CTime t;
	//DWORD dwResult = m_GetReservationsByDate.GetTime(t);
	Guest guest;
	int day = t1.GetDay();
	int month = t1.GetMonth();
	int year = t1.GetYear();
	bookingList.DeleteAllItems();
	guest.Open();
	while (!guest.IsEOF()) {
		if (guest.m_Date.GetDay() - day == 0 && guest.m_Date.GetMonth() - month == 0 && guest.m_Date.GetYear() - year == 0) {
			CString id;
			id.Format(_T("%ld"), guest.m_Id);
			int elementAtIndex = bookingList.InsertItem(0, id);
			bookingList.SetItemText(elementAtIndex, 1, guest.m_Name);
			bookingList.SetItemText(elementAtIndex, 2, guest.m_Surname);
			bookingList.SetItemText(elementAtIndex, 3, guest.m_Pax);
			bookingList.SetItemText(elementAtIndex, 4, guest.m_Time.Format(_T("%H:%M")));//"%H:%M:%S"
			bookingList.SetItemText(elementAtIndex, 5, guest.m_Date.Format(_T("%d:%m:%Y")));//"%m:%d:%Y"
			bookingList.SetItemText(elementAtIndex, 6, guest.m_Occasion);
			bookingList.SetItemText(elementAtIndex, 7, guest.m_Contact);
			guest.MoveNext();
		}
		else {
			guest.MoveNext();
		}
	}
	guest.Close();

	*pResult = 0;
}



void Bookings::OnPrint(CDC* pDC)//
{

	int const a4size = 21;
	int paper_width = pDC->GetDeviceCaps(HORZRES);
	int paper_heigth = pDC->GetDeviceCaps(VERTRES);
	float start_point = paper_width / a4size;

	CSize cs = pDC->GetTextExtent(_T("A"));
	int row = 0;
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
		pDC->TextOut(start_point * 1, row, bookingList.GetItemText(r,1));
		pDC->TextOut(start_point * 5, row, bookingList.GetItemText(r,2));
		pDC->TextOut(start_point * 9, row, bookingList.GetItemText(r,3));
		pDC->TextOut(start_point * 13, row, bookingList.GetItemText(r,4));
		pDC->TextOut(start_point * 17, row, bookingList.GetItemText(r,6));
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

	  
	  //CPrintInfo Info;
	  //Info.m_rectDraw.SetRect(0, 0, dcPrinter.GetDeviceCaps(HORZRES), dcPrinter.GetDeviceCaps(VERTRES));

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
            // actually do some printing
			 dcPrinter.SetMapMode(MM_TEXT);
			 /*CFont* pOldFont;
			 CFont fnt;
			 fnt.CreatePointFont(100, _T("HM"), &dcPrinter);*/
			 CFont font;
			 LOGFONT lf;
			 memset(&lf, 0, sizeof(LOGFONT)); // zero out structure
			 lf.lfHeight = 12;                // request a 12-pixel-height font
			 _tcsncpy_s(lf.lfFaceName, LF_FACESIZE,
				 _T("Arial"), 7);           // request a face name "Arial"
			 VERIFY(font.CreateFontIndirect(&lf)); // create the font

			 // Do something with the font just created...
			 
			 CFont* def_font = dcPrinter.SelectObject(&font);
			 dcPrinter.TextOut(5, 5, _T("Hello"), 5);
			 dcPrinter.SelectObject(def_font);
			 //if (fnt.CreatePointFont(120, _T("HM"), &dcPrinter)) {
				// pOldFont = (CFont*)dcPrinter.SelectObject(&fnt);
			 //}
			 //else {
				// pOldFont = (CFont*)dcPrinter.SelectStockObject(DEVICE_DEFAULT_FONT);
			 //}
            //CGdiObject *pOldFont = dcPrinter.SelectStockObject(SYSTEM_FONT);
			//pOldFont = (CFont*)dcPrinter.SelectObject(&fnt);
			//CPoint pt(dcPrinter.GetDeviceCaps(HORZRES), dcPrinter.GetDeviceCaps(VERTRES));
			//dcPrinter.DPtoLP(&pt);
			
			//dcPrinter.TextOut(50, 50, _T("Hello World!"), 12);
			OnPrint(&dcPrinter);
            dcPrinter.EndPage();
            dcPrinter.EndDoc();
            dcPrinter.SelectObject(def_font);
         }
      }
   }
}

//void Bookings::Print()
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
//
//	CDC dc;
//	CPrintDialog* pPrntDialog(FALSE);
//	if (pPrntDialog == NULL)
//	{
//		CPrintDialog printDlg(FALSE);
//		if (printDlg.DoModal() != IDOK)         // Get printer settings from user
//			return;
//
//		dc.Attach(printDlg.GetPrinterDC());     // attach a printer DC
//	}
//	else
//		dc.Attach(pPrntDialog->GetPrinterDC()); // attach a printer DC
//	dc.m_bPrinting = TRUE;
//	//CString strTitle;
//	DOCINFO di;                                 // Initialise print doc details
//	memset(&di, 0, sizeof(DOCINFO));
//	di.cbSize = sizeof(DOCINFO);
//	//di.lpszDocName = strTitle.c_str();
//
//	BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job
//
//	CPrintInfo Info;
//	Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
//
//	OnBeginPrinting(&dc, &Info);                // Initialise printing
//	for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++)
//	{
//		dc.StartPage();                         // begin new page
//		Info.m_nCurPage = page;
//		OnPrint(&dc, &Info);                    // Print page
//		bPrintingOK = (dc.EndPage() > 0);       // end page
//	}
//	OnEndPrinting(&dc, &Info);                  // Clean up after printing
//
//	if (bPrintingOK)
//		dc.EndDoc();                            // end a print job
//	else
//		dc.AbortDoc();                          // abort job.
//
//	dc.Detach();                                // detach the printer DC
//}



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
	CString id = bookingList.GetItemText(reservationIndex, 0);
	Guest guest;
	guest.m_strFilter.Format(_T("[BookingID] = %d"), _tstoi(id));
	guest.Open();
	guest.Delete();
	bookingList.DeleteItem(reservationIndex);
	guest.Close();
}


void Bookings::OnBnClickedUpdateBtn()
{
	int reservationIndex = bookingList.GetNextItem(-1, LVNI_SELECTED);
	CString id = bookingList.GetItemText(reservationIndex, 0);
	Guest guest;
	guest.m_strFilter.Format(_T("[BookingID] = %d"), _tstoi(id));
	guest.Open();
	UpdateReservation update(_tstoi(id), guest.m_Time, guest.m_Date, guest.m_Pax, guest.m_Occasion);
	update.DoModal();
		//IspisRezervacija();
}
