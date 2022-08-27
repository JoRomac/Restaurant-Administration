#pragma once


// NewReservation dialog

class NewReservation : public CDialogEx
{
	DECLARE_DYNAMIC(NewReservation)

public:
	NewReservation(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewReservation();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_RESERVATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
