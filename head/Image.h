#pragma once
#include "UIElement.h"
class Image : public UIElement
{
	//-------------基类公有成员变量
	// 位置position
	// 缩放scale
	// 宽度width
	// 高度height
	//------------
private:
	LPCTSTR imgsrcpath; // 绑定的图片资源文件路径
	IMAGE *srcimg;		// 图片文件指针
	bool issrc = true;
	float realwidth;
	float realheight;

public:
	Image(const char path[], float x = 0, float y = 0, float width = 0, float height = 0);
	Image(const char path[], Vector2 position, float width = 0, float height = 0);
	Image(IMAGE &src, float x = 0, float y = 0, float width = 0, float height = 0);
	Image(IMAGE &src, Vector2 position, float width = 0, float height = 0);
	void Resize(float width, float height);			   // 重设宽度高度
	void Setscale(float scalex = 1, float scaley = 1); // 设置缩放
	void SetisSrc(bool issrc);
	void Draw(Vector2 pagepos); // 绘制图片
};
Image::Image(const char path[], float x, float y, float width, float height)
{
	position.x = x;
	position.y = y;
	imgsrcpath = (LPCTSTR)path;
	srcimg = new IMAGE;
	if (width == 0 || height == 0)
	{
		loadimage(srcimg, imgsrcpath);
		this->width = srcimg->getwidth();
		this->height = srcimg->getheight();
	}
	else
	{
		loadimage(srcimg, imgsrcpath, width, height);
		this->width = width;
		this->height = height;
	}
	realwidth = this->width;
	realheight = this->height;
}
Image::Image(const char path[], Vector2 position, float width, float height) : Image(path, position.x, position.y, width, height)
{
}
Image::Image(IMAGE &src, float x, float y, float width, float height)
{
	imgsrcpath = NULL;
	this->srcimg = &src;
	position.x = x;
	position.y = y;
	if (width == 0 || height == 0)
	{
		this->width = srcimg->getwidth();
		this->height = srcimg->getheight();
	}
	else
	{
		this->width = width;
		this->height = height;
	}
	realwidth = this->width;
	realheight = this->height;
}
Image::Image(IMAGE &src, Vector2 position, float width, float height) : Image(src, position.x, position.y, width, height)
{
}
void Image::Resize(float width, float height)
{
	this->width = width;
	this->height = height;
	realwidth = this->width * scale.x;
	realheight = this->height * scale.y;
	srcimg->Resize(realwidth, realheight);
}
void Image::Setscale(float scalex, float scaley)
{
	scale.x = scalex;
	scale.y = scaley;
	realwidth = this->width * scale.x;
	realheight = this->height * scale.y;
	srcimg->Resize(realwidth, realheight);
}
inline void Image::SetisSrc(bool issrc)
{
	this->issrc = issrc;
}
void Image::Draw(Vector2 pagepos)
{
	// 这里的real指的是easyx的坐标系下的坐标
	float realx = position.x + pagepos.x - srcimg->getwidth() / 2;
	float realy = position.y + pagepos.y - srcimg->getheight() / 2;
	if (issrc)
	{
		putimage(srcimg, realx, realy);//透明背景图
	}
	else
		putimage(realx, realy, srcimg);
}