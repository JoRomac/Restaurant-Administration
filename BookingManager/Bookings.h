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
	
};
