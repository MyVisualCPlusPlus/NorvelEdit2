// DlgDatabaseEditTechnology.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NorvelEdit.h"
#include "DlgDatabaseEditTechnology.h"
#include "afxdialogex.h"


// CDlgDatabaseEditTechnology �Ի���

IMPLEMENT_DYNAMIC(CDlgDatabaseEditTechnology, CDialogEx)

CDlgDatabaseEditTechnology::CDlgDatabaseEditTechnology(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDatabaseEditTechnology::IDD, pParent)
	, m_nType(0)
{

}

CDlgDatabaseEditTechnology::~CDlgDatabaseEditTechnology()
{
}

void CDlgDatabaseEditTechnology::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TECHNOLOGY, m_lsTechnology);
	DDX_Control(pDX, IDC_LIST_PROFESSION, m_lsProfession);
	DDX_Control(pDX, IDC_EDIT_TECHNOLOGY, m_edtTech);
	DDX_Control(pDX, IDC_EDIT_TECHNOLOGY_CONTENT, m_edtContentTech);
	DDX_Control(pDX, IDC_EDIT_PROFESSION, m_edtProfession);
	DDX_Control(pDX, IDC_EDIT_PROFESSION_CONTENT, m_edtContentProfession);
	DDX_Radio(pDX, IDC_RADIO1, m_nType);
}


BEGIN_MESSAGE_MAP(CDlgDatabaseEditTechnology, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TECHNOLOGY, &CDlgDatabaseEditTechnology::OnBnClickedButtonTechnology)
	ON_BN_CLICKED(IDC_BUTTON_PROFESSION, &CDlgDatabaseEditTechnology::OnBnClickedButtonProfession)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgDatabaseEditTechnology::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgDatabaseEditTechnology::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CDlgDatabaseEditTechnology ��Ϣ�������


void CDlgDatabaseEditTechnology::OnBnClickedButtonTechnology()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strdata;
	m_edtTech.GetWindowText(strdata);
	if(strdata.IsEmpty())
	{
		AfxMessageBox(_T("���ݲ���Ϊ�գ�"));
		return;
	}
	if(m_tableTech.Find(_T("technology"),strdata).size() != 0)
	{
		AfxMessageBox(_T("�����Ѿ����ڣ�"));
		return;
	}
	CString strContent;
	m_edtContentTech.GetWindowText(strContent);
	if(!m_tableTech.Insert(strdata,strContent))
	{
		AfxMessageBox(_T("��������ʧ�ܣ�"));
		return;
	}
	m_lsTechnology.AddString(strdata);
	m_edtTech.SetWindowTextW(NULL);
	m_edtContentTech.SetWindowTextW(NULL);
}


void CDlgDatabaseEditTechnology::OnBnClickedButtonProfession()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strdata;
	m_edtProfession.GetWindowText(strdata);
	if(strdata.IsEmpty())
	{
		AfxMessageBox(_T("���ݲ���Ϊ�գ�"));
		return;
	}
	if(m_tableProf.Find(_T("profession"),strdata).size() != 0)
	{
		AfxMessageBox(_T("�����Ѿ����ڣ�"));
		return;
	}
	CString strContent;
	m_edtContentProfession.GetWindowText(strContent);
	if(!m_tableProf.Insert(strdata,strContent,m_nType))
	{
		AfxMessageBox(_T("��������ʧ�ܣ�"));
		return;
	}
	m_lsProfession.AddString(strdata);
	m_edtContentProfession.SetWindowTextW(NULL);
	m_edtProfession.SetWindowTextW(NULL);
}


BOOL CDlgDatabaseEditTechnology::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	VectorTechnology vtheme = m_tableTech.GetData();
	for(int i = 0;i<vtheme.size();i++)
	{
		m_lsTechnology.AddString(vtheme[i].strName);
	}

	vectorProfession vdecade = m_tableProf.GetData();
	for(int i = 0;i<vdecade.size();i++)
	{
		m_lsProfession.AddString(vdecade[i].strProfessionName);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgDatabaseEditTechnology::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	m_nType = 0;
}


void CDlgDatabaseEditTechnology::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	m_nType  = 1;
}
