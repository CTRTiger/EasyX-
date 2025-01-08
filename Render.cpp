#include "Render.h"

// ����͸��ͼƬ
void PutTransparentImage(IMAGE* src_image, int x, int y, IMAGE* dst_image = NULL) 
{
    // ��ʼ������
    const int src_width = src_image->getwidth();
    const int src_height = src_image->getheight();
    const int dst_width = (dst_image == NULL ? getwidth() : dst_image->getwidth());
    const int dst_height = (dst_image == NULL ? getheight() : dst_image->getheight());

    DWORD* dst_buffer = GetImageBuffer(dst_image);
    DWORD* src_buffer = GetImageBuffer(src_image);

    // �������߽�����
    if (x < 0)
    {
        src_buffer -= x;
        x = 0;
    }
    if (y < 0) 
    {
        src_buffer -= src_width * y;
        y = 0;
    }
    const int max_width = dst_width - x;
    const int max_height = dst_height - y;
    const int iwidth = (src_width > max_width) ? max_width : src_width;
    const int iheight = (src_height > max_height) ? max_height : src_height;

    // ͸���Ȼ�ϼ���
    for (int iy = 0; iy < iheight; ++iy) 
    {
        DWORD* dst = dst_buffer + dst_width * (y + iy) + x;
        DWORD* src = src_buffer + src_width * iy;
        for (int ix = 0; ix < iwidth; ++ix) 
        {
            const DWORD src_pixel = *src++;
            const int sa = (src_pixel >> 24) & 0xFF;
            if (sa == 0)
                continue;
            else if (sa == 255) 
            {
                *dst = src_pixel;
            } 
            else 
            {
                const int da = ((*dst >> 24) * (255 - sa) + 128) / 255;
                const int dr = ((*dst >> 16 & 0xFF) * da + 128) / 255 + ((src_pixel >> 16 & 0xFF) * sa + 128) / 255;
                const int dg = ((*dst >> 8 & 0xFF) * da + 128) / 255 + ((src_pixel >> 8 & 0xFF) * sa + 128) / 255;
                const int db = ((*dst & 0xFF) * da + 128) / 255 + ((src_pixel & 0xFF) * sa + 128) / 255;
                *dst = (da << 24) | (dr << 16) | (dg << 8) | db;
            }
            ++dst;
        }
    }
}
void PutTransparentImage(IMAGE* srcimg, int x, int y, UINT saadd, IMAGE* dstimg) 
{
if (saadd < 0) return;
// ������ʼ��
DWORD* dst = GetImageBuffer(dstimg);
DWORD* src = GetImageBuffer(srcimg);
int src_width = srcimg->getwidth();
int src_height = srcimg->getheight();
int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());
// ������ͼ��ʵ�ʳ���
int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width; // �������ұ߽�
int iheight = (y + src_height > dst_height) ? dst_height - y : src_height; // �������±߽�
if (x < 0) { src += -x; iwidth -= -x; x = 0; } // ��������߽�
if (y < 0) { src += src_width * -y; iheight -= -y; y = 0; } // �������ϱ߽�
// ������ͼ��ʼλ��
dst += dst_width * y + x;
// ������ֵ
int sa;
// ʵ��͸����ͼ
for (int iy = 0; iy < iheight; ++iy) {
for (int i = 0; i < iwidth; ++i) {
sa = ((src[i] & 0xff000000) >> 24) + saadd; //��ȡ������ֵ
if (sa > 0) { //��������ȫ͸���Ͳ�����
if (sa >= 255) { //������ȫ��͸����ֱ�ӿ���
dst[i] = src[i];
} else { //������Ҫ��������ϼ����ͼ��߽�Ž��л��
int isrc_r = (src[i] & 0xff0000) >> 16;
int idst_r = (dst[i] & 0xff0000) >> 16;
int isrc_g = (src[i] & 0xff00) >> 8;
int idst_g = (dst[i] & 0xff00) >> 8;
int isrc_b = src[i] & 0xff;
int idst_b = dst[i] & 0xff;
int ialpha = 255 - sa;
dst[i] = ((isrc_r * sa + idst_r * ialpha) / 255 << 16) |
((isrc_g * sa + idst_g * ialpha) / 255 << 8) |
((isrc_b * sa + idst_b * ialpha) / 255);
}
}
}
dst += dst_width;
src += src_width;
}
}
IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor)
{
	radian = -radian;														// ���� y �ᷭת����ת�Ƕ���Ҫ�为
	double fSin = (double)sin(radian), fCos = (double)cos(radian);				// �洢���Ǻ���ֵ
	double fNSin = (double)sin(-radian), fNCos = (double)cos(-radian);
	int left = 0, top = 0, right = 0, bottom = 0;							// ��ת��ͼ�񶥵�
	int w = pImg->getwidth(), h = pImg->getheight();
	DWORD* pBuf = GetImageBuffer(pImg);
	POINT points[4] = { { 0, 0 },{ w, 0 },{ 0, h },{ w, h } };				// �洢ͼ�񶥵�
	for (int j = 0; j < 4; ++j)												// ��תͼ�񶥵㣬������ת���ͼ��߽�
	{
		points[j] = {
			(int)(points[j].x * fCos - points[j].y * fSin),
			(int)(points[j].x * fSin + points[j].y * fCos)
		};
		if (points[j].x < points[left].x)	left = j;
		if (points[j].y > points[top].y)	top = j;
		if (points[j].x > points[right].x)	right = j;
		if (points[j].y < points[bottom].y)	bottom = j;
	}

	int nw = points[right].x - points[left].x;								// ��ת���ͼ��ߴ�
	int nh = points[top].y - points[bottom].y;
	int nSize = nw * nh;
	int offset_x = points[left].x < 0 ? points[left].x : 0;					// ��ת��ͼ�񳬳���һ���޵�λ�ƣ��ݴ˵���ͼ��λ�ã�
	int offset_y = points[bottom].y < 0 ? points[bottom].y : 0;

	IMAGE img(nw, nh);
	DWORD* pNewBuf = GetImageBuffer(&img);
	if (bkcolor != BLACK)													// ����ͼ�񱳾�ɫ
		for (int i = 0; i < nSize; i++)
			pNewBuf[i] = BGR(bkcolor);

	for (int i = offset_x, ni = 0; ni < nw; ++i, ++ni)						// i ����ӳ��ԭͼ�����꣬ni ���ڶ�λ��ת��ͼ������
	{
		for (int j = offset_y, nj = 0; nj < nh; ++j, ++nj)
		{
			int nx = (int)(i * fNCos - j * fNSin);							// ����ת���ͼ��������ԭͼ������ӳ��
			int ny = (int)(i * fNSin + j * fNCos);
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)						// ��Ŀ��ӳ����ԭͼ��Χ�ڣ��򿽱�ɫֵ
				pNewBuf[nj * nw + ni] = pBuf[ny * w + nx];
		}
	}

	return img;
}
IMAGE ZoomImage(IMAGE* srcimg, int width, int height)
{
	// ��ʼ����ͼ
	IMAGE dstImage(width, height);
	IMAGE* dstimg = &dstImage;

	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);

	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();

	int dst_width = (!dstimg ? getwidth() : dstimg->getwidth());

	double w_scale_rate = (double)src_width / width;
	double h_scale_rate = (double)src_height / height;

	DWORD* p = src;
	int psc_width = srcimg->getwidth();

	for (int iy = 0; iy < height; ++iy)
	{
		for (int ix = 0; ix < width; ++ix)
		{
			// ����ԭͼ��Ӧ����
			int i_scale = (int)(h_scale_rate * iy);
			int j_scale = (int)(w_scale_rate * ix);
			DWORD* pp = p;
			for (int iy = 0; iy < i_scale; ++iy)
			{
				pp += psc_width;
			}
			dst[ix] = pp[j_scale];
		}
		dst += dst_width;
		src += src_width;
	}

	return dstImage;
}
void ZoomImage(IMAGE* TargetImage, IMAGE* SourceImage, int TargetWidth, int TargetHeight)
{
	TargetImage->Resize(TargetWidth, TargetHeight);
	HDC TargetDC = GetImageHDC(TargetImage);
	HDC SourceDC = GetImageHDC(SourceImage);
	int Width = SourceImage->getwidth();
	int Height = SourceImage->getheight();

	SetStretchBltMode(TargetDC, HALFTONE);
	StretchBlt(TargetDC, 0, 0, TargetWidth, TargetHeight, SourceDC, 0, 0, Width, Height, SRCCOPY);
}

//��ͼ
void PutPixel(int x, int y, COLORREF c)
{
	GetImageBuffer()[y * getwidth() + x] = BGR(c);
}
COLORREF GetPixel(int x, int y)
{
	return BGR(GetImageBuffer()[y * getwidth() + x]);
}

