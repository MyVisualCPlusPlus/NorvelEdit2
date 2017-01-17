#pragma once
#include "afxwin.h"

#include "DatabaseTableTheme.h"
#include "DatabaseTableDecade.h"
// CDlgDatabaseEdit �Ի���

class CDlgDatabaseEditTheme : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDatabaseEditTheme)

public:
	CDlgDatabaseEditTheme(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDatabaseEditTheme();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATABASE_EDIT_THEME };

	CDatabaseTableTheme  table_theme;
	CDatabaseTableDecade table_eDecade;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTheme();
	CEdit m_edtTheme;
	CEdit m_edtThemeContent;
	CEdit m_edtDecade;
	CEdit m_edtDecadeContent;
	afx_msg void OnBnClickedButtonDecade();
	CListBox m_lsTheme;
	CListBox m_lsDecade;
	virtual BOOL OnInitDialog();
};
