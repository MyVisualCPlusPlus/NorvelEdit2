#pragma once

#define FIRST_YEAR 1936 /* the first year in lunarcal[] */ 

struct convdate 
{ 
	int source; 
	int solaryear; 
	int solarmonth; 
	int solardate; 
	int lunaryear; 
	int lunarmonth; 
	int lunardate; 
	int weekday; 
	int kan; 
	int chih; 
}; 

typedef struct tag_lunarcal 
{ 
	int basedays; /* ������ 1 �� 1 �յ�ũ�����³�һ���ۻ����� */ 
	int intercalation; /* �����·�. 0==����û������ */ 
	int baseweekday; /* �������� 1 �� 1 ��Ϊ���ڼ��ټ� 1 */ 
	int basekanchih; /* �������� 1 �� 1 ��֮��֧��ż� 1 */ 
	int monthdays[13]; /* ��ũ����ÿ��֮��С, 0==С��(29��), 1==����(30��)*/ 
}StructLunarcal; 

class CDataConvert
{
public:
	CDataConvert(void);
	~CDataConvert(void);
public:
	int getleap( int year );
	int calconv( struct convdate *cd );
	CString GetDayOf(PSYSTEMTIME pSt);
};

