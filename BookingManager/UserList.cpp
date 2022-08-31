// UserList.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "UserList.h"
#include "afxdialogex.h"
#include "CUser.h"
#include "NewUser.h"

// UserList dialog

IMPLEMENT_DYNAMIC(UserList, CDialogEx)

UserList::UserList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_DIALOG, pParent)
{

}

UserList::~UserList()
{
}

void UserList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_LIST, usersList);
}


BEGIN_MESSAGE_MAP(UserList, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_USER_LIST, &UserList::OnLvnItemchangedUserList)
	ON_BN_CLICKED(IDC_REMOVE_USER_BTN, &UserList::OnRemoveUserClicked)
	ON_BN_CLICKED(IDC_ADD_USER_BTN, &UserList::OnAddUserCliked)
END_MESSAGE_MAP()


// UserList message handlers


BOOL UserList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	usersList.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 30);
	usersList.InsertColumn(1, _T("UserName"), LVCFMT_LEFT, 130);
	usersList.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 150);
	usersList.InsertColumn(3, _T("Surname"), LVCFMT_LEFT, 170);
	usersList.InsertColumn(4, _T("Mobile"), LVCFMT_LEFT, 140);
	usersList.InsertColumn(5, _T("Email"), LVCFMT_LEFT, 140);
	usersList.SetExtendedStyle(usersList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	DisplayUsers();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void UserList::DisplayUsers() 
{
	usersList.DeleteAllItems();
	CUser user;
	user.Open();
	while (!user.IsEOF()) {
		CString id;
		id.Format(_T("%ld"), user.m_EmployeeID);
		int nIndex = usersList.InsertItem(0, id);
		usersList.SetItemText(nIndex, 1, user.m_Username);
		usersList.SetItemText(nIndex, 2, user.m_Name);
		usersList.SetItemText(nIndex, 3, user.m_Surname);
		usersList.SetItemText(nIndex, 4, user.m_Mobile);
		usersList.SetItemText(nIndex, 5, user.m_Email);;
		user.MoveNext();
	}
	user.Close();
}

//void CZaposlenici::OnBnClickedButtonZaposlenikIzbrisi()
//{
//
//	int x = zaposlenici.GetNextItem(-1, LVNI_SELECTED);
//	CString t = zaposlenici.GetItemText(x, 0);
//	CZaposlenik zaposlenik;
//	zaposlenik.m_strFilter.Format(_T("[ZaposlenikID] = %d"), _tstoi(t));
//	zaposlenik.Open();
//	zaposlenik.Delete();
//	zaposlenici.DeleteItem(x);
//	zaposlenik.Close();
//}

void UserList::OnLvnItemchangedUserList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool isSelected = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_REMOVE_USER_BTN)->EnableWindow(isSelected);
	*pResult = 0;
}


void UserList::OnRemoveUserClicked()
{
	int userIndex = usersList.GetNextItem(-1, LVNI_SELECTED);
	CString id = usersList.GetItemText(userIndex, 0);
	CUser user;
	user.m_strFilter.Format(_T("[EmployeeID] = %d"), _tstoi(id));
	user.Open();
	user.Delete();
	usersList.DeleteItem(userIndex);
	user.Close();
}


void UserList::OnAddUserCliked()
{
	NewUser newUser;
	newUser.DoModal();
}
