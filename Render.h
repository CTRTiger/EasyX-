/*
2023/1/30
�����йص�����

�����error C4716�����ڡ����ԡ���C/C++�����߼����������ض����桱����ӡ�4716��
*/
#pragma once
#include "Header.h"

//ͼƬ
//͸����ͼ https://codebus.cn/lingyin/improve-transparent-putimage
//srcimg��Դͼ dstimg��Ŀ��ͼ 
void PutTransparentImage(IMAGE* srcimg, int, int, IMAGE*);
//����͸��ֵ https://codebus.cn/lingyin/improve-transparent-putimage
//srcimg��Դͼ saadd������͸���� dstimg��Ŀ��ͼ 
void PutTransparentImage(IMAGE* srcimg, int x, int y, UINT saadd, IMAGE* dstimg = NULL);
//��תͼƬ��ָ���������ɫ������Ӧ��С https://codebus.cn/huidong/hieasyx
//����Ŀ��ͼ pImg��Դͼ randian���Ƕ� bkcolor�����������ɫ
IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor = BLACK);
//����ͼƬ https://codebus.cn/huidong/hieasyx
//����Ŀ��ͼ srcimg��Դͼ 
IMAGE ZoomImage(IMAGE* srcimg, int width, int height);
//����������ͼƬ https://codebus.cn/margoo/anti-aliasing
//TargetImage��Ŀ��ͼ SourceImage��Դͼ TargetWidth��Ŀ���� TargetHeight��Ŀ��߶�
void ZoomImage(IMAGE* TargetImage, IMAGE* SourceImage, int TargetWidth, int TargetHeight);

//��ͼ
//���ٻ��㺯�� https://codebus.cn/yangw/fast-putpixel
void PutPixel(int x, int y, COLORREF c);
//�������� ���ٶ��㺯�� https://codebus.cn/yangw/fast-putpixel
COLORREF GetPixel(int x, int y);
