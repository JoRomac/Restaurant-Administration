#pragma once


// UserList dialog

class UserList : public CDialogEx
{
	DECLARE_DYNAMIC(UserList)

public:
	UserList(CWnd* pParent = nullptr);   // standard constructor
	virtual ~UserList();
	void DisplayUsers();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl usersList;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemoveUserClicked();
	afx_msg void OnAddUserCliked();
};
