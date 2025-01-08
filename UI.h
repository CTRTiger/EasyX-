#pragma once
#include "Header.h"

//ƽʱ
const int UI_NORMAL = 0;
//�����ͣ
const int UI_ONPASS = 1;
//����
const int UI_ONCLICK = 2;

//�����Ŀ���
const int ANIMATION = 7;

//��ť����۽ṹ��
struct ButtonStyle
{
	/* 0��ƽʱ��1�������ͣ��2����� */
	//�߿���ɫ
	int EdgeColor[3] = { RGB(208, 208, 208) ,RGB(0, 120, 212) ,RGB(0, 120, 212) };
	//������ɫ
	int BackgroundColor[3] = { RGB(253, 253, 253) ,RGB(224, 238, 249) ,RGB(204, 228, 247) };
	//������ɫ
	int TextColor[3] = { RGB(0, 0, 0) , RGB(0, 0, 0) , RGB(94, 94, 94) };
};
//��ť
class Button
{
public:
	Button() {};
	//���Ͻ�X���꣬���Ͻ�Y���꣬��ȣ��߶ȣ���ʾ����
	Button(int, int, int, int, std::wstring);
	//���Ͻ�X���꣬���Ͻ�Y���꣬��ȣ��߶ȣ���ʾ���ݣ���۽ṹ��
	Button(int, int, int, int, std::wstring, ButtonStyle);
	//���ð�ť��۽ṹ��
	void SetStyle(ButtonStyle);
	//ˢ�°�ť����Ⱦ
	//���ص�ǰ״̬
	int Flush(ExMessage);
	//�ض���ť����Ⱦ���������ΪNULL��ʹ��Ĭ��
	//��������ֵvoid������int������Ϊ��ǰ״̬
	void RedirectRenderFunction(void (*)(int));
	//���ð�ť����Ϣ�����������ΪNULL��ʹ��
	// ��������ֵvoid������int������Ϊ��ǰ״̬
	void SetUIMsgProc(void (*)(int));
	//��������
	void SetText(std::wstring);
	//�������ð�ťλ�ú�����
	//���Ͻ�X���꣬���Ͻ�Y���꣬��ȣ��߶�
	void Reset(int, int, int, int);
	//���ó�����ť���ı���ʾ����
	//��� https://docs.easyx.cn/zh-cn/drawtext
	//DT_WORDBREAK�����������Զ����У�DT_WORD_ELLIPSIS���������ֽضϲ���...����
	void SetTextRender(UINT);
private:
	int X, Y, Width, Height; //��С
	int Edge = RGB(0, 120, 212), Background = RGB(253, 253, 253), text = RGB(0, 0, 0); //��ǰ��ɫ
	UINT TextRenderType = DT_WORD_ELLIPSIS | DT_CENTER | DT_VCENTER | DT_SINGLELINE; //������Ⱦģʽ
	std::wstring Text; //����
	ButtonStyle Style; //��۽ṹ��
	RECT TextRectangle; //��������ľ��η�Χ
	void (*RedirectRender) (int) = NULL, (*MsgProc) (int) = NULL; //�Զ�����Ⱦ��������Ϣ������

	void Render(int); //��Ⱦ����
};

//��ק������۽ṹ��
struct SeekBarStyle
{
	/* 0��ƽʱ��1�������ͣ��2����� */
	//���/�·� ��ɫ
	int LeftLineColor[3] = { RGB(0, 103, 192) ,RGB(0, 103, 192) ,RGB(0, 103, 192) };
	//�Ҳ�/�Ϸ� ��ɫ
	int RightLineColor[3] = { RGB(127, 127, 127) ,RGB(127, 127, 127) ,RGB(127, 127, 127) };
	//�м䰴ť�߿���ɫ
	int ButtonEdgeColor[3] = { RGB(254, 254, 255) , RGB(254, 254, 255) , RGB(254, 254, 255) };
	//�м䰴ť��ɫ
	int ButtonColor[3] = { RGB(0, 103, 192) , RGB(0, 103, 192) , RGB(51, 133, 204) };
};
//��ק��
class SeekBar
{
public:
	SeekBar() {};
	//[=======(O)------]
	//���Ͻ�X���꣬���Ͻ�Y���꣬��ȣ��߶ȣ�Բ�ΰ�ť������뾶���м䲿�ֺ����ľ���
	SeekBar(int, int, int, int, int, int);
	//���Ͻ�X���꣬���Ͻ�Y���꣬��ȣ��߶ȣ�Բ�ΰ�ť������뾶���м䲿�ֺ����ľ��룬��۽ṹ��
	SeekBar(int, int, int, int, int, int, SeekBarStyle);
	//������ק����۽ṹ��
	void SetStyle(ButtonStyle);
	//ˢ����ק������Ⱦ
	//���ص�ǰ״̬
	int Flush(ExMessage);
	//�ض���ť����Ⱦ���������ΪNULL��ʹ��Ĭ��
	//��������ֵvoid������int������Ϊ��ǰ״̬�͵�ǰ��ק���ȣ����/�·���
	void RedirectRenderFunction(void (*)(int, int));
	//���õ���ק�������������ΪNULL��ʹ��
	// ��������ֵvoid������int������Ϊ��ǰ״̬�͵�ǰ��ק���ȣ����/�·���
	void SetUIMsgProc(void (*)(int, int));
	//���õ�ǰ��ק���ȣ����/�·���
	void SetLength(std::wstring);
	//����������ק��λ��
	void Reset(int, int, int, int, int, int);
private:
	int X, Y, Width, Height, Radius, EdgeWidth; //��С
	int LeftLine = RGB(0, 103, 192), RightLine = RGB(127, 127, 127), ButtonEdgeColor = RGB(254, 254, 255), ButtonColor = RGB(0, 103, 192); //��ǰ��ɫ
	SeekBarStyle Style; //��۽ṹ��
	void (*RedirectRender) (int, int) = NULL, (*MsgProc) (int, int) = NULL; //�Զ�����Ⱦ��������Ϣ������
	bool IsOnClick = false; //�Ƿ����ڱ��϶�

	void Render(int);
};
