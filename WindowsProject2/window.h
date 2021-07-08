#pragma once
#include "wx/wx.h"
#include "string.h"
#include "cmain.h"
#include <iostream>
#include <wx/listimpl.cpp>
#include <wx/regex.h>
#include <wx/wx.h>
#include <wx/progdlg.h>
#include <stdlib.h>     
#include <cstring>


class window_1 : public wxWindow // ADD TO BASE
{
public:
	friend class window_3;
	window_1(wxWindow* okno);
	wxWindow* base_win;
	wxTextCtrl* text_box[8];
	wxStaticText* box_labels[8];
	 static wxButton* button;
	void button_action(wxCommandEvent& evt);   
};


class window_2 : public wxWindow    // FIND 
{
public:
	wxFrame* okno2 = NULL;
	wxFrame* okno3 = NULL;
	wxFrame* okno4 = NULL;
	wxRadioBox*choice;
	window_2(wxFrame* okno);
	wxFrame* x;
	wxTextCtrl* text_box;
	wxStaticText* box_labels;
	wxButton* button;
	wxButton* button2;
	wxButton* button_lancuchowe;
	wxButton* button_inwersyjne;
	void find(int i, int column, wxString txt_box);
	void search(wxCommandEvent& evt);   
	void jump(wxCommandEvent& evt); 
	void lancuchowe(wxCommandEvent& evt);
	void inwersyjne(wxCommandEvent& evt);
	void sortowanie();
	void binarne(wxCommandEvent& evt);
};

class window_3 : public wxWindow      // EDIT / DELETE BASE 
{
public:
	window_3(wxWindow* okno);
	static long int edit_index;
	wxTextCtrl* text_box;
	wxStaticText* box_labels;
	wxButton* button[2];
	void edit(wxCommandEvent& evt);
	void delete_line(wxCommandEvent& evt);
};

class window_4 : public wxWindow       // GENERATE CUSTOM BASE
{
public:
	window_4(wxWindow* okno);
	wxWindow* main_window;
	wxTextCtrl* text_box;
	wxStaticText* box_labels[2];
	wxButton* button[2];
	void button_generate(wxCommandEvent& evt);     
	void base_delete(wxCommandEvent& evt);
};

