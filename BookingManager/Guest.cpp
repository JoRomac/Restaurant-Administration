// Guest.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "Guest.h"


// Guest
IMPLEMENT_DYNAMIC(Guest, CRecordset)

Guest::Guest(CDatabase* pdb)
	: CRecordset(pdb)
{	
	m_Id = 0;
	m_Name = L"";
	m_Surname = L"";
	m_Pax = L"";
	m_Time;
	m_Date;
	m_Occasion = L"";
	m_Contact = L"";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
CString Guest::GetDefaultConnect()
{
	return _T("ODBC;DSN=RestaurantDb");
}

CString Guest::GetDefaultSQL()
{
	return _T("[Guest]");
}

void Guest::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[BookingID]"), m_Id);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Surname]"), m_Surname);
	RFX_Text(pFX, _T("[NumOfGuests]"), m_Pax);
	RFX_Date(pFX, _T("[Time]"), m_Time);
	RFX_Date(pFX, _T("[Dmy]"), m_Date);
	RFX_Text(pFX, _T("[Occasion]"), m_Occasion);
	RFX_Text(pFX, _T("[Contact]"), m_Contact);
}
/////////////////////////////////////////////////////////////////////////////
// Guest diagnostics


#ifdef _DEBUG
void Guest::AssertValid() const
{
	CRecordset::AssertValid();
}

void Guest::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

// Guest member functions
