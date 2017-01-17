
// NorvelEditDoc.cpp : CNorvelEditDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "NorvelEdit.h"
#endif

#include "NorvelEditDoc.h"

#include <propkey.h>
#include "WizardSheet.h"

#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNorvelEditDoc

IMPLEMENT_DYNCREATE(CNorvelEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CNorvelEditDoc, CDocument)
END_MESSAGE_MAP()


// CNorvelEditDoc ����/����

CNorvelEditDoc::CNorvelEditDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CNorvelEditDoc::~CNorvelEditDoc()
{
}

BOOL CNorvelEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);
	}

	m_SaveFormat.CreateNew();

	CWizardSheet wsheet(_T("��"));
	wsheet.SetWizardMode();

	int ret = wsheet.DoModal() ;
	if(ret == 2)
		return TRUE;
	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	m_SaveFormat.m_strBookname = wsheet.GetBookName();
	m_SaveFormat.m_nTheme = wsheet.GetTheme();
	m_SaveFormat.m_nDecade = wsheet.GetDecade();

	CMainFrame * pMainFrm = (CMainFrame*)AfxGetMainWnd();

	pMainFrm->SetBookName(wsheet.GetBookName());
	return TRUE;
}




// CNorvelEditDoc ���л�

void CNorvelEditDoc::Serialize(CArchive& ar)
{
	// CEditView ����һ�������������л��ı༭�ؼ�
	//if (!m_viewList.IsEmpty())
	//{
	//	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	//}
	m_SaveFormat.Serialize(ar);

	AfxGetMainWnd()->SendMessage(GLOBAL_MSG_READ_FILE,0,0);
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != NULL)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CNorvelEditDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CNorvelEditDoc::InitializeSearchContent()
{
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ʹ�������ı��ļ���Ϊ�������ݡ�
	SetSearchContent(m_strSearchContent);
}

void CNorvelEditDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CNorvelEditDoc ���

#ifdef _DEBUG
void CNorvelEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNorvelEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNorvelEditDoc ����
