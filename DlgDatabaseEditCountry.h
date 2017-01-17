#pragma once
#include "afxwin.h"

#include "DatabaseTableCountry.h"
#include "DatabaseTableReligion.h"
// CDlgDatabaseEditCountry �Ի���

class CDlgDatabaseEditCountry : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDatabaseEditCountry)

public:
	CDlgDatabaseEditCountry(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDatabaseEditCountry();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATABASE_EDIT_COUNTRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCountry();
	afx_msg void OnBnClickedButtonReligious();
	virtual BOOL OnInitDialog();
	CListBox m_lsCountry;
	CListBox m_lsReli;
	CEdit m_edtCountry;
	CEdit m_edtContentCountry;
	CEdit m_edtReli;
	CEdit m_ContentReli;

	vectorCountry	m_vectorCountry;
	vectorReligion	m_vectorReligion;

	CDatabaseTableCountry m_tableCountry;
	CDatabaseTableReligion	m_tableReli;
	int m_nCountryType;
};
