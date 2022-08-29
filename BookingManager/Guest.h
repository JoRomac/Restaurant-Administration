#pragma once

// Guest command target

class Guest : public CRecordset
{
public:
	Guest(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Guest)
	long	m_Id;
	CStringW	m_Name;
	CStringW	m_Surname;
	CStringW	m_Pax;
	CTime	m_Time;
	CTime	m_Date;
	CStringW	m_Occasion;
	CStringW	m_Contact;

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


