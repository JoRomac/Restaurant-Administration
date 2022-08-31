#pragma once

// CUser command target

class CUser : public CRecordset
{
public:
	CUser(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUser)


	long	m_EmployeeID;
	CString	m_Username;
	CString	m_Password;
	CString	m_Name;
	CString	m_Surname;
	CString	m_Mobile;
	CString	m_Email;

	// Overrides
		// Wizard generated virtual function overrides
public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};


