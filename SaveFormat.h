#pragma once
#include <vector>
using namespace std;
/*��ɫ����*/
typedef struct tag_RoleProperties
{
	TCHAR m_strName[24];		//��������
	SYSTEMTIME m_timeBirthday;	//����
	int m_nAge;					//����
	int m_nWorkType;			//����
	bool m_nSex;				//�Ա�
	int m_nStartChapter;		//��ʼ��
	//int m_nCloth;				//��װ
	int m_nChara;				//�Ը�
	int m_nReleation;			//�����ǹ�ϵ

	TCHAR m_strExplain[256];	//˵��
	TCHAR m_strTheEnd[256];		//���ս��
}RoleProperties;
/*����״̬*/
typedef struct tag_RoleStatus
{
	int m_nClothType;		//�������ʽ
	int m_nBodyStatus;		//��������״̬
	int m_nFaceExpression;	//����
	int m_nHeartExpression;	//����
}RoleStatus;

/*��������*/
typedef struct tag_SceneFormat
{
	TCHAR	m_strSceneName[24];//��������
	int		m_nChapterID;		//��ID
	int		m_nSegment;			//��ID

	int		m_nSceneType; //��������
	TCHAR	m_strAddress[24];//�����ص�
	int		m_nTime;//ʱ��
	int		m_nTimeLong;//ʱ��
	int		m_nGeographicalEnvironment;//������
	int		m_nWeather;//����״̬
	int		m_nTimeUnit;//ʱ�䵥λ

	int				m_nMainRoleID;	//��Ҫ��ɫID
	RoleStatus		m_RoleStatus;//��Ҫ��ɫ״̬

	TCHAR			m_strOtherRole[32][24];//������ɫID
	RoleStatus		m_nOtherStatus[32];//������ɫ״̬

	TCHAR					m_strEventStart[255];//����
	TCHAR					m_strEventProgress[255];//����
	TCHAR					m_strEventEnd[255];//���

}SceneFormat;

typedef struct tag_Chapter
{
	CString strName;
	CString	strData;
}STRUCT_CHAPTER;

typedef vector<STRUCT_CHAPTER> VectorCapter;

class CSaveFormat:public CObject
{
	DECLARE_SERIAL(CSaveFormat)
public:
	CSaveFormat(void);
	~CSaveFormat(void);
public:
	void			CreateNew();
	CString			m_strBookname;
	int				m_nTheme;
	int				m_nDecade;
	vector<RoleProperties>	m_vectorRole;
	vector<SceneFormat>		m_vectorScene;
	VectorCapter			m_vectorCapter;

	virtual void Serialize(CArchive&);

	void WriteRole( CString strFilePath ); 


	void WriteIni( CString strFilePath ) ;


	void ReadRole( CString strFilePath ) ;


	void ReadIni( CString strFilePath );

	void ReadScene(CString strFilePath);
	void WriteScene(CString strFilePath);
};

