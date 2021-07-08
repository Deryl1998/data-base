#pragma once
#include "wx/wx.h"
#include "string.h"
#include "cmain.h"
#include <iostream>
#include <wx/listimpl.cpp>
#include <wx/wx.h>
#include <wx/progdlg.h>
#include <stdlib.h>     
#include <cstring>
#include <wx/listctrl.h>
class Heap_Sort
{
	public:
		struct strc
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

		 strc S;
		 int column;
		 bool is_char;
		 int x;
		 void swap(int index_1, int index_2, wxListCtrl &lista);
		 void heapify(int n, int i, wxListCtrl &lista);
		 void heapSort(int n, int number_of_column, wxListCtrl &lista, wxWindow* okno);

};

