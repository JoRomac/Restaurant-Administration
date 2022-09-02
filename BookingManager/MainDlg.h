#pragma once


// MainDlg dialog

class MainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainDlg) 

public:
	MainDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainDlg();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBookingClicked();
	afx_msg void OnUsersClicked();
	afx_msg void OnBnClickedSignout();
};
