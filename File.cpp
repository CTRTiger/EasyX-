#include "File.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

int GetFileLine(const char* filename)
{
	FILE* fd;
	int count = 0;
	if (fd = fopen(filename, "r"))
		while (!feof(fd))
			if ('\n' == fgetc(fd))
				++count;
	if (fd)
		fclose(fd);
	return count;
}
string _U8ToGB(const char* str)
{
	std::string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//�����ʱ�����Ĵ�С
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//�����ʱ�����Ĵ�С
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}
string ReadFileLineContent(char* filename, int line)
{
	int i = 0;
	string temp;
	fstream file;
	file.open(filename, ios::in);

	if (line <= 0)
		return "Error:Wrong number of rows,only accept positive integer";
	if (file.fail())
		return "Error:Can't find the file";
	while (getline(file, temp) && i < line - 1)
		++i;
	temp = _U8ToGB(temp.c_str());
	file.close();
	return temp;
}
void ChangeFileLineContent(char* fileName, int lineNum, const char* lineData)
{
	ifstream in;
	in.open(fileName);
	string strFileData = "";
	int line = 1;
	char tmpLineData[1024] = { 0 };
	while (in.getline(tmpLineData, sizeof(tmpLineData)))
	{
		if (line == lineNum)
		{
			strFileData += string(lineData);
			strFileData += "\n";
		}
		else
		{
			strFileData += string(tmpLineData);
			strFileData += "\n";
		}
		++line;
	}
	in.close();
	//д���ļ�
	ofstream out;
	out.open(fileName);
	out.flush();
	out << strFileData;
	out.close();
}