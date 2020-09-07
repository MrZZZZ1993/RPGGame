#pragma once
class CSelectFile:public CKeyListener
{
public:
	CSelectFile();
	~CSelectFile();
	void Init();
	void Draw();
	void Update();
	void OnKeyDown(SEvent);
	void SetIsUp(bool);
	void Save();
	void LoadSave();
	void DeleteFile();
	int GetSaveNum();
	enum SELECT_FILE{eFILE_NONE=0,eFILE_ONE=1,eFILE_TWO=2,eFILE_THREE=3,eFILE_DELETE};
private:
	CMulImg *m_pFile1;
	CMulImg*m_pFile2;
	CMulImg*m_pFile3;
	CMulImg*m_pDelete;
	CStaticImg*m_pBg;
	CStaticImg*m_pLogo;
	CSingleImg*m_pFile;
	vector<CSingleImg*>m_file;
	int m_speed;
	int m_select;
	int m_save;
	int m_saveNum1;
	int m_saveNum2;
	int m_saveNum3;
	int m_count;
	bool m_bIsUp;
};

