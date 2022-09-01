#pragma once


// UpdateReservation dialog

class UpdateReservation : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateReservation)

public:
	UpdateReservation(int bookingId, CTime t, CTime d, CString pax, CString occasion, CWnd* pParent = nullptr);   // standard constructor
	virtual ~UpdateReservation();
	int bookingId;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_RES_DLG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Pax;
//	COleDateTime m_Date;
//	COleDateTime m_Time;
	CString m_Occasion;
	afx_msg void OnBnClickedUpdate();
	CDateTimeCtrl m_Date;
	CDateTimeCtrl m_Time;
	CTime time, date;
	CString pax, occasion;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditUpPax();
	afx_msg void OnDtnDatetimechangeUpDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeUpTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeUpOccasion();
};
