// NewUser.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "NewUser.h"
#include "afxdialogex.h"
#include "CUser.h"

// NewUser dialog

IMPLEMENT_DYNAMIC(NewUser, CDialogEx)

NewUser::NewUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_USER, pParent)
	, m_Password(_T(""))
	, m_Name(_T(""))
	, m_Lastname(_T(""))
	, m_Mobile(_T(""))
	, m_Email(_T(""))
	, m_Username(_T(""))
{

}

NewUser::~NewUser()
{
}

void NewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_LASTNAME, m_Lastname);
	DDX_Text(pDX, IDC_EDIT_MOBILE, m_Mobile);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_Email);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_Username);
}


BEGIN_MESSAGE_MAP(NewUser, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewUser::OnBnClickedOk)
END_MESSAGE_MAP()


// NewUser message handlers


void NewUser::OnBnClickedOk()
{
	UpdateData(TRUE);
	CUser user;
	user.Open();
	user.AddNew();
	user.m_Username = m_Username;
	user.m_Password = m_Password;
	user.m_Name = m_Name;
	user.m_Surname = m_Lastname;
	user.m_Mobile = m_Mobile;
	user.m_Email = m_Email;
	if (!user.Update()) {
		AfxMessageBox(_T("Unsuccessful attempt"));
	}
	user.Close();
	CDialogEx::OnOK();
}
