#include "StdAfx.h"
#include "Global.h"


CGlobal::CGlobal(void)
{
	structTable tempTable;
	tempTable.strName = GLOBAL_TABLE_ANIMA;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);
	tempTable.strName = GLOBAL_TABLE_PLANE;
	tempTable.strContent = _T("ֲ��");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_WEAPON;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);	

	tempTable.strName = GLOBAL_TABLE_RANK;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);		

	tempTable.strName = GLOBAL_TABLE_TITLE;
	tempTable.strContent = _T("�ƺ�");
	m_vectorTable.push_back(tempTable);		
	tempTable.strName = GLOBAL_TABLE_TIME_UNIT;
	tempTable.strContent = _T("ʱ�䵥λ");
	m_vectorTable.push_back(tempTable);
	tempTable.strName = GLOBAL_TABLE_SCENE_TYPE;
	tempTable.strContent = _T("��������");

	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_MOOD;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);
	tempTable.strName = GLOBAL_TABLE_EXPRESSION;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_COMM_TIME_LEN;
	tempTable.strContent = _T("ʱ��");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_CHARACTER;
	tempTable.strContent = _T("�Ը�");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_RELACTIONSHIP;
	tempTable.strContent = _T("�˼ʹ�ϵ");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_ROLE_STATUS;
	tempTable.strContent = _T("����״̬");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_THEME;
	tempTable.strContent = _T("���");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_DECADE;
	tempTable.strContent = _T("���");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_WEATHER;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_GEOGRAPHY;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_CLOTH;
	tempTable.strContent = _T("��װ");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_THINGS;
	tempTable.strContent = _T("��Ʒ");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_COUNTRY;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_RELIGION;
	tempTable.strContent = _T("�ڽ�");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_PROFESSION;
	tempTable.strContent = _T("ְҵ");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_TECHNOLOGY;
	tempTable.strContent = _T("����");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_GIRL;
	tempTable.strContent = _T("Ů����ò");
	m_vectorTable.push_back(tempTable);

	tempTable.strName = GLOBAL_TABLE_BOY;
	tempTable.strContent = _T("������ò");
	m_vectorTable.push_back(tempTable);

}


CGlobal::~CGlobal(void)
{
}

CString CGlobal::GetExePath()
{
	static CString strPath;
	if(strPath.IsEmpty())
	{
		TCHAR buf[256] = {0};  
		GetModuleFileName(NULL, buf, sizeof(buf)/sizeof(TCHAR));  
		strPath = buf;         
		strPath = strPath.Left(strPath.ReverseFind('\\') + 1);  
	}
	return strPath;
}

CString CGlobal::GetDataBasePath()
{
	CString strExepath = GetExePath();
	strExepath += _T("Database\\");
	strExepath += GLOBAL_DATABASE_NAME;
	return strExepath;
}

CGlobal g_Global;