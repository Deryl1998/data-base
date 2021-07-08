#pragma once
#include "wx/wx.h"
#include "cmain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
private:
	cmain* m_frame1 = nullptr;
public:
	bool OnInit();
};