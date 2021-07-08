#include "window.h"
#include <random>
#include <algorithm>
using namespace std;
random_device rd;  
mt19937 gen(rd());

template<typename T>
T random(T min, T max) 
{
	return std::uniform_int_distribution<T>{min, max}(gen);
}

wxRegEx numbers("^[1-9]{1,1}[0-9]{0,6}[,]?[0-9]{0,2}$");
wxRegEx numbers2("^[1-9]{1,1}[0-9]{0,7}$");
wxRegEx post_number("^[1-9]{1,1}[0-9]{1,1}[-]{1,1}[0-9]{3,3}$");
wxRegEx words("^[A-Z]?[a-z]{2,10}$|^[A-Z]?[a-z]{2,10}[[:space:]]?[A-Z]?[a-z]{2,8}$");
wxRegEx surname("^[A-Z]{1,1}[a-z]{2,10}$");
wxRegEx street("^[A-Z]{1,1}[a-z]{2,11}$");



void czas_message(int czas,wxWindow *okno)
{
	wxMessageBox("Zmierzony czas : "+ to_string(czas)+" ms"+"  ||  " + to_string(czas / 1000)+" sekund", "Pomiar", wxOK, okno);
}

window_1::window_1(wxWindow* okno) : wxWindow(okno, wxID_ANY, wxPoint(20, 350), wxSize(545, 600))
{
	base_win = okno;
	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD, false);
	wxFont font_box(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false);
	wxColour color(80, 150, 250);
	this->SetBackgroundColour(color);
	box_labels[0] = new wxStaticText(this,wxID_ANY, "Imie", wxPoint(70, 40), wxSize(150, 45));
	box_labels[1] = new wxStaticText(this,wxID_ANY, "Nazwisko", wxPoint(70, 100), wxSize(150, 45));
	box_labels[2] = new wxStaticText(this,wxID_ANY, "Miejscowosc", wxPoint(70, 160), wxSize(150, 45));
	box_labels[3] = new wxStaticText(this,wxID_ANY, "Ulica", wxPoint(70, 220), wxSize(150, 45));
	box_labels[4] = new wxStaticText(this,wxID_ANY, "Kod Pocztowy", wxPoint(70, 280), wxSize(150, 45));
	box_labels[5] = new wxStaticText(this,wxID_ANY, "Zakupiony przedmiot", wxPoint(70, 340), wxSize(150, 45));
	box_labels[6] = new wxStaticText(this,wxID_ANY, "Cena netto", wxPoint(70, 400), wxSize(150, 45));
	box_labels[7] = new wxStaticText(this,wxID_ANY, "Cena brutto", wxPoint(70, 460), wxSize(150, 45));
	for (int i = 0; i < 8; i++)
	{
		text_box[i] = new wxTextCtrl(this, 2, "", wxPoint(330, 30 + (i * 60)), wxSize(200, 45));
		text_box[i]->SetFont(font_box);
		box_labels[i]->SetFont(font);
	}
	button = new wxButton(this, wxID_ANY, "Dodaj", wxPoint(200, 520), wxSize(100, 50));
	button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_1::button_action, this);
}

void window_1::button_action(wxCommandEvent& evt)  
{
	bool error = false;
	wxColour color(255, 77, 77); wxColour color2(255, 255, 255);
	struktura S;
	if (surname.Matches(text_box[0]->GetValue()) )
	{
		S.Imie = text_box[0]->GetValue(); text_box[0]->SetBackgroundColour(color2);
	}
		else { text_box[0]->SetBackgroundColour(color);  error = true; }

	if (surname.Matches(text_box[1]->GetValue()) )
	{
		S.Nazwisko = text_box[1]->GetValue(); text_box[1]->SetBackgroundColour(color2);
	}
		else { text_box[1]->SetBackgroundColour(color);  error = true; }

	if (words.Matches(text_box[2]->GetValue()) )
	{
		S.Miejscowosc = text_box[2]->GetValue(); text_box[2]->SetBackgroundColour(color2);
	}
		else { text_box[2]->SetBackgroundColour(color);  error = true; }

	if (street.Matches(text_box[3]->GetValue()) )
	{
		S.Ulica = text_box[3]->GetValue(); text_box[3]->SetBackgroundColour(color2);
	}
	else { text_box[3]->SetBackgroundColour(color);  error = true; }

	if (post_number.Matches(text_box[4]->GetValue()) )
	{
		S.Kod = text_box[4]->GetValue(); text_box[4]->SetBackgroundColour(color2);
	}
	else { text_box[4]->SetBackgroundColour(color);  error = true; }

	if (words.Matches(text_box[5]->GetValue()) )
	{
		S.przedmiot = text_box[5]->GetValue(); text_box[5]->SetBackgroundColour(color2);
	}
		else { text_box[5]->SetBackgroundColour(color);  error = true; }

	if (numbers.Matches(text_box[6]->GetValue()) || numbers2.Matches(text_box[6]->GetValue()))
	{
		S.netto = text_box[6]->GetValue(); text_box[6]->SetBackgroundColour(color2);
		S.netto += "zl";
	}
		else { text_box[6]->SetBackgroundColour(color);  error = true; }

	if (numbers.Matches(text_box[7]->GetValue())|| numbers2.Matches(text_box[7]->GetValue()))
	{
		S.brutto = text_box[7]->GetValue(); text_box[7]->SetBackgroundColour(color2);
		S.brutto += "zl";
	}
		else { text_box[7]->SetBackgroundColour(color);  error = true; }

	if (error == true) { this->Hide(); this->Show(); return; } 

	for (int i = 0; i < 8; i++)
	{
		text_box[i]->Clear();
	}
	if(window_3::edit_index == -1)  frame_2::add_list(S, frame_2::lista->GetItemCount() + 1, frame_2::lista);
		else frame_2::add_list(S,window_3::edit_index, frame_2::lista);
	if (window_3::edit_index != -1)
	{
		this->Hide();
		cmain::window[2]->Show();
	}
	window_3::edit_index = -1;
	evt.Skip();
	return;
}



window_2::window_2(wxFrame* okno) : wxWindow(okno, wxID_ANY, wxPoint(20, 350), wxSize(545, 600))
{
	x = okno;
	wxColour color(80, 150, 250);
	this->SetBackgroundColour(color);
	wxString tab[] = { "Lp","Imie","Nazwisko","Miejscowosc","Ulica","Kod pocztowy","Przedmiot","C.Netto","C.Brutto" };
	choice = new wxRadioBox(this, wxID_ANY,"wybierz", wxPoint(20, 120), wxSize(200, 225),9, tab,12,wxRA_SPECIFY_ROWS);
	wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD, false);
	wxFont font_box(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false);
	choice->SetFont(font_box);
	font_box.SetPointSize(24);
	box_labels = new wxStaticText(this, wxID_ANY, "Podaj dane do wyszukiwania", wxPoint(125, 50), wxSize(150, 40));
	box_labels->SetFont(font);
	text_box = new wxTextCtrl(this, 2, "", wxPoint(260, 125), wxSize(245, 45));
	text_box->SetFont(font_box);
	button = new wxButton(this, wxID_ANY, "Binarne", wxPoint(260, 190), wxSize(245, 75));
	button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_2::binarne, this);
	button->SetFont(font_box);
	button2 = new wxButton(this, wxID_ANY, "Liniowe", wxPoint(260, 275), wxSize(245, 75));
	button2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_2::search, this);
	button2->SetFont(font_box);
	button_lancuchowe = new wxButton(this, wxID_ANY, "£añcuchowe", wxPoint(20, 390), wxSize(200, 150));
	button_lancuchowe->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_2::lancuchowe, this);
	button_lancuchowe->SetFont(font_box);
	button_inwersyjne = new wxButton(this, wxID_ANY, "Inwersyjne", wxPoint(230, 390), wxSize(200, 150));
	button_inwersyjne->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_2::inwersyjne, this);
	button_inwersyjne->SetFont(font_box);
	okno2 = new frame_5(x); // pomocna
}

void window_2::search(wxCommandEvent& evt)
{
	if (text_box->GetValue()=="") return;
	okno2 = new frame_3(x);
	struktura S;
	frame_2::lista->ScrollList(0, -100000000);
	int column = choice->GetSelection(); 
	int i=0 , itemindex;
	this->GetParent()->Freeze();
	clock_t start = clock(); 
	for (i = 0; i < frame_2::lista->GetItemCount(); i++)
	{
		if (frame_2::lista->GetItemText(i, column) == text_box->GetValue())
		{
			S.Imie = frame_2::lista->GetItemText(i, 1);
			S.Nazwisko = frame_2::lista->GetItemText(i, 2);
			S.Ulica = frame_2::lista->GetItemText(i, 4);
			S.Kod = frame_2::lista->GetItemText(i, 5);
			S.Miejscowosc = frame_2::lista->GetItemText(i, 3);
			S.przedmiot = frame_2::lista->GetItemText(i, 6);
			S.netto = frame_2::lista->GetItemText(i, 7);
			S.brutto = frame_2::lista->GetItemText(i, 8);
			frame_2::add_list(S, i+1, frame_3::lista);
		}
	}
	okno2->Show();
	evt.Skip();
	text_box->Clear();
	czas_message(clock() - start,this);
	return;
}


void window_2::find(int i ,int column,wxString txt_box)
{
	string index;
	struktura S;
	int j = i;
	long int max = frame_2::lista->GetItemCount();
	while (frame_2::lista->GetItemText(i, column)[0] == txt_box[0])
	{
		if (txt_box == frame_2::lista->GetItemText(i, column))
		{
			S.lp = frame_2::lista->GetItemText(i, 0);
			S.Imie = frame_2::lista->GetItemText(i, 1);
			S.Nazwisko = frame_2::lista->GetItemText(i, 2);
			S.Ulica = frame_2::lista->GetItemText(i, 4);
			S.Kod = frame_2::lista->GetItemText(i, 5);
			S.Miejscowosc = frame_2::lista->GetItemText(i, 3);
			S.przedmiot = frame_2::lista->GetItemText(i, 6);
			S.netto = frame_2::lista->GetItemText(i, 7);
			S.brutto = frame_2::lista->GetItemText(i, 8);
			frame_2::add_list(S, i + 1, frame_3::lista);
		}
		i++;
		if (i > max - 1) break;
	}
	i = j - 1;
	if (i < 0) return;
	while (frame_2::lista->GetItemText(i, column)[0] == txt_box[0])
	{
		if (txt_box == frame_2::lista->GetItemText(i, column))
		{
			S.lp = frame_2::lista->GetItemText(i, 0);
			S.Imie = frame_2::lista->GetItemText(i, 1);
			S.Nazwisko = frame_2::lista->GetItemText(i, 2);
			S.Ulica = frame_2::lista->GetItemText(i, 4);
			S.Kod = frame_2::lista->GetItemText(i, 5);
			S.Miejscowosc = frame_2::lista->GetItemText(i, 3);
			S.przedmiot = frame_2::lista->GetItemText(i, 6);
			S.netto = frame_2::lista->GetItemText(i, 7);
			S.brutto = frame_2::lista->GetItemText(i, 8);
			frame_2::add_list(S, i + 1, frame_3::lista);
		}
		i--;
		if (i < 0) break;
	}
}


void window_2::binarne(wxCommandEvent& evt)
{
	{
		wxString txt_string = text_box->GetValue();
		okno2 = new frame_3(x);
		this->GetParent()->Freeze();
		int sr, l = 0, p = frame_2::lista->GetItemCount() - 1;
		int szukana,item;
		int column = choice->GetSelection();
		clock_t start = clock(); 
		if (column == 0 || column == 7 || column == 8)
		{
			if (column == 0 && numbers2.Matches(txt_string) == false) { text_box->SetValue("blad");  this->GetParent()->Thaw();  return; }
			szukana = stod(string(txt_string));
		}
		else szukana = txt_string[0];
	
		while (l <= p)
		{
			sr = (l + p) / 2;
			if (column == 0 || column == 7 || column == 8) item = stod(string(frame_2::lista->GetItemText(sr, column)));
			else item = frame_2::lista->GetItemText(sr, column)[0];
			if (item == szukana)
			{
				find(sr, column, txt_string);	
				okno2->Show();
				evt.Skip();
				text_box->Clear(); 
				czas_message(clock() - start, this);
				return;
			}
			if (item > szukana)
				p = sr - 1;
			else
				l = sr + 1;
		}

		okno2->Show();
		evt.Skip();
		text_box->Clear(); 
		czas_message(clock() - start, this);
		return ; 
	}
}


void pomocna(int col,wxWindow *okno, wxString szukana)
{
	long itemIndex;
	itemIndex = frame_5::lista->InsertItem(0, "");
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa generowanie listy pomocnej..."), frame_2::lista->GetItemCount(), okno, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	frame_5::lista->SetItem(itemIndex, 0, "1");
	frame_5::lista->SetItem(itemIndex, (col*2)-1, frame_2::lista->GetItemText(0, col));
	frame_5::lista->SetItem(itemIndex, (col*2), "0");

	for (int i = 1; i < frame_2::lista->GetItemCount(); i++)
	{
		if (i % 1000) dialog->Update(i);
		for (int j = 0; j <i; j++)
		{
			
			if (col < 7 && frame_5::lista->GetItemText(j, (col * 2) - 1) == frame_2::lista->GetItemText(i, col))
			{
				break;
			}

			if (col >= 7)
			{
				if (wxAtoi(frame_5::lista->GetItemText(j, (col * 2) - 1)) == wxAtoi(frame_2::lista->GetItemText(i, col))) break;

			}

			if (j == frame_5::lista->GetItemCount()-1)
			{
				itemIndex = frame_5::lista->InsertItem(frame_5::lista->GetItemCount(), NULL);
				frame_5::lista->SetItem(itemIndex, (col * 2)-1, frame_2::lista->GetItemText(i, col));
		
				frame_5::lista->SetItem(itemIndex, (col * 2), wxString::Format(wxT("%i"), (wxAtoi(frame_2::lista->GetItemText(i, 0)) - 1)));
				frame_5::lista->SetItem(itemIndex, 0, wxString::Format(wxT("%i"),i+1));
				break;
			}

		}
		if (szukana == frame_2::lista->GetItemText(i, col)) break;
	}
	dialog->Update(frame_2::lista->GetItemCount());
	delete dialog;
}

void lancuch(int col , wxWindow  *okno, wxString szukana)
{
	long itemIndex;
	itemIndex = frame_4::lista->InsertItem(0, "");
	frame_4::lista->SetItem(itemIndex, 0, "1");
	frame_4::lista->SetItem(itemIndex, col, "-1");
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa generowanie lancuchow..."), frame_2::lista->GetItemCount(), okno, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	int last=0;
	bool y=true;
	for (int i = 1; i < frame_2::lista->GetItemCount(); i++)
	{
		itemIndex = frame_4::lista->InsertItem(i, "");
		if (i % 1000) dialog->Update(i);
		for (int j = last; j < i; j++)
		{
			if (szukana != frame_2::lista->GetItemText(i, col)) break;
			if (frame_4::lista->GetItemText(j, col) == "-1" && frame_2::lista->GetItemText(j, col) == frame_2::lista->GetItemText(i, col))
			{
				frame_4::lista->SetItem(itemIndex, col, "-1"); last = i;
				frame_4::lista->SetItem(j, col,frame_2::lista->GetItemText(i, 0));

			}
			if (j == i - 1) { frame_4::lista->SetItem(itemIndex, col, "-1"); last = i; break; }
		}
		frame_4::lista->SetItem(itemIndex, 0, to_string(i + 1));
	
	}
	dialog->Update(frame_2::lista->GetItemCount());
	delete dialog;
}

void lancuchowe_wyszukanie(int columna ,wxString szukana)
{
	long itemIndex;
	for (int i=0;i< frame_2::lista->GetItemCount();i++)
	{
		if (frame_5::lista->GetItemText(i, (columna * 2) - 1) == szukana)
		{
			int j =wxAtoi(frame_5::lista->GetItemText(i, columna * 2));
			i = 0;
		
			while (true)
			{
				
				itemIndex = frame_3::lista->InsertItem(i, "");
				frame_3::lista->SetItem(i, 0, frame_2::lista->GetItemText(j, 0));
				frame_3::lista->SetItem(i, 1, frame_2::lista->GetItemText(j, 1));
				frame_3::lista->SetItem(i, 2, frame_2::lista->GetItemText(j, 2));
				frame_3::lista->SetItem(i, 3, frame_2::lista->GetItemText(j, 3));
				frame_3::lista->SetItem(i, 4, frame_2::lista->GetItemText(j, 4));
				frame_3::lista->SetItem(i, 5, frame_2::lista->GetItemText(j, 5));
				frame_3::lista->SetItem(i, 6, frame_2::lista->GetItemText(j, 6));
				frame_3::lista->SetItem(i, 7, frame_2::lista->GetItemText(j, 7));
				frame_3::lista->SetItem(i, 8, frame_2::lista->GetItemText(j, 8));
				j = wxAtoi(frame_4::lista->GetItemText(j, columna))-1;
				if (j == -2) return;

				i++;
			
			}
		}
	}

}


void window_2::lancuchowe(wxCommandEvent& evt)
{
	okno3 = new frame_4(x); // lancuchy
	//okno3->Show();
	//okno2->Show();
	//okno2->Freeze();
	this->GetParent()->Freeze();
	//okno3->Freeze();
	
	pomocna(choice->GetSelection(),this, text_box->GetValue());  // TWORZY TABLICE POMOCNA
	lancuch(choice->GetSelection(),this, text_box->GetValue()); // TWORZY TABLICE ³ancuchy

	okno4 = new frame_3(x); // wyniki 
	
	clock_t start = clock(); 
	lancuchowe_wyszukanie(choice->GetSelection(),text_box->GetValue());
	czas_message(clock() - start, this);

	this->GetParent()->Thaw();
	okno4->Show();
	okno4->Freeze();
	if (frame_2::lista->GetItemCount() > 100000) 
	{ 
		wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa renderowanie tablicy..."), 20000, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
		for (int i = 0; i < 20000; i++)  { if (i % 1000) dialog->Update(i); }
	okno4->Thaw(); 
	dialog->Update(20000);
	delete dialog;
	}
	else  okno4->Thaw();
}



void indexowanie_inwersyjne(int numer_kolumny,wxWindow *okno, wxString szukana)
{
	frame_4::lista->DeleteAllColumns();
	long itemIndex;
	wxListItem col;
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa generowanie listy inwersyjnej..."), frame_2::lista->GetItemCount(), okno, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	int a=1,b;
	for (int i = 0; i < frame_5::lista->GetItemCount(); i++)
	{
		if (frame_5::lista->GetItemText(i, (numer_kolumny * 2) - 1) != "")
		{
			b = wxAtoi(frame_5::lista->GetItemText(i,numer_kolumny * 2));
			col.SetId(a); col.SetText(_(frame_2::lista->GetItemText(b, numer_kolumny))); col.SetWidth(90); frame_4::lista->InsertColumn(a, col);
			a++;
		}
	}
	a = 0;
	for (int i = 0; i < frame_2::lista->GetItemCount(); i++)
	{
		if (i % 1000) dialog->Update(i);
	
		for (int j=0 ; j < frame_4::lista->GetColumnCount(); j++)
		{
			frame_4::lista->GetColumn(j, col);
			if (szukana != frame_2::lista->GetItemText(i, numer_kolumny)) break;
			if (col.GetText() == frame_2::lista->GetItemText(i,numer_kolumny))
			{
						frame_4::lista->InsertItem(a, "");
						frame_4::lista->SetItem(a, j, wxString::Format(wxT("%i"), i));
						j = frame_4::lista->GetColumnCount();
						a++;
						break;
				
			}
		}
	}
	dialog->Update(frame_2::lista->GetItemCount());
	delete dialog;
}


void szukanie_inwersyjne(int columna, wxString szukana)
{
	long itemIndex;
	wxListItem col;
	col.SetId(0); col.SetText(""); col.SetWidth(90);
	int X;
	for (int i = 0; i < frame_4::lista->GetColumnCount(); i++)
	{
		frame_4::lista->GetColumn(i, col);
		if (col.GetText() == szukana)
		{
			for (int j = 0; j< frame_4::lista->GetItemCount(); j++)
			{
				X = wxAtoi(frame_4::lista->GetItemText(j,i));
				itemIndex = frame_3::lista->InsertItem(j, "");
				frame_3::lista->SetItem(j, 0, frame_2::lista->GetItemText(X, 0));
				frame_3::lista->SetItem(j, 1, frame_2::lista->GetItemText(X, 1));
				frame_3::lista->SetItem(j, 2, frame_2::lista->GetItemText(X, 2));
				frame_3::lista->SetItem(j, 3, frame_2::lista->GetItemText(X, 3));
				frame_3::lista->SetItem(j, 4, frame_2::lista->GetItemText(X, 4));
				frame_3::lista->SetItem(j, 5, frame_2::lista->GetItemText(X, 5));
				frame_3::lista->SetItem(j, 6, frame_2::lista->GetItemText(X, 6));
				frame_3::lista->SetItem(j, 7, frame_2::lista->GetItemText(X, 7));
				frame_3::lista->SetItem(j, 8, frame_2::lista->GetItemText(X, 8));
			}
			return;	
		}
	}
}




void window_2::inwersyjne(wxCommandEvent& evt)
{
	
	okno3 = new frame_4(x); // inwersyjne
	okno4 = new frame_3(x); // wyniki 
	this->GetParent()->Freeze();
	pomocna(choice->GetSelection(),this, text_box->GetValue());  // TWORZY TABLICE POMOCNA
	indexowanie_inwersyjne(choice->GetSelection(),this, text_box->GetValue()); // TWORZY TABLICE inwersyjna

	clock_t start = clock(); 
	szukanie_inwersyjne(choice->GetSelection(), text_box->GetValue());
	czas_message(clock() - start, this);

	this->GetParent()->Thaw();
	okno4->Show();
	okno4->Freeze();
	if (frame_2::lista->GetItemCount() >= 100000)
	{
		wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa renderowanie tablicy..."), 20000, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
		for (int i = 0; i < 20000; i++) { if (i % 1000) dialog->Update(i); }
		okno4->Thaw();
		dialog->Update(20000);
		delete dialog;
	}
	else  okno4->Thaw();
}


void window_2::sortowanie()
{
	string index;
	struktura S;
	long l1, l2;
	int jj;
	frame_2::lista->Freeze();
	int column = choice->GetSelection();
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa sortowanie danych..."), frame_2::lista->GetItemCount()*2 -2, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	for (int j = 0; j < frame_2::lista->GetItemCount()-1; j++)
	{
		if (j % 1000) dialog->Update(j);
		for (int i = 0; i < frame_2::lista->GetItemCount() - j - 1; i++)
		{

			if (column == 0 || column == 7 || column == 8) // sprawdza czy kolumna jest liczbowa
			{
				l1 = stod(string(frame_2::lista->GetItemText(i, column)));   // konwertuje  stringa w liczbe
				l2 = stod(string(frame_2::lista->GetItemText(i + 1, column)));
			}
			else
			{
				l1 = frame_2::lista->GetItemText(i, column)[0];  // konwertuje  pierwszy znak stringa w liczbe
				l2 = frame_2::lista->GetItemText(i + 1, column)[0];
			}

			if (l1 > l2)
			{
				index = frame_2::lista->GetItemText(i + 1, 0);
				S.Imie = frame_2::lista->GetItemText(i + 1, 1);
				S.Nazwisko = frame_2::lista->GetItemText(i + 1, 2);
				S.Ulica = frame_2::lista->GetItemText(i + 1, 4);
				S.Kod = frame_2::lista->GetItemText(i + 1, 5);
				S.Miejscowosc = frame_2::lista->GetItemText(i + 1, 3);
				S.przedmiot = frame_2::lista->GetItemText(i + 1, 6);
				S.netto = frame_2::lista->GetItemText(i + 1, 7);
				S.brutto = frame_2::lista->GetItemText(i + 1, 8);
				frame_2::lista->SetItem(i + 1, 0, frame_2::lista->GetItemText(i, 0));
				frame_2::lista->SetItem(i + 1, 1, frame_2::lista->GetItemText(i, 1));
				frame_2::lista->SetItem(i + 1, 2, frame_2::lista->GetItemText(i, 2));
				frame_2::lista->SetItem(i + 1, 3, frame_2::lista->GetItemText(i, 3));
				frame_2::lista->SetItem(i + 1, 4, frame_2::lista->GetItemText(i, 4));
				frame_2::lista->SetItem(i + 1, 5, frame_2::lista->GetItemText(i, 5));
				frame_2::lista->SetItem(i + 1, 6, frame_2::lista->GetItemText(i, 6));
				frame_2::lista->SetItem(i + 1, 7, frame_2::lista->GetItemText(i, 7));
				frame_2::lista->SetItem(i + 1, 8, frame_2::lista->GetItemText(i, 8));

				frame_2::lista->SetItem(i, 0, index);
				frame_2::lista->SetItem(i, 1, S.Imie);
				frame_2::lista->SetItem(i, 2, S.Nazwisko);
				frame_2::lista->SetItem(i, 3, S.Miejscowosc);
				frame_2::lista->SetItem(i, 4, S.Miejscowosc);
				frame_2::lista->SetItem(i, 5, S.Kod);
				frame_2::lista->SetItem(i, 6, S.przedmiot);
				frame_2::lista->SetItem(i, 7, S.netto);
				frame_2::lista->SetItem(i, 8, S.brutto);

			}
		
			
		}
		jj = j;
	}
	
	if (column != 0 || column != 7 || column != 8)
	{
		
		for (int j = 0; j < frame_2::lista->GetItemCount() - 1; j++)
		{
			if (j % 1000) dialog->Update(jj+j);
			for (int i = 0; i < frame_2::lista->GetItemCount() - 1; i++)
			{
				l1 = frame_2::lista->GetItemText(i, column)[0];  
				l2 = frame_2::lista->GetItemText(i + 1, column)[0];
				if (l1 == l2)
				{
					int max_h = 0;
					if (frame_2::lista->GetItemText(i, column).Length() < frame_2::lista->GetItemText(i + 1, column).Length()) max_h = frame_2::lista->GetItemText(i+1, column).Length();
					else max_h = frame_2::lista->GetItemText(i , column).Length();
					for (int h = 1; h < max_h; h++)
					{
						
						if (frame_2::lista->GetItemText(i, column)[h] > frame_2::lista->GetItemText(i + 1, column)[h])
						{
							index = frame_2::lista->GetItemText(i + 1, 0);
							S.Imie = frame_2::lista->GetItemText(i + 1, 1);
							S.Nazwisko = frame_2::lista->GetItemText(i + 1, 2);
							S.Ulica = frame_2::lista->GetItemText(i + 1, 4);
							S.Kod = frame_2::lista->GetItemText(i + 1, 5);
							S.Miejscowosc = frame_2::lista->GetItemText(i + 1, 3);
							S.przedmiot = frame_2::lista->GetItemText(i + 1, 6);
							S.netto = frame_2::lista->GetItemText(i + 1, 7);
							S.brutto = frame_2::lista->GetItemText(i + 1, 8);
							frame_2::lista->SetItem(i + 1, 0, frame_2::lista->GetItemText(i, 0));
							frame_2::lista->SetItem(i + 1, 1, frame_2::lista->GetItemText(i, 1));
							frame_2::lista->SetItem(i + 1, 2, frame_2::lista->GetItemText(i, 2));
							frame_2::lista->SetItem(i + 1, 3, frame_2::lista->GetItemText(i, 3));
							frame_2::lista->SetItem(i + 1, 4, frame_2::lista->GetItemText(i, 4));
							frame_2::lista->SetItem(i + 1, 5, frame_2::lista->GetItemText(i, 5));
							frame_2::lista->SetItem(i + 1, 6, frame_2::lista->GetItemText(i, 6));
							frame_2::lista->SetItem(i + 1, 7, frame_2::lista->GetItemText(i, 7));
							frame_2::lista->SetItem(i + 1, 8, frame_2::lista->GetItemText(i, 8));

							frame_2::lista->SetItem(i, 0, index);
							frame_2::lista->SetItem(i, 1, S.Imie);
							frame_2::lista->SetItem(i, 2, S.Nazwisko);
							frame_2::lista->SetItem(i, 3, S.Miejscowosc);
							frame_2::lista->SetItem(i, 4, S.Miejscowosc);
							frame_2::lista->SetItem(i, 5, S.Kod);
							frame_2::lista->SetItem(i, 6, S.przedmiot);
							frame_2::lista->SetItem(i, 7, S.netto);
							frame_2::lista->SetItem(i, 8, S.brutto);
						}
						if(frame_2::lista->GetItemText(i, column)[h] < frame_2::lista->GetItemText(i + 1, column)[h]) break;

					}

				}
			}
		}
	}
	dialog->Update(frame_2::lista->GetItemCount() - 1);
	delete dialog;
	frame_2::lista->Thaw();
	return;
}



window_3::window_3(wxWindow* okno) : wxWindow(okno, wxID_ANY, wxPoint(20, 350), wxSize(545, 600))
{
	wxColour color(80, 150, 250);
	this->SetBackgroundColour(color);
	wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD, false);
	wxFont font_box(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false);

	box_labels = new wxStaticText(this, wxID_ANY, "Wpisz Id", wxPoint(80, 305), wxSize(100, 60));
	box_labels->SetFont(font);
	text_box = new wxTextCtrl(this, 2, "", wxPoint(200, 290), wxSize(150, 60));
	text_box->SetFont(font_box);

	button[0] = new wxButton(this, wxID_ANY, "Usun", wxPoint(50, 60), wxSize(200, 160));
	button[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_3::delete_line, this);
	button[0]->SetFont(font_box);
	button[1] = new wxButton(this, wxID_ANY, "Edytuj", wxPoint(300, 60), wxSize(200, 160));
	button[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_3::edit, this);
	button[1]->SetFont(font_box);
}


void window_3::edit(wxCommandEvent& evt)
{
	string caption = string(text_box->GetValue());
	if (numbers.Matches(caption) == false) { text_box->SetValue("Blad");  return; }
	edit_index = stod(caption)-1;
	this->Hide();
	cmain::window[0]->Show();
	text_box->Clear();
	window_1::button->SetLabelText("Edytuj");
	evt.Skip();
	return;
}

void window_3::delete_line(wxCommandEvent& evt)
{
	string caption = string(text_box->GetValue());
	if (numbers.Matches(caption) == false) { text_box->SetValue("Blad");  return; }
	long item_index = stod(caption);
	string a;
	cmain::okno->Freeze();
	frame_2::lista->DeleteItem(item_index-1);
	long max = frame_2::lista->GetItemCount()-1;
	if (max < 0)	return;
	for (int i = max; i >= item_index-1;i--)
	{
		a = to_string(i+1);
		frame_2::lista->SetItem(i, 0, a);
	}
	cmain::okno->Thaw();
	return;
}

window_4::window_4(wxWindow* okno) : wxWindow(okno, wxID_ANY, wxPoint(20, 350), wxSize(545, 600))
{
	main_window = okno;
	wxColour color(80, 150, 250);
	this->SetBackgroundColour(color);
	wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD, false);
	wxFont font_box(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false);
	box_labels[0] = new wxStaticText(this, wxID_ANY, "liczba do wygenerowania", wxPoint(20, 105), wxSize(150, 60));
	box_labels[0]->SetFont(font);
	box_labels[1] = new wxStaticText(this, wxID_ANY, "Usun wszystkie dane", wxPoint(20, 200), wxSize(150, 60));
	box_labels[1]->SetFont(font);
	text_box = new wxTextCtrl(this, 2, "", wxPoint(280,90), wxSize(150,60));
	text_box->SetFont(font_box);
	button[0] = new wxButton(this, wxID_ANY, "Generuj", wxPoint(440, 90), wxSize(100, 60));
	button[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_4::button_generate, this);
	button[1] = new wxButton(this, wxID_ANY, "Usun", wxPoint(440, 180), wxSize(100, 60));
	button[1]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &window_4::base_delete, this);
}


void window_4::button_generate(wxCommandEvent& evt)
{
	string baza_imion[11] = { "Cecylia","Arnold","Andrzej","Agata","Emilian","Felicja","Hipolit","Jan","Norman","Protazy","Ryszard" };
	string baza_nazwisk[11] = { "Kowalski","Nowak","Bury","Czarny","Czerwony","Szary","Bialy","Zielony","Fioletowy","Bravo","Wójcik" };
	char c,c_2;
	int lot,l1,l2;
	string caption = string(text_box->GetValue()) , caption_2;
	if (numbers.Matches(caption) == false) { text_box->SetValue("Blad");  return; }
	long int licznik = stod(caption);
	caption.clear();
	long int i=frame_2::lista->GetItemCount() + 1;
	long int max = licznik+i;
	long itemIndex;
	cmain::okno->Freeze();
	main_window->Freeze();
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa generowanie bazy..."), max, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	while (licznik != 0)
	{
		if (i % 1000) dialog->Update(i);
		itemIndex = frame_2::lista->InsertItem(i - 1, "");
		caption = wxString::Format(wxT("%d"), i);
		frame_2::lista->SetItem(itemIndex, 0, caption); // ID
		caption.clear();
		//  SURNAME
		lot = random(3,7);
	
		caption = baza_imion[random(0, 10)];
		caption_2 = baza_nazwisk[random(0, 10)];
		frame_2::lista->SetItem(itemIndex, 1, caption);
		frame_2::lista->SetItem(itemIndex, 2, caption_2);
		caption_2.clear();
		//STREET
		caption.clear();
		c = random(97, 122); c = toupper(c);
		for (int i = lot; i > 0; i--)
		{
			caption += c;
			c = random(97, 122);
		}
		frame_2::lista->SetItem(itemIndex, 4, caption);
		caption.clear();
		//POSTAL CODE
		for (int i = 5; i > 0; i--)
		{
			c = random(48, 57);
			//if (i == 3)caption += '-';
			caption += c;
		}
		caption.insert(2, "-");
		frame_2::lista->SetItem(itemIndex, 5, caption);
		caption.clear();

		// TOWN
		c = random(97, 122); c = toupper(c);
		for (int i = lot+1; i > 0; i--)
		{
			caption += c;
			c = random(97, 122);
		}
		frame_2::lista->SetItem(itemIndex, 3, caption);
		caption.clear();
		// ITEM
		c = random(97, 122); c = toupper(c);
		for (int i = lot+1; i > 0; i--)
		{
			caption += c; 
			c = random(97, 122);
		}
		frame_2::lista->SetItem(itemIndex, 6, caption);
		caption.clear();
		lot = random(1,4);
		//NETTO
		for (int i = lot; i > 0; i--)
		{
			c = random(48, 57);
			caption += c;
			c_2 = random(48, 57);
			caption_2 += c_2;
		}
		l1 = stod(caption);
		l2 = stod(caption_2);
		caption = to_string(l1);
		caption_2 = to_string(l2);
		frame_2::lista->SetItem(itemIndex, 7, caption + " z³");
		frame_2::lista->SetItem(itemIndex, 8, caption_2 + " z³");
		caption_2.clear();
		licznik--;
		i++;
	}
	dialog->Update(max);
	delete dialog;
	cmain::okno->Thaw();
	main_window->Thaw();
	return;
	evt.Skip();
}

void window_4::base_delete(wxCommandEvent& evt)
{
	int answer = wxMessageBox("Czy na pewno usunac baze?", "Potwierdz", wxYES_NO, this);
	if (answer == wxNO)  return;

	if (cmain::file->Access("Fiery_Bull_base", wxFile::read_write) == false)
	{
		cmain::file->Close();
		wxMessageBox("Nie znaleziono pliku");
		evt.Skip(); return;
	}
	frame_2::lista->DeleteAllItems();
	wxRemoveFile("Fiery_Bull_base");
	evt.Skip();
}