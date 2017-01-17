#pragma once
#include "afxwin.h"

#include "DatabaseTableTechnology.h"
#include "DatabaseTableProfession.h"
// CDlgDatabaseEditTechnology �Ի���

class CDlgDatabaseEditTechnology : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDatabaseEditTechnology)

public:
	CDlgDatabaseEditTechnology(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDatabaseEditTechnology();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATABASE_EDIT_PROFRESSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lsTechnology;
	CListBox m_lsProfession;
	CEdit m_edtTech;
	CEdit m_edtContentTech;
	CEdit m_edtProfession;
	CEdit m_edtContentProfession;

	CDatabaseTableTechnology	m_tableTech;
	CDatabaseTableProfession	m_tableProf;

	VectorTechnology	m_vectorTech;
	vectorProfession	m_vectorProf;

	afx_msg void OnBnClickedButtonTechnology();
	afx_msg void OnBnClickedButtonProfession();
	virtual BOOL OnInitDialog();
	int m_nType;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
