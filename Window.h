/*
2023/1/30
�����йص�����
*/
#pragma once
#include "Header.h"

//���ñ�����ɫ
void SetWindowBackgroundColor(int);
//���ñ���
void SetWindowTitle(std::wstring);
//����ͼ��
void SetWindowIcon(int);
//���ù��
void SetWindowCursor(HCURSOR);
//ȫ��ģ�� https://codebus.cn/yangw/free-dots
//��������������
void Blur();
//��ȡfps
//����fps
int GetFPS();

//����
//���������С����������
//Size:����
void SetTextSize(double Size);
//�������忹���
void OpentTextAntiAliasing();
//�ر����忹���
void CloseTextAntiAliasing();
//����ָ��·������ https://codebus.cn/yangw/use-external-font-file
//Path��·��
void LoadFontPath(LPTSTR Path);
//ж��ָ��·������ https://codebus.cn/yangw/use-external-font-file
//Path��·��
void CloseFontPath(LPTSTR Path);

//�ö�����
void TopWindow();
//ȡ�������ö���������ײ�
void BottomWindow();
//���ش���
void HideWindow();
//��ʾ����
void ShowWindow();