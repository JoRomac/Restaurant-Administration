#pragma once


namespace sortbytime {
	struct SORTPARAM
	{
		SORTPARAM(HWND hWnd, int column, bool order, bool time);
		HWND m_hWnd;
		int  m_column;
		bool m_order;
		bool m_time;
	};
	int CALLBACK Sort(LPARAM lParam1, LPARAM lParam2, LPARAM lSortParam);
};


