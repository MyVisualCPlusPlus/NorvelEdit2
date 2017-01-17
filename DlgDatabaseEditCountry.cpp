// DlgDatabaseEditCountry.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NorvelEdit.h"
#include "DlgDatabaseEditCountry.h"
#include "afxdialogex.h"


// CDlgDatabaseEditCountry �Ի���

IMPLEMENT_DYNAMIC(CDlgDatabaseEditCountry, CDialogEx)

CDlgDatabaseEditCountry::CDlgDatabaseEditCountry(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDatabaseEditCountry::IDD, pParent)
	, m_nCountryType(0)
{

}

CDlgDatabaseEditCountry::~CDlgDatabaseEditCountry()
{
}

void CDlgDatabaseEditCountry::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COUNTRY, m_lsCountry);
	DDX_Control(pDX, IDC_LIST_RELIGIOUS, m_lsReli);
	DDX_Control(pDX, IDC_EDIT_COUNTRY, m_edtCountry);
	DDX_Control(pDX, IDC_EDIT_COUNTRY_CONTENT, m_edtContentCountry);
	DDX_Control(pDX, IDC_EDIT_RELIGIOUS, m_edtReli);
	DDX_Control(pDX, IDC_EDIT_RELIGIOUS_CONTENT, m_ContentReli);
	DDX_Radio(pDX, IDC_RADIO1, m_nCountryType);
	DDV_MinMaxInt(pDX, m_nCountryType, 1, 2);
}


BEGIN_MESSAGE_MAP(CDlgDatabaseEditCountry, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COUNTRY, &CDlgDatabaseEditCountry::OnBnClickedButtonCountry)
	ON_BN_CLICKED(IDC_BUTTON_RELIGIOUS, &CDlgDatabaseEditCountry::OnBnClickedButtonReligious)
END_MESSAGE_MAP()


// CDlgDatabaseEditCountry ��Ϣ�������


void CDlgDatabaseEditCountry::OnBnClickedButtonCountry()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strdata;
	m_edtCountry.GetWindowText(strdata);
	if(strdata.IsEmpty())
	{
		AfxMessageBox(_T("���ݲ���Ϊ�գ�"));
		return;
	}
	if(m_tableCountry.Find(_T("country"),strdata).size() != 0)
	{
		AfxMessageBox(_T("�����Ѿ����ڣ�"));
		return;
	}
	CString strContent;
	m_edtContentCountry.GetWindowText(strContent);
	if(!m_tableCountry.Insert(strdata,strContent,m_nCountryType))
		AfxMessageBox(_T("��������ʧ�ܣ�"));
	m_lsCountry.AddString(strdata);
}


void CDlgDatabaseEditCountry::OnBnClickedButtonReligious()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strdata;
	m_edtReli.GetWindowText(strdata);
	if(strdata.IsEmpty())
	{
		AfxMessageBox(_T("���ݲ���Ϊ�գ�"));
		return;
	}
	if(m_tableReli.Find(_T("religion"),strdata).size() != 0)
	{
		AfxMessageBox(_T("�����Ѿ����ڣ�"));
		return;
	}
	CString strContent;
	m_ContentReli.GetWindowText(strContent);
	if(!m_tableReli.Insert(strdata,strContent))
		AfxMessageBox(_T("��������ʧ�ܣ�"));
	m_lsReli.AddString(strdata);
}


BOOL CDlgDatabaseEditCountry::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	vectorCountry vtheme = m_tableCountry.GetData();
	for(int i = 0;i<vtheme.size();i++)
	{
		m_lsCountry.AddString(vtheme[i].strName);
	}

	vectorReligion vdecade = m_tableReli.GetData();
	for(int i = 0;i<vdecade.size();i++)
	{
		m_lsReli.AddString(vdecade[i].strName);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
