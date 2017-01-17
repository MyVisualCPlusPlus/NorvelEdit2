// DlgMap.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NorvelEdit.h"
#include "DlgMap.h"
#include "afxdialogex.h"


// CDlgMap �Ի���

IMPLEMENT_DYNAMIC(CDlgMap, CDialogEx)

CDlgMap::CDlgMap(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMap::IDD, pParent)
	, m_nDrawType(0)
{

}

CDlgMap::~CDlgMap()
{
}

void CDlgMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_MOUSE_EVENT, m_MapCanvas);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Radio(pDX, IDC_RADIO1, m_nDrawType);
	DDX_Control(pDX, IDC_CHECK_DISP_CON, m_chkCon);
	DDX_Control(pDX, IDC_CHECK_DISP_LINE, m_chkLine);
}


BEGIN_MESSAGE_MAP(CDlgMap, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RADIO1, &CDlgMap::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgMap::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK_DISP_CON, &CDlgMap::OnBnClickedCheckDispCon)
	ON_BN_CLICKED(IDC_CHECK_DISP_LINE, &CDlgMap::OnBnClickedCheckDispLine)
	ON_BN_CLICKED(IDOK, &CDlgMap::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMap ��Ϣ�������


void CDlgMap::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	SetCtrlPosition(cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CDlgMap::SetCtrlPosition( int cx, int cy )
{
	if(::IsWindow(m_MapCanvas.GetSafeHwnd()))
	{
		CRect mapRc;
		m_MapCanvas.GetWindowRect(mapRc);

		ScreenToClient(mapRc);

		m_MapCanvas.MoveWindow(mapRc.left,mapRc.top,cx-130,cy-50);
		Invalidate();
	}

	if(::IsWindow(m_btnOK.GetSafeHwnd()))
	{
		CRect mapRc;
		m_btnOK.GetWindowRect(mapRc);

		m_btnOK.MoveWindow(cx - 200,cy-30,mapRc.Width(),mapRc.Height());
		Invalidate();
	}

	if(::IsWindow(m_btnCancel.GetSafeHwnd()))
	{
		CRect mapRc;
		m_btnCancel.GetWindowRect(mapRc);

		ScreenToClient(mapRc);

		m_btnCancel.MoveWindow(cx - 100,cy-30,mapRc.Width(),mapRc.Height());
		Invalidate();
	}
}

BOOL CDlgMap::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	GetClientRect(rc);

	m_MapCanvas.CreateEx(WS_EX_CLIENTEDGE,
				NULL, _T("Hi"),
				WS_CHILD  | WS_VISIBLE|WS_HSCROLL |WS_VSCROLL|WS_OVERLAPPED,
				130, 5, 400, 800, m_hWnd, (HMENU)1234);

	SetCtrlPosition(rc.right,rc.bottom);
	m_MapCanvas.SetDrawType(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgMap::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MapCanvas.SetDrawType(0);
	m_MapCanvas.Invalidate();
}


void CDlgMap::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgMap::OnBnClickedCheckDispCon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	m_MapCanvas.SetDispCoor(m_chkCon.GetCheck());
	m_MapCanvas.Invalidate();
}


void CDlgMap::OnBnClickedCheckDispLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MapCanvas.SetDispGrid(m_chkLine.GetCheck());
	m_MapCanvas.Invalidate();
}


void CDlgMap::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
