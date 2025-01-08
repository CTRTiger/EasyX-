/*
2023/2/13
�ļ��йص�����

//��������й�_CRT_SECURE_NO_WARNINGS�ı������ڡ����ԡ���C/C++����Ԥ����������Ԥ���������塪���༭������ӡ�_CRT_SECURE_NO_WARNINGS��
*/
#pragma once
#include "Header.h"

//��ȡ�ļ�����
//�������� filename���ļ���
int GetFileLine(const char* filename);
//��ȡ�ļ�ĳ������
//�������� filename���ļ��� line������
std::string ReadFileLineContent(char* filename, int line);
//�����ļ�ĳ������
//fileName���ļ��� lineNum������ lineDate���µ�����
void ChangeFileLineContent(char* fileName, int lineNum, const char* lineData);

//����һ��ѡ���ļ��Ի���
//�����ļ�λ�� FileType��ѡ���ļ����������ƣ���ʹ��ͨ���������\0�ָ����Ϊ��ʾ��ѡ�����ƺ��ļ��� Title���Ի���ı���
//�磺"All\0*.*\0Cpp\0*.cpp\0README\0README.MD\0"
std::wstring GetFilePath(std::wstring FileType, std::wstring Title);
//����һ����ȡ����λ�öԻ���
//�����ļ�λ�ã������ļ����� FileType�������ļ������ƣ���ʹ��ͨ���������\0�ָ����Ϊ��ʾ��ѡ�����ƺ��ļ��� Title���Ի���ı���
//�磺"All\0*.*\0Cpp\0*.cpp\0README\0README.MD\0"
std::wstring GetSavePath(std::wstring FileType, std::wstring Title);
