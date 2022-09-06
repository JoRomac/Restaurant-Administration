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
		if (sp.m_order)
			return _tcscmp(first, second);
		else
			return _tcscmp(second, first);
	}
}