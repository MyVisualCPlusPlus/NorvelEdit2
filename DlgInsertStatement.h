#pragma once
#include "afxwin.h"


// CDlgInsertStatement �Ի���

class CDlgInsertStatement : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsertStatement)

public:
	CDlgInsertStatement(CWnd* pParent = NULL);   // ��׼���캯��
	CDlgInsertStatement(CString strKey,CWnd* pParent = NULL);
	virtual ~CDlgInsertStatement();

// �Ի�������
	enum { IDD = IDD_DIALOG_STATEMENT };
	CString m_strKeyWord;
	vectorBase	m_vectorData;
	CString m_strRetContent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_combTableName;
	CEdit m_edtSearchKey;
	CListBox m_lsKey;
	CStatic m_staticContent;

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboTable();
	afx_msg void OnLbnSelchangeListKeyWord();

	CString GetString();
	afx_msg void OnBnClickedButtonSearch();
};
