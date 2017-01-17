// DlgDatabaseEditCloth.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NorvelEdit.h"
#include "DlgDatabaseEditCloth.h"
#include "afxdialogex.h"


// CDlgDatabaseEditCloth �Ի���

IMPLEMENT_DYNAMIC(CDlgDatabaseEditCloth, CDialogEx)

CDlgDatabaseEditCloth::CDlgDatabaseEditCloth(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDatabaseEditCloth::IDD, pParent)
{

}

CDlgDatabaseEditCloth::~CDlgDatabaseEditCloth()
{
}

void CDlgDatabaseEditCloth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLOTH, m_lsCloth);
	DDX_Control(pDX, IDC_LIST_THINGS, m_lsThings);
	DDX_Control(pDX, IDC_EDIT_CLOTH, m_edtCloth);
	DDX_Control(pDX, IDC_EDIT_CLOTH_CONTENT, m_edtContentCloth);
	DDX_Control(pDX, IDC_EDIT_THINGS, m_edtThings);
	DDX_Control(pDX, IDC_EDIT_THINGS_CONTENT, m_edtContentThings);
}


BEGIN_MESSAGE_MAP(CDlgDatabaseEditCloth, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLOTH, &CDlgDatabaseEditCloth::OnBnClickedButtonCloth)
	ON_BN_CLICKED(IDC_BUTTON_THINGS, &CDlgDatabaseEditCloth::OnBnClickedButtonThings)
END_MESSAGE_MAP()


// CDlgDatabaseEditCloth ��Ϣ�������


void CDlgDatabaseEditCloth::OnBnClickedButtonCloth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strdata;
	m_edtCloth.GetWindowText(strdata);
	if(strdata.IsEmpty())
	{
		AfxMessageBox(_T("���ݲ���Ϊ�գ�"));
		return;
	}
	if(m_tableCloth.Find(_T("cloth"),strdata).size() != 0)
	{
		AfxMessageBox(_T("�����Ѿ����ڣ�"));
		return;
	}
	CString strContent;
	m_edtContentCloth.GetWindowText(strContent);
	if(!m_tableCloth.Insert(strdata,strContent))
	{
		AfxMessageBox(_T("��������ʧ�ܣ�"));
		return;
	}
	m_lsCloth.AddString(strdata);
	m_edtContentCloth.SetWindowTextW(NULL);
}


void CDlgDatabaseEditCloth::OnBnClickedButtonThings()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strdata;
	m_edtThings.GetWindowText(strdata);
	if(strdata.IsEmpty())
	{
		AfxMessageBox(_T("���ݲ���Ϊ�գ�"));
		return;
	}
	if(m_tableThing.Find(_T("things"),strdata).size() != 0)
	{
		AfxMessageBox(_T("�����Ѿ����ڣ�"));
		return;
	}
	CString strContent;
	m_edtContentThings.GetWindowText(strContent);
	if(!m_tableThing.Insert(strdata,strContent))
	{
		AfxMessageBox(_T("��������ʧ�ܣ�"));
		return;
	}
	m_lsThings.AddString(strdata);
	m_edtContentThings.Clear();
}


BOOL CDlgDatabaseEditCloth::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	vectorCloth vtheme = m_tableCloth.GetData();
	for(int i = 0;i<vtheme.size();i++)
	{
		m_lsCloth.AddString(vtheme[i].strName);
	}

	VectorThings vdecade = m_tableThing.GetData();
	for(int i = 0;i<vdecade.size();i++)
	{
		m_lsThings.AddString(vdecade[i].strName);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
