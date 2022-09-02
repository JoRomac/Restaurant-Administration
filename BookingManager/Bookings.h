#pragma once


// Bookings dialog

class Bookings : public CDialogEx
{
	DECLARE_DYNAMIC(Bookings)

public:
	Bookings(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Bookings();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl bookingList;
	virtual void OnPrint(CDC* pDC);
	afx_msg void OnAddReservationClicked();
	afx_msg void OnDisplayAllClicked();
	CDateTimeCtrl m_GetReservationsByDate;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedPrint();
	void Print();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedRemoveReservation();
	afx_msg void OnBnClickedUpdateBtn();
	int bookingId;
	CString bookingDate;
	void DisplayReservations(int d, int m, int y);

	bool SortByColumn(int columnIndex, bool order);
	bool order;
	int column;
	afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);

	int totalGuestNum;
	CString totalGuests;
};
