/*
2023/2/12
����
*/
#pragma once
#include "Header.h"

//�������
//���������� A<B
int Random(int A, int B);
//��׼�ӳٺ��� https://codebus.cn/yangw/accurate-delayc
//��λ����
void HpSleep(int);
//�����������ַ��� https://blog.csdn.net/airen3339/article/details/122716734
void ClipboardString(std::string);
//�Ӽ������ȡ�ַ��� https://blog.csdn.net/airen3339/article/details/122716734
std::string GetClipboardString();

//stringתwstring https://blog.csdn.net/c914620529/article/details/73503708
std::wstring StringToWString(const std::string&);
//wstringתstring https://blog.csdn.net/c914620529/article/details/73503708
std::string WStringToString(const std::wstring&);
//��Http������������ https://blog.csdn.net/shuilongyin_00/article/details/123790576
//Url��Http���� FileName�������·��
int DownloadFromHttp(std::string Url, std::string FileName);
//���غ�����������������ʱ�������ؽ��ȵ���Ӧ����
//��Ӧ����������ֵvoid�������б�int
int DownloadFromHttp(std::string Url, std::string FileName, void (*Function)(double));

//������Ƶ
//���mp3�ļ��޷����ţ���������Ϊ�������ȥ�����С����
class Audio
{
public:
	Audio() {};
	Audio(std::wstring Path);
	~Audio();
	//����·��
	void SetAudioPath(std::wstring); 
	//����
	void Play(); 
	//���Ų�ѭ��
	void PlayRepeat(); 
	//���Ų��ȴ�����
	void PlayWait(); 
	//ֹͣ
	void Stop(); 
	//��ͣ
	void Pause(); 
	//����
	void Resume(); 
	//�ر�
	void Close(); 
	//������bug�����Ƽ�ʹ�á� ���ò���λ�ã�����λ�ã���λ�����룩/start����ͷ��/end����β��
	void Seek(std::wstring); 
	//�������� ��Χ��0-1000
	void SetVolume(std::wstring); 
	//��ȡ���� ���أ����� ��Χ��0-1
	double GetProgress(); 
private:
	std::wstring AudioPath;
};
