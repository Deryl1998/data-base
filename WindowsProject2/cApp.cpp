#include "cApp.h"
wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()  // START PROGRAM
{
	m_frame1 = new cmain();
	m_frame1->Show();
	return 1;
}

