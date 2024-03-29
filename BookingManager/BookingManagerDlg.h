
// BookingManagerDlg.h : header file
//

#pragma once


// CBookingManagerDlg dialog
class CBookingManagerDlg : public CDialogEx
{
// Construction
public:
	CBookingManagerDlg(CWnd* pParent = nullptr);	// standard constructor
	 
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKINGMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_User;
	CString m_Password;
	afx_msg void OnLoginClicked();
};
