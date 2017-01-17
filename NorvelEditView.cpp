
// NorvelEditView.cpp : CNorvelEditView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "NorvelEdit.h"
#endif

#include "NorvelEditDoc.h"
#include "NorvelEditView.h"
#include "DlgInsertStatement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNorvelEditView

IMPLEMENT_DYNCREATE(CNorvelEditView, CRichEditView)

BEGIN_MESSAGE_MAP(CNorvelEditView, CRichEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNorvelEditView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MENU_FONT_SET, &CNorvelEditView::OnMenuFontSet)

	ON_COMMAND(ID_EDIT_CUT, &CNorvelEditView::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CNorvelEditView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CNorvelEditView::OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CNorvelEditView::OnEditSelectAll)
	ON_COMMAND_RANGE(ID_MENU_FIRST,ID_MENU_FIRST+g_Global.m_vectorTable.size(),OnPopMenuFirstID)
	ON_COMMAND(ID_FILE_SAVE, &CNorvelEditView::OnFileSave)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CNorvelEditView ����/����

CNorvelEditView::CNorvelEditView()
{
	// TODO: �ڴ˴���ӹ������
	m_bChange = false;
}

CNorvelEditView::~CNorvelEditView()
{
}

BOOL CNorvelEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CRichEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CNorvelEditView ��ӡ


void CNorvelEditView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNorvelEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CRichEditView ׼��
	return CRichEditView::OnPreparePrinting(pInfo);
}

void CNorvelEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CRichEditView ��ʼ��ӡ
	CRichEditView::OnBeginPrinting(pDC, pInfo);
}

void CNorvelEditView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CRichEditView ������ӡ
	CRichEditView::OnEndPrinting(pDC, pInfo);
}

void CNorvelEditView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNorvelEditView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	CPoint pt;
	GetCursorPos(&pt);

	CMenu m_NewMenu;
	m_NewMenu.LoadMenu(IDR_POPUP_EDIT);//�����˵�,��������Դ�������н���

	CMenu* pM = m_NewMenu.GetSubMenu(0);//һ�������˵�

	CMenu *pSubmenu=pM->GetSubMenu(pM->GetMenuItemCount()-1);//�����Ӳ˵�
	ASSERT(pSubmenu);

	UINT nEnable = MF_BYPOSITION|MF_STRING|MF_ENABLED;
	for(int i = 0;i<g_Global.m_vectorTable.size();i++)
	{
		pSubmenu->InsertMenu(pSubmenu->GetMenuItemCount()-1, nEnable,(UINT_PTR)(ID_MENU_FIRST+i),g_Global.m_vectorTable[i].strContent);
	}

	int SelectID = pM->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL//|
		/*TPM_RETURNCMD*/, pt.x, pt.y, this);

	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNorvelEditView ���

#ifdef _DEBUG
void CNorvelEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CNorvelEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CNorvelEditDoc* CNorvelEditView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNorvelEditDoc)));
	return (CNorvelEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CNorvelEditView ��Ϣ�������


void CNorvelEditView::OnMenuFontSet()
{
	// TODO: Add your command handler code here
	CString strFontName;    // ��������   
	LOGFONT lf;             // LOGFONT����   

	// ��lf�����ֽ�����   
	memset(&lf, 0, sizeof(LOGFONT));   

	// ��lf�е�Ԫ����������Ϊ�����塱   
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("����"));   

	
	// ��������Ի��򣬳�ʼѡ��������Ϊ�����塱   
	CFontDialog fontDlg(&lf);   

	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���   
	{   
		// ���m_font�Ѿ�������һ��������Դ�������ͷ���   
		if (m_Font.m_hObject)   
		{   
			m_Font.DeleteObject();   
		}   
		// ʹ��ѡ�������LOGFONT�����µ�����   
		m_Font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);   
		// ��ȡ�༭��IDC_FONT_EDIT��CWndָ�룬������������   
		SetFont(&m_Font);      
	}   
}



void CNorvelEditView::OnEditCut()
{
	// TODO: �ڴ���������������
	CRichEditView::OnEditCut();
}


void CNorvelEditView::OnEditCopy()
{
	// TODO: �ڴ���������������
	CRichEditView::OnEditCopy();
}


void CNorvelEditView::OnEditPaste()
{
	// TODO: �ڴ���������������
	CRichEditView::OnEditPaste();
}


void CNorvelEditView::OnEditSelectAll()
{
	// TODO: �ڴ���������������
	CRichEditView::OnEditSelectAll();
}

void CNorvelEditView::OnPopMenuFirstID(UINT id)
{
	int a = id - ID_MENU_FIRST;

	CDlgInsertStatement dlg(g_Global.m_vectorTable[a].strName);
	if(dlg.DoModal() != IDOK)
		return;
	
	GetRichEditCtrl().ReplaceSel(dlg.GetString(),TRUE);

	
	//AfxMessageBox(g_Global.m_vectorTable[a].strName);
}

void CNorvelEditView::DisplayTextByTitle( CString strTitle )
{
	
	//GetDocument()->OnSaveDocument(GetDocument()->m_SaveFormat.m_strBookname);
	if(strTitle.IsEmpty())
		return;

	CNorvelEditDoc* doc = GetDocument();
	if(g_Global.m_strTreeSelectItem.IsEmpty())
	{
		g_Global.m_strTreeSelectItem = strTitle;
	}
	else
	{
		if(m_bChange)
		{
			for(int i = 0;i<doc->m_SaveFormat.m_vectorCapter.size();i++)
			{
				if(doc->m_SaveFormat.m_vectorCapter[i].strName == g_Global.m_strTreeSelectItem)
				{
					GetWindowTextW(doc->m_SaveFormat.m_vectorCapter[i].strData);
					break;
				}
			}
		}
	}

	bool bfind = false;
	for(int i = 0;i<doc->m_SaveFormat.m_vectorCapter.size();i++)
	{
		if(doc->m_SaveFormat.m_vectorCapter[i].strName == strTitle)
		{
			bfind = true;
			SetWindowTextW(doc->m_SaveFormat.m_vectorCapter[i].strData);
			break;
		}
	}
	if(!bfind)
	{
		SetWindowTextW(NULL);
	}
	m_bChange = false;
	g_Global.m_strTreeSelectItem = strTitle;
}


void CNorvelEditView::OnFileSave()
{
	// TODO: �ڴ���������������
	for(int i = 0;i<GetDocument()->m_SaveFormat.m_vectorCapter.size();i++)
	{
		if(GetDocument()->m_SaveFormat.m_vectorCapter[i].strName == g_Global.m_strTreeSelectItem)
		{
			GetWindowTextW(GetDocument()->m_SaveFormat.m_vectorCapter[i].strData);
			break;
		}
	}
	CString strFullPath = g_Global.GetExePath();
	
	if(GetDocument()->m_SaveFormat.m_strBookname.IsEmpty())
	{
		AfxMessageBox(_T("������û�𣬱����ë����"));
		return;
	}

	strFullPath += GetDocument()->m_SaveFormat.m_strBookname;

	CreateDirectory(strFullPath,NULL);

	strFullPath += _T("\\");
	strFullPath += GetDocument()->m_SaveFormat.m_strBookname;
	strFullPath += _T(".nov");
	GetDocument()->OnSaveDocument(strFullPath);
}


void CNorvelEditView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	m_bChange = true;
	CRichEditView::OnChar(nChar, nRepCnt, nFlags);
}
