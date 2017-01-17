#pragma once
#include "afxwin.h"
#include "DatabaseTableCloth.h"
#include "DatabaseTableThings.h"


// CDlgDatabaseEditCloth �Ի���

class CDlgDatabaseEditCloth : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDatabaseEditCloth)

public:
	CDlgDatabaseEditCloth(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDatabaseEditCloth();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATABASE_EDIT_CLOTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lsCloth;
	CListBox m_lsThings;
	CEdit m_edtCloth;
	CEdit m_edtContentCloth;
	CEdit m_edtThings;
	CEdit m_edtContentThings;

	CDatabaseTableCloth	m_tableCloth;
	CDatabaseTableThings m_tableThing;

	VectorThings	m_vectorThings;
	vectorCloth		m_vectorCloth;

	afx_msg void OnBnClickedButtonCloth();
	afx_msg void OnBnClickedButtonThings();
	virtual BOOL OnInitDialog();
};
