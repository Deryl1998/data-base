#pragma once
#include "wx/wx.h"
#include "string.h"
#include "window.h"
#include "Heap_Sort.h"
#include <wx/listctrl.h>
#include <wx/file.h>
#include <wx/progdlg.h>
#include <wx/listctrl.h>
using namespace std;

struct struktura
{
	wxString lp;
	wxString Imie;
	wxString Nazwisko;
	wxString Miejscowosc;
	wxString Ulica;
	wxString Kod;
	wxString przedmiot;
	wxString netto;
	wxString brutto;
};

class cmain : public wxFrame    // MAIN FRAME
{

public:
	cmain();
	~cmain();
public:
	static wxFile* file;
	static wxFrame* okno;
	static wxWindow* window[4]; 
	wxButton *m_button[6];
	void m_button_action_1(wxCommandEvent& evt);
	void m_button_action_2(wxCommandEvent& evt);
	void m_button_action_3(wxCommandEvent& evt);
	void m_button_action_4(wxCommandEvent& evt);
	void m_button_action_5(wxCommandEvent& evt);
	void m_button_action_6(wxCommandEvent& evt);
	void close(wxKeyEvent& event);
	wxDECLARE_EVENT_TABLE();
};


class frame_2 : public wxFrame  // BASE - FRAME
{
public:
void sorting(wxListEvent& evt);
static wxListCtrl* lista;
static void add_list(struktura s,long i, wxListCtrl* l);
frame_2(wxFrame*okno);
~frame_2();
wxDECLARE_EVENT_TABLE();
};

class frame_3 : public wxFrame  // FIND - FRAME
{
public:
	static wxListCtrl* lista;
	frame_3(wxFrame* okno);
	~frame_3();
};

class frame_4 : public wxFrame  // lancuch - FRAME
{
public:
	static wxListCtrl* lista;
	frame_4(wxFrame* okno);
	~frame_4();
};

class frame_5 : public wxFrame  // pomocna - FRAME
{
public:
	static wxListCtrl* lista;
	frame_5(wxFrame* okno);
	~frame_5();
};
