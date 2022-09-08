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
	, m_Password()
	, m_Name()
	, m_Lastname()
	, m_Mobile()
	, m_Email()
	, m_Username()
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


BOOL NewUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
