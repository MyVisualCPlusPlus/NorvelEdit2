#pragma once
#include "mapcanvas.h"
#include "afxwin.h"


// CDlgMap �Ի���


class CDlgMap : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMap)

public:
	CDlgMap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMap();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAP_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMapCanvas m_MapCanvas;
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void SetCtrlPosition( int cx, int cy );
	

	CButton m_btnOK;
	CButton m_btnCancel;
	virtual BOOL OnInitDialog();
	int m_nDrawType;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheckDispCon();
	CButton m_chkCon;
	CButton m_chkLine;
	afx_msg void OnBnClickedCheckDispLine();
	afx_msg void OnBnClickedOk();
};
