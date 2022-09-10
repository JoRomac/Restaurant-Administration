// CUser.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "CUser.h"


// CUser
IMPLEMENT_DYNAMIC(CUser, CRecordset)

CUser::CUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 7;
	m_nDefaultType = dynaset;
}

CString CUser::GetDefaultConnect()
{
	return _T("ODBC;DSN=RestaurantDb");
}

CString CUser::GetDefaultSQL()
{
	return _T("[Employee]");
}

void CUser::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[EmployeeID]"), m_EmployeeID);
	RFX_Text(pFX, _T("[Username]"), m_Username);
	RFX_Text(pFX, _T("[Password]"), m_Password);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Surname]"), m_Surname);
	RFX_Text(pFX, _T("[Mobile]"), m_Mobile);
	RFX_Text(pFX, _T("[Email]"), m_Email);
}
/////////////////////////////////////////////////////////////////////////////
// CUser diagnostics

#ifdef _DEBUG
void CUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
