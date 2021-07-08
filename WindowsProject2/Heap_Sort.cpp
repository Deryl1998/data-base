#include "Heap_Sort.h"

void Heap_Sort::swap(int index_1, int index_2,wxListCtrl &lista)
{
	
	S.lp = lista.GetItemText(index_1, 0);
	S.Imie = lista.GetItemText(index_1, 1);
	S.Nazwisko = lista.GetItemText(index_1, 2);
	S.Ulica = lista.GetItemText(index_1, 4);
	S.Kod = lista.GetItemText(index_1, 5);
	S.Miejscowosc = lista.GetItemText(index_1, 3);
	S.przedmiot = lista.GetItemText(index_1, 6);
	S.netto = lista.GetItemText(index_1, 7);
	S.brutto = lista.GetItemText(index_1, 8);
	lista.SetItem(index_1, 0, lista.GetItemText(index_2, 0));
	lista.SetItem(index_1, 1, lista.GetItemText(index_2, 1));
	lista.SetItem(index_1, 2, lista.GetItemText(index_2, 2));
	lista.SetItem(index_1, 3, lista.GetItemText(index_2, 3));
	lista.SetItem(index_1, 4, lista.GetItemText(index_2, 4));
	lista.SetItem(index_1, 5, lista.GetItemText(index_2, 5));
	lista.SetItem(index_1, 6, lista.GetItemText(index_2, 6));
	lista.SetItem(index_1, 7, lista.GetItemText(index_2, 7));
	lista.SetItem(index_1, 8, lista.GetItemText(index_2, 8));
	lista.SetItem(index_2, 0, S.lp);
	lista.SetItem(index_2, 1, S.Imie);
	lista.SetItem(index_2, 2, S.Nazwisko);
	lista.SetItem(index_2, 3, S.Miejscowosc);
	lista.SetItem(index_2, 4, S.Ulica);
	lista.SetItem(index_2, 5, S.Kod);
	lista.SetItem(index_2, 6, S.przedmiot);
	lista.SetItem(index_2, 7, S.netto);
	lista.SetItem(index_2, 8, S.brutto);
}


void Heap_Sort::heapify(int n, int i,wxListCtrl &lista)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2
	// If left child is larger than root
	 int x1, x2, x3;

	if (l < n)
	{
		if (is_char == false)
		{
			x1 = wxAtoi(lista.GetItemText(l, column));
			x2 = wxAtoi(lista.GetItemText(largest, column));
		}
		else
		{
			x1 = lista.GetItemText(l, column)[x];
			x2 = lista.GetItemText(largest, column)[x];
		}

		if (is_char == true && x1 == x2)
		{
	
			while (x1 == x2 )
			{
				if (lista.GetItemText(l, column) == lista.GetItemText(largest, column)) break;
				x++;
				if (x < lista.GetItemText(l, column).Length()-1) x1 = lista.GetItemText(l, column)[x];
				else { x1 = 0; break; }
				if (x < lista.GetItemText(largest, column).Length()-1) x2 = lista.GetItemText(largest, column)[x];
				else { x2 = 0; break; }
			}
			x = 0;
		}

		if (x1 > x2)
		{
			largest = l; x = 0;
		}
	}

	// If right child is larger than largest so far
	if (r < n)
	{
		if (is_char == false)
		{
			x2 = wxAtoi(lista.GetItemText(largest, column));
			x3 = wxAtoi(lista.GetItemText(r, column));
		}
		else
		{
			x2 = lista.GetItemText(largest, column)[x];
			x3 = lista.GetItemText(r, column)[x];
		}
		if (is_char == true && x3 == x2)
		{
	
			while (x3 == x2)
			{
				if (lista.GetItemText(r, column) == lista.GetItemText(largest, column)) break;
				x++;
				if (x < lista.GetItemText(r, column).Length()-1) x3 = lista.GetItemText(r, column)[x];
				else { x3 = 0; break; }
				if (x < lista.GetItemText(largest, column).Length()-1) x2 = lista.GetItemText(largest, column)[x];
				else { x2 = 0; break; }
			}
			x = 0;
		}

		if (x3 > x2)
		{
			largest = r; x = 0;
		}
	}

	// If largest is not root

	if (largest != i) {
		swap(largest, i,lista);
		// Recursively heapify the affected sub-tree
		heapify(n, largest,lista);
	}
}


void Heap_Sort::heapSort(int n,int number_of_column, wxListCtrl &lista, wxWindow*okno)
{
	
	x = 0;
	if (number_of_column == 0 || number_of_column == 7 || number_of_column == 8) is_char = 0;
	else is_char = 1;
	column = number_of_column;
	int a = n;
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Czekaj.."), wxT("Trwa sortowanie..."), a+a/2, okno, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	a = 0;
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		a++;
		heapify(n, i, lista);
		if (a % 1000) dialog->Update(a);
	}
	for (int i = n; i > 0; i--) {
		a++;
		swap(0, i, lista);
		heapify(i, 0, lista);
		if (a % 1000) dialog->Update(a);
	}

	delete dialog;
}