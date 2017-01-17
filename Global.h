#pragma once
#include <vector>
#include <string>
using namespace std;
#include "CppSQLite3U.h"
#include "DatabaseTableBase.h"

#define GLOBAL_DATABASE_NAME				_T("MainBase.db")//��������
#define GLOBAL_TABLE_LAST_NAME				_T("lastName")		//��
#define GLOBAL_TABLE_FIRST_NAME				_T("firstName")		//��
#define GLOBAL_TABLE_THEME					_T("theme")//С˵���
#define GLOBAL_TABLE_DECADE					_T("decade")//���
#define GLOBAL_TABLE_PROFESSION				_T("profession")//ְҵ
#define GLOBAL_TABLE_GEOGRAPHY				_T("geography")//����
#define GLOBAL_TABLE_WEATHER				_T("weather")//����
#define GLOBAL_TABLE_CLOTH					_T("cloth")//С˵�·�
#define GLOBAL_TABLE_THINGS					_T("things")//С˵��Ʒ
#define GLOBAL_TABLE_TECHNOLOGY				_T("technology")//���� һЩ�߿Ƽ������Լ�����

#define GLOBAL_TABLE_COMMON_WORD			_T("common_word")//���ú���
#define GLOBAL_TABLE_COUNTRY				_T("country")//���ң�ʡ������
#define GLOBAL_TABLE_RELIGION				_T("religion")//�ڽ�

#define GLOBAL_TABLE_ANIMA					_T("animation")//�����ʵ�����룬�񻰣��ƻ�
#define GLOBAL_TABLE_PLANE					_T("plane")//ֲ��
#define GLOBAL_TABLE_WEAPON					_T("weapon")//����
#define GLOBAL_TABLE_RANK					_T("rank")//���Σ��ֹŴ����ִ�
#define GLOBAL_TABLE_TITLE					_T("title")//�ųƣ���������
#define GLOBAL_TABLE_TIME_UNIT				_T("time_unit")//С˵ʱ��

#define GLOBAL_TABLE_SCENE_TYPE				_T("scene_type")//�������� ˵����ѧϰ���о������������̣�ս������Ϸ
#define GLOBAL_TABLE_MOOD					_T("mood")//����
#define GLOBAL_TABLE_EXPRESSION				_T("expression")//����
#define GLOBAL_TABLE_COMM_TIME_LEN			_T("time_len")//����ʱ��

#define GLOBAL_TABLE_CHARACTER				_T("character")		//�Ը�����
#define GLOBAL_TABLE_RELACTIONSHIP			_T("relactionship")//�˼ʹ�ϵ
#define GLOBAL_TABLE_ROLE_STATUS			_T("role_status")//����״̬

#define GLOBAL_TABLE_GIRL					_T("girl")//��������
#define GLOBAL_TABLE_BOY					_T("boy")//������д
//#define GLOBAL_TABLE_LINK					_T("LIKE")//ϲ��
//#define GLOBAL_TABLE_HATE					_T("HATE")//����
#define GLOBAL_MSG_TREE_SELECT_CHANGE		WM_USER+0x01
#define GLOBAL_MSG_READ_FILE				WM_USER+0x02
typedef struct tag_structTable
{
	CString strName;
	CString strContent;
}structTable;
typedef vector<structTable> VectorTable;

class CGlobal
{
public:
	CGlobal(void);
	~CGlobal(void);
public:
	//CDataBaseName m_DataBase;
	CString			m_strTreeSelectItem;
	VectorTable		m_vectorTable;
	vector<CString>	m_vectorChapter;
	static CString GetExePath();
	static CString GetDataBasePath();
	
};

extern CGlobal g_Global;