
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "NorvelEdit.h"

#include "MainFrm.h"
#include "DlgGetName.h"
#include "DlgAddress.h"
#include "DlgDatabaseNameEdit.h"
#include "DlgCreateScene.h"
#include "DlgRoleDesign.h"
#include "DlgDatabaseTableEditOther.h"
#include "DlgDatabaseEditCommWord.h"
#include "NorvelEditView.h"
#include "DlgMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_MENU_GET_NAME, &CMainFrame::OnMenuGetName)
	ON_COMMAND(ID_MENU_ADDRESS, &CMainFrame::OnMenuAddress)

	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(ID_TOOLBAR_FONT_NAME, &CMainFrame::OnFontNameClickComboBox)
	ON_CBN_SELCHANGE(ID_TOOLBAR_FONT_NAME,&CMainFrame::OnFontNameSelChangeClick)//��������TOOLBAR�����IDR_COM��Դ��
	ON_COMMAND(ID_TOOLBAR_FONT_SIZE, &CMainFrame::OnFontSizeClickComboBox)
	ON_CBN_SELCHANGE(ID_TOOLBAR_FONT_SIZE,&CMainFrame::OnFontSizeSelChangeClick)


	ON_COMMAND(ID_MENU_DATABASE_NAME_EDIT, &CMainFrame::OnMenuDatabaseNameEdit)
	ON_COMMAND(ID_MENU_PLACE_NAME, &CMainFrame::OnMenuPlaceName)
	ON_COMMAND(ID_MENU_SENCE, &CMainFrame::OnMenuSence)
	ON_COMMAND(ID_MENU_PEOPLE, &CMainFrame::OnMenuPeople)
	ON_COMMAND(ID_MENU_TOTEL, &CMainFrame::OnMenuTotel)
	ON_COMMAND(ID_MENU_COMM_WORD, &CMainFrame::OnMenuCommWord)

	ON_MESSAGE(GLOBAL_MSG_TREE_SELECT_CHANGE,&CMainFrame::OnTreeViewSelectChange)
	ON_MESSAGE(GLOBAL_MSG_READ_FILE,&CMainFrame::OnMsgReadFile)
	ON_COMMAND(ID_MENU_MAP_EDIT, &CMainFrame::OnMenuMapEdit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_comboFont = NULL;
	m_comboFontSize = NULL;
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
	delete m_comboFont;
	delete m_comboFontSize;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	if (!m_wndFormatBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndFormatBar.LoadToolBar(IDR_TOOLBAR_FONT))
	{
		TRACE0("Failed to create FormatBar\n");
		return -1;      // fail to create
	}
	
	m_wndFormatBar.SetWindowText(_T("�����ʽ"));

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	m_wndFormatBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFormatBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	DockPane(&m_wndFormatBar);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndRoleNameView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCapterView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndRoleNameView);
	CDockablePane* pTabbedBar = NULL;
	m_wndCapterView.AttachToTabWnd(&m_wndRoleNameView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	CreateCaptionBar();
	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);



	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;

	//m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);

	//m_wndCaptionBar.SetButtonToolTip(strTemp);

	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	//m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);

	//m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ��������ͼ
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndCapterView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI  ))
	{
		TRACE0("δ�ܴ���������ͼ������\n");
		return FALSE; // δ�ܴ���
	}
	//m_wndClassView.ModifyStyle(0,TVS_EDITLABELS);

	// �����ļ���ͼ
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndRoleNameView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndRoleNameView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndCapterView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::OnMenuGetName()
{
	// TODO: Add your command handler code here
	CDlgGetName dlg;
	dlg.DoModal();
}


void CMainFrame::OnMenuAddress()
{
	// TODO: Add your command handler code here
	CDlgAddress dlg;
	dlg.DoModal();
}

void CMainFrame::SetBookName( CString strBookName )
{
	m_wndCapterView.SetBookTitle(strBookName);
}

LRESULT CMainFrame::OnToolbarReset( WPARAM,LPARAM )
{
	if(m_comboFont != NULL)
	{
		delete m_comboFont;
		m_comboFont= NULL;
	}
	m_comboFont = new CMFCToolBarComboBoxButton(ID_TOOLBAR_FONT_NAME,GetCmdMgr()->GetCmdImage(ID_TOOLBAR_FONT_NAME, FALSE));
	m_comboFont->SetVisible();
	m_comboFont->EnableWindow(true);
	m_comboFont->SetCenterVert();
	m_comboFont->SetDropDownHeight(25);
	m_comboFont->SetFlatMode();

	CClientDC dc(this); 
	::EnumFontFamilies( dc.m_hDC, NULL, (FONTENUMPROC)EnumFontFamProc, 
				(LPARAM) this );

	m_comboFont->SelectItem(0); 
	m_wndFormatBar.ReplaceButton (ID_TOOLBAR_FONT_NAME, *m_comboFont);

	if(m_comboFontSize != NULL)
	{
		delete m_comboFontSize;
		m_comboFontSize= NULL;
	}
	m_comboFontSize = new CMFCToolBarComboBoxButton(ID_TOOLBAR_FONT_SIZE,GetCmdMgr()->GetCmdImage(ID_TOOLBAR_FONT_SIZE, FALSE));
	m_comboFontSize->SetVisible();
	m_comboFontSize->EnableWindow(true);
	m_comboFontSize->SetCenterVert();
	m_comboFontSize->SetDropDownHeight(25);
	m_comboFontSize->SetFlatMode();
	
	m_comboFontSize->AddItem(_T("8"));
	m_comboFontSize->AddItem(_T("9"));
	m_comboFontSize->AddItem(_T("10"));
	m_comboFontSize->AddItem(_T("11"));

	m_comboFontSize->AddItem(_T("12"));
	m_comboFontSize->AddItem(_T("14"));

	m_comboFontSize->AddItem(_T("16"));
	m_comboFontSize->AddItem(_T("18"));

	m_comboFontSize->AddItem(_T("20"));
	m_comboFontSize->AddItem(_T("22"));

	m_comboFontSize->AddItem(_T("24"));
		m_comboFontSize->AddItem(_T("26"));
		m_comboFontSize->AddItem(_T("28"));
		m_comboFontSize->AddItem(_T("36"));
		m_comboFontSize->AddItem(_T("48"));
		m_comboFontSize->AddItem(_T("72"));


	m_comboFontSize->SelectItem(0); 
	m_wndFormatBar.ReplaceButton (ID_TOOLBAR_FONT_SIZE, *m_comboFontSize);

	return 0;
}

void CMainFrame::OnFontNameSelChangeClick()
{
	CMFCToolBarComboBoxButton* pSrcCombo = CMFCToolBarComboBoxButton::GetByCmd (ID_TOOLBAR_FONT_NAME, TRUE);
	int index = pSrcCombo->GetCurSel();
	CString str = pSrcCombo->GetItem(index);

	CRichEditView* tempview = (CRichEditView*)GetActiveView();

	CHARFORMAT2W cf;
	cf.dwMask = CFM_FACE;
	_tcscpy_s(cf.szFaceName,str);
	tempview->SetCharFormat(cf);
}

void CMainFrame::OnFontNameClickComboBox()
{

}

void CMainFrame::OnFontSizeSelChangeClick()
{
	CMFCToolBarComboBoxButton* pSrcCombo = CMFCToolBarComboBoxButton::GetByCmd (ID_TOOLBAR_FONT_SIZE, TRUE);
	int index = pSrcCombo->GetCurSel();
	CString str = m_comboFontSize->GetItem(index);

	
	CRichEditView* tempview = (CRichEditView*)GetActiveView();

	CHARFORMAT2W cf;
	cf.dwMask = CFM_SIZE;
	cf.yHeight = _ttoi(str) * 20;
	tempview->SetCharFormat(cf);
}

void CMainFrame::OnFontSizeClickComboBox()
{

}

int CALLBACK CMainFrame::EnumFontFamProc( ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm, int nFontType, LPARAM lParam )
{
	CMainFrame* pWnd = (CMainFrame*)lParam;

	// Add the font name to the combo
	//pWnd->m_cmbFontName.AddString(lpelf->elfLogFont.lfFaceName);
	pWnd->m_comboFont->AddItem(lpelf->elfLogFont.lfFaceName);
	return 1;		// 1 to continue enumeration
}


void CMainFrame::OnMenuDatabaseNameEdit()
{
	// TODO: �ڴ���������������
	CDlgDatabaseNameEdit dlg;
	dlg.DoModal();
}






void CMainFrame::OnMenuPlaceName()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnMenuSence()
{
	// TODO: �ڴ���������������
	
	//vector<CString> retVector;
	g_Global.m_vectorChapter.clear();
	m_wndCapterView.GetTreeItemText(g_Global.m_vectorChapter);
	CDlgCreateScene dlg(this);
	if(dlg.DoModal() != IDOK)
		return;

	CNorvelEditDoc *pDoc = (CNorvelEditDoc*)GetActiveDocument();

	SceneFormat scene = dlg.GetSceneFormat();
	pDoc->m_SaveFormat.m_vectorScene.push_back(scene);
}


void CMainFrame::OnMenuPeople()
{
	// TODO: �ڴ���������������
	//vector<CString> retVector;
	g_Global.m_vectorChapter.clear();
	m_wndCapterView.GetTreeItemText(g_Global.m_vectorChapter);
	CDlgRoleDesign dlg(this);
	if(dlg.DoModal() != IDOK)
	{
		return;
	}
	RoleProperties tempRole = dlg.GetRoleData();

	CNorvelEditDoc *pDoc = (CNorvelEditDoc*)GetActiveDocument();

	pDoc->m_SaveFormat.m_vectorRole.push_back(tempRole);
	m_wndRoleNameView.AddNameItem(tempRole.m_strName);
}


void CMainFrame::OnMenuTotel()
{
	// TODO: �ڴ���������������
	CDlgDatabaseTableEditOther dlg;
	dlg.DoModal();
}


void CMainFrame::OnMenuCommWord()
{
	// TODO: Add your command handler code here
	CDlgDatabaseEditCommWord dlg;
	dlg.DoModal();
}

LRESULT CMainFrame::OnTreeViewSelectChange(WPARAM wparam,LPARAM lparam )
{
	CString strTemp = *(CString*)lparam;

	CNorvelEditView* tempview = (CNorvelEditView*)GetActiveView();

	tempview->DisplayTextByTitle(strTemp);
	m_wndOutput.SetScene();

	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_CENTER);
	return 0;
}

LRESULT CMainFrame::OnMsgReadFile( WPARAM wparam,LPARAM lparam )
{
	m_wndCapterView.ReadDataFromFile();
	m_wndRoleNameView.ReadDataFromFile();
	return 0;
}


void CMainFrame::OnMenuMapEdit()
{
	// TODO: �ڴ���������������
	CDlgMap	dlg;
	dlg.DoModal();
}
