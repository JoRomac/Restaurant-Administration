// NewReservation.cpp : implementation file
//

#include "pch.h"
#include "BookingManager.h"
#include "NewReservation.h"
#include "afxdialogex.h"


// NewReservation dialog

IMPLEMENT_DYNAMIC(NewReservation, CDialogEx)

NewReservation::NewReservation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_RESERVATION, pParent)
{

}

NewReservation::~NewReservation()
{
}

void NewReservation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewReservation, CDialogEx)
END_MESSAGE_MAP()


// NewReservation message handlers
