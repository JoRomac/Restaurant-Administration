#pragma once


// NewUser dialog

class NewUser : public CDialogEx
{
	DECLARE_DYNAMIC(NewUser)

public:
	NewUser(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewUser();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CEdit m_Username;
	CString m_Password;
	CString m_Name;
	CString m_Lastname;
	CString m_Mobile;
	CString m_Email;
	afx_msg void OnBnClickedOk();
	CString m_Username;
	virtual BOOL OnInitDialog();
};
