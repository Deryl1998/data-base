#include "cmain.h"
wxListCtrl* frame_2::lista;
wxListCtrl* frame_3::lista;
wxListCtrl* frame_4::lista;
wxListCtrl* frame_5::lista;
wxFile* cmain::file;
long int window_3::edit_index;
wxButton* window_1:: button;
wxWindow* cmain::window[4];
wxFrame* cmain::okno;
wxBEGIN_EVENT_TABLE(cmain, wxFrame)
EVT_BUTTON(1, m_button_action_1)
EVT_BUTTON(2, m_button_action_2)
EVT_BUTTON(3, m_button_action_3)
EVT_BUTTON(4, m_button_action_4)
EVT_BUTTON(5, m_button_action_5)
EVT_BUTTON(6, m_button_action_6)
wxEND_EVENT_TABLE() 


cmain::cmain() : wxFrame(nullptr, wxID_ANY, "Okno", wxPoint(60, 20), wxSize(600, 1000), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER|wxMAXIMIZE_BOX))
{
	wxColour color(205, 229, 255), color2(162, 199, 215);
	this->SetBackgroundColour(color);
	file = new wxFile();
	m_button[0] = new wxButton(this, 1, "Dodawanie", wxPoint(60, 50), wxSize(140, 100));
	m_button[1] = new wxButton(this, 2, "Wyszukiwanie", wxPoint(200, 50), wxSize(140, 100));
	m_button[2] = new wxButton(this, 3, "Edytowanie", wxPoint(60, 150), wxSize(140, 100));
	m_button[3] = new wxButton(this, 4, "Dodatkowe", wxPoint(200, 150), wxSize(140, 100));
	m_button[4] = new wxButton(this, 5, "Zapisz do pliku", wxPoint(340, 150), wxSize(180, 100));
	m_button[5] = new wxButton(this, 6, "Wczytaj baze", wxPoint(340, 50), wxSize(180, 100));
	for (int i = 0; i < 6; i++)
	{
		m_button[i]->SetBackgroundColour(color2);
	}
	//wxPanel* mainPane = new wxPanel(this, 99, wxPoint(200, 60), wxSize(1980,1080), wxWANTS_CHARS);
	//mainPane->Bind(wxEVT_CHAR_HOOK, &cmain::close, this);
	okno = new frame_2(this);
	okno->Show();
	window[0] = new window_1(this);
	window[1] = new window_2(this); window[1]->Hide();
	window[2] = new window_3(this); window[2]->Hide();
	window[3] = new window_4(this); window[3]->Hide();
	window_3::edit_index = -1;

}



cmain::~cmain()
{
	
}

void cmain::close(wxKeyEvent& event)
{
	if ((int)event.GetKeyCode() == 27)
	{
		this->Destroy();
	}
	return;
}


void cmain::m_button_action_1(wxCommandEvent& evt)
{
	for (int i = 0; i < 4; i++)
	{
		if(this->window[i]->IsShown() ) this->window[i]->Hide();
	}
	this->window[0]->Show();
	window_3::edit_index = -1;
	window_1::button->SetLabelText("Dodaj");
	evt.Skip();
}

void cmain::m_button_action_2(wxCommandEvent& evt)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->window[i]->IsShown()) this->window[i]->Hide();
	}
	this->window[1]->Show();
	window_3::edit_index = -1;
	window_1::button->SetLabelText("Dodaj");
	evt.Skip();
}

void cmain::m_button_action_3(wxCommandEvent& evt)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->window[i]->IsShown()) this->window[i]->Hide();
	}
	this->window[2]->Show();
	window_3::edit_index = -1;
	window_1::button->SetLabelText("Dodaj");
	evt.Skip();
}

void cmain::m_button_action_4(wxCommandEvent& evt)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->window[i]->IsShown()) this->window[i]->Hide();
	}
	this->window[3]->Show();
	window_3::edit_index = -1;
	window_1::button->SetLabelText("Dodaj");
	evt.Skip();
}

void cmain::m_button_action_5(wxCommandEvent& evt)  // SAVE FILE 
{
	long x = frame_2::lista->GetItemCount() - 1;
	if (x < 0) { wxMessageBox("Baza jest pusta"); return; }

	file->Create("Fiery_Bull_base", true, wxS_DEFAULT);
	long int max = frame_2::lista->GetItemCount() + 1;
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."),
		wxT("Trwa zapysywanie bazy..."), max, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	for (int i = 0; i < max-1; i++) 
	{
		if (i % 1000) dialog->Update(i);
		for (int j = 0; j < 9; j++)
		{
			file->Write(frame_2::lista->GetItemText(i, j),15);
		}
	}
	dialog->Update(max);
	delete dialog;
	file->Close();
	evt.Skip();
}

void cmain::m_button_action_6(wxCommandEvent& evt)
{
	if (file->Access("Fiery_Bull_base", wxFile::read) == false)
	{
		file->Close();
		wxMessageBox("Nie znaleziono pliku");
		evt.Skip(); return;
	}

	file->Open("Fiery_Bull_base", wxFile::read);
	this->Freeze();
	okno->Freeze();
	long itemIndex;
	file->Length();
	frame_2::lista->DeleteAllItems();
	long int max = ( file->Length() /15)/9;
	char* file_buff = new char[15];
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), 
	wxT("Trwa wczytywanie bazy..."), max, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);

	for (int i = 0; i < max; i++)
	{
		if (i % 1000) dialog->Update(i);
		itemIndex = frame_2::lista->InsertItem(i, "");
		for (int j = 0; j < 9; j++)
		{
			file->Read(file_buff, 15);
			frame_2::lista->SetItem(itemIndex, j, file_buff);
		}
	}
	dialog->Update(max);
	delete dialog;
	file->Close();
	this->Thaw();
	okno->Thaw();
	evt.Skip();
}


wxBEGIN_EVENT_TABLE(frame_2, wxFrame)
EVT_LIST_COL_CLICK(100, sorting)
wxEND_EVENT_TABLE()

void frame_2::sorting(wxListEvent& evt)
{
	cmain::okno->Freeze();
	cmain::okno->GetParent()->Freeze();
	lista->Freeze();
	Heap_Sort x;
	x.heapSort(lista->GetItemCount()-1, evt.GetColumn(),*lista , this);
	cmain::okno->GetParent()->Thaw();
	lista->Thaw();
	cmain::okno->Thaw();
}



frame_2::~frame_2()
{
	lista->DeleteAllItems();
	delete[] lista;
}

void frame_2::add_list(struktura s, long int i , wxListCtrl *l)
{
	wxString id;
	long itemIndex;
	if (window_3::edit_index == -1)
	{
		if (s.lp.IsEmpty()) id = wxString(to_string(i));
		else id = s.lp;
		itemIndex = l->InsertItem(i - 1, ""); 
	}
	else
	{
		id = wxString(to_string(i + 1));
		itemIndex = i; 
	}
	l->SetItem(itemIndex, 1, s.Imie);		l->SetItem(itemIndex, 0, id );
	l->SetItem(itemIndex, 2, s.Nazwisko);	l->SetItem(itemIndex, 3, s.Miejscowosc);
	l->SetItem(itemIndex, 4, s.Ulica);		l->SetItem(itemIndex, 5, s.Kod);
	l->SetItem(itemIndex, 6, s.przedmiot);	l->SetItem(itemIndex, 7, s.netto);
	l->SetItem(itemIndex, 8, s.brutto);
	return;
}



frame_2::frame_2(wxFrame* okno) : wxFrame(okno, wxID_ANY, "Baza Klientów", wxPoint(660, 20), wxSize(1200, 1000), wxDEFAULT_FRAME_STYLE & ~(wxCLOSE_BOX))
{
	
	wxPanel* mainPane = new wxPanel(this);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	lista = new wxListCtrl(mainPane, 100,wxPoint(60, 60), wxSize(1000, 800), wxLC_REPORT);
	wxColour color2(100, 189, 225);
	wxListItem col;
	col.SetId(0); col.SetText(_("LP")); col.SetWidth(50); lista->InsertColumn(0, col);
	lista->SetBackgroundColour(color2); 
	col.SetId(1); col.SetText(_("Imie")); col.SetWidth(150); lista->InsertColumn(1, col); 
	col.SetId(2); col.SetText(_("Nazwisko")); col.SetWidth(150); lista->InsertColumn(2, col);
	col.SetId(3); col.SetText(_("Miejscowosc")); col.SetWidth(150); lista->InsertColumn(3, col); 
	col.SetId(4); col.SetText(_("Ulica")); col.SetWidth(150); lista->InsertColumn(4, col); 
	col.SetId(5); col.SetText(_("Kod pocztowy")); col.SetWidth(150); lista->InsertColumn(5, col); 
	col.SetId(6); col.SetText(_("Zakupiony Przedmiot")); col.SetWidth(150); lista->InsertColumn(6, col); 
	col.SetId(7); col.SetText(_("Cena Netto")); col.SetWidth(100); lista->InsertColumn(7, col); 
	col.SetId(8); col.SetText(_("Cena Brutto")); col.SetWidth(120); lista->InsertColumn(8, col); 
	sizer->Add(lista,1, wxEXPAND | wxALL, 5);
	mainPane->SetSizer(sizer); 
}

frame_3::frame_3(wxFrame* okno) : wxFrame(okno, wxID_ANY, "Wyszukiwanie", wxPoint(660, 120), wxSize(1200, 800), wxDEFAULT_FRAME_STYLE )
{
	wxPanel* mainPane = new wxPanel(this);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	lista = new wxListCtrl(mainPane, 100, wxPoint(60, 60), wxSize(1000, 800), wxLC_REPORT);
	wxColour color2(80, 150, 225);
	wxListItem col;
	col.SetId(0); col.SetText(_("LP")); col.SetWidth(50); lista->InsertColumn(0, col);
	lista->SetBackgroundColour(color2);
	col.SetId(1); col.SetText(_("Imie")); col.SetWidth(150); lista->InsertColumn(1, col);
	col.SetId(2); col.SetText(_("Nazwisko")); col.SetWidth(150); lista->InsertColumn(2, col);
	col.SetId(3); col.SetText(_("Miejscowosc")); col.SetWidth(150); lista->InsertColumn(3, col);
	col.SetId(4); col.SetText(_("Ulica")); col.SetWidth(150); lista->InsertColumn(4, col);
	col.SetId(5); col.SetText(_("Kod pocztowy")); col.SetWidth(150); lista->InsertColumn(5, col);
	col.SetId(6); col.SetText(_("Zakupiony Przedmiot")); col.SetWidth(150); lista->InsertColumn(6, col);
	col.SetId(7); col.SetText(_("Cena Netto")); col.SetWidth(100); lista->InsertColumn(7, col);
	col.SetId(8); col.SetText(_("Cena Brutto")); col.SetWidth(120); lista->InsertColumn(8, col);
	sizer->Add(lista, 1, wxEXPAND | wxALL, 5);
	mainPane->SetSizer(sizer);
}

frame_3::~frame_3()
{
	if(this->GetParent()->IsFrozen())  this->GetParent()->Thaw();
}

frame_4::frame_4(wxFrame* okno) : wxFrame(okno, wxID_ANY, "³ancuchy", wxPoint(660, 120), wxSize(1200, 800), wxDEFAULT_FRAME_STYLE)
{
	wxPanel* mainPane = new wxPanel(this);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	lista = new wxListCtrl(mainPane, 100, wxPoint(60, 60), wxSize(1000, 800), wxLC_REPORT);
	wxColour color2(100, 150, 225);
	wxListItem col;
	col.SetId(0); col.SetText(_("LP")); col.SetWidth(50); lista->InsertColumn(0, col);
	lista->SetBackgroundColour(color2);
	col.SetId(1); col.SetText(_("Imie")); col.SetWidth(150); lista->InsertColumn(1, col);
	col.SetId(2); col.SetText(_("Nazwisko")); col.SetWidth(150); lista->InsertColumn(2, col);
	col.SetId(3); col.SetText(_("Miejscowosc")); col.SetWidth(150); lista->InsertColumn(3, col);
	col.SetId(4); col.SetText(_("Ulica")); col.SetWidth(150); lista->InsertColumn(4, col);
	col.SetId(5); col.SetText(_("Kod pocztowy")); col.SetWidth(150); lista->InsertColumn(5, col);
	col.SetId(6); col.SetText(_("Zakupiony Przedmiot")); col.SetWidth(150); lista->InsertColumn(6, col);
	col.SetId(7); col.SetText(_("Cena Netto")); col.SetWidth(100); lista->InsertColumn(7, col);
	col.SetId(8); col.SetText(_("Cena Brutto")); col.SetWidth(120); lista->InsertColumn(8, col);
	sizer->Add(lista, 1, wxEXPAND | wxALL, 5);
	mainPane->SetSizer(sizer);
}

frame_4::~frame_4()
{
	if (this->GetParent()->IsFrozen())  this->GetParent()->Thaw();
}


frame_5::frame_5(wxFrame* okno) : wxFrame(okno, wxID_ANY, "Pomocna", wxPoint(660, 120), wxSize(1200, 800), wxDEFAULT_FRAME_STYLE)
{
	wxPanel* mainPane = new wxPanel(this);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	lista = new wxListCtrl(mainPane, 100, wxPoint(60, 60), wxSize(1000, 800), wxLC_REPORT);
	wxColour color2(120, 140, 225);
	wxListItem col;
	col.SetId(0); col.SetText(_("LP")); col.SetWidth(50); lista->InsertColumn(0, col);
	lista->SetBackgroundColour(color2);
	col.SetId(1); col.SetText(_("Imie")); col.SetWidth(120); lista->InsertColumn(1, col);
	col.SetId(2); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(2, col);
	col.SetId(3); col.SetText(_("Nazwisko")); col.SetWidth(120); lista->InsertColumn(3, col);
	col.SetId(4); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(4, col);
	col.SetId(5); col.SetText(_("Miejscowosc")); col.SetWidth(120); lista->InsertColumn(5, col);
	col.SetId(6); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(6, col);
	col.SetId(7); col.SetText(_("Ulica")); col.SetWidth(120); lista->InsertColumn(7, col);
	col.SetId(8); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(8, col);
	col.SetId(5); col.SetText(_("Kod pocztowy")); col.SetWidth(120); lista->InsertColumn(9, col);
	col.SetId(10); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(10, col);
	col.SetId(11); col.SetText(_("Zakupiony Przedmiot")); col.SetWidth(120); lista->InsertColumn(11, col);
	col.SetId(12); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(12, col);
	col.SetId(13); col.SetText(_("Cena Netto")); col.SetWidth(100); lista->InsertColumn(13, col);
	col.SetId(14); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(14, col);
	col.SetId(15); col.SetText(_("Cena Brutto")); col.SetWidth(100); lista->InsertColumn(15, col);
	col.SetId(16); col.SetText(_("index")); col.SetWidth(60); lista->InsertColumn(16, col);
	sizer->Add(lista, 1, wxEXPAND | wxALL, 5);
	mainPane->SetSizer(sizer);
}

frame_5::~frame_5()
{
	if (this->GetParent()->IsFrozen())  this->GetParent()->Thaw();
	lista->DeleteAllItems();
	delete[] lista;
}

