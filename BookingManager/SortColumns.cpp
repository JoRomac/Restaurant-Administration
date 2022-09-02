#include "pch.h"
#include "SortColumns.h"


namespace sortbytime {
	
		SORTPARAM::SORTPARAM(HWND hWnd, int column, bool order, bool time)
		:m_hWnd(hWnd)
		, m_column(column)
		, m_order(order)
		, m_time(time)
		{}
	int CALLBACK Sort(LPARAM lParam1, LPARAM lParam2, LPARAM lSortParam)
	{
		SORTPARAM& sp = *(SORTPARAM*)lSortParam;

		TCHAR first[256] = _T(""), second[256] = _T("");
		ListView_GetItemText(sp.m_hWnd, lParam1, sp.m_column, first, sizeof(first));
		ListView_GetItemText(sp.m_hWnd, lParam2, sp.m_column, second, sizeof(second));
		int f = _ttoi(first);
		int s = _ttoi(second);
		if (f != 0 && sp.m_time == false) {
			return sp.m_order ? f - s : -(f - s);
		}
		if (sp.m_time == true) {
			CTime t1, t2;
			t1 = Time(first);
			t2 = Time(second);
			return sp.m_order ? t1 < t2 : t1 > t2;
		}
		return sp.m_order ? _tcscmp(first, second) : _tcscmp(second, first);

	}
	CTime Time(CString datum) {
		COleDateTime t;
		CTime t1;
		SYSTEMTIME st;
		t.ParseDateTime(datum);
		if (t.GetAsSystemTime(st))
			t1 = CTime(st);
		return t1;
	}
}