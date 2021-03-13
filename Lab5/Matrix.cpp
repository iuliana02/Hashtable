#include "Matrix.h"
#include <exception>
using namespace std;


//Complexitate constructor: Theta(m) in toate cazurile, fiindca initializez array-ul cu pointeri nuli
Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	
	m = 97;
	elements = new Node*[m];
	size = 0;
	//initializez lista de pointeri cu NULL
	for (int i = 0; i < m; i++)
	{
		Node* n = NULL;
		elements[i] = n;
	}
	
	NrLines = nrLines;
	NrCols = nrCols;

}

//Theta(1) in toate cazurile, returnez doar o constanta
int Matrix::nrLines() const {
	//TODO - Implementation
	return NrLines;
}

//Theta(1) in toate cazurile, returnez doar o constanta
int Matrix::nrColumns() const {
	//TODO - Implementation
	return NrCols;
}

//Hashwert:Theta(1)
// Best:Theta(1), Worst und Average:Theta(1+belegungsfaktor) ; depinde de cate elemente sunt in lista de pe pozitia respectiva
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	
	if (i < 0 || i>NrLines || j < 0 || j>NrCols)
	{
		exception e;
		throw e;
	}

	// ca si cheie pt functia hash folosesc spalte
	//daca hashcode-ul este < 0 sau > m, inseamna ca e pozitie invalida
	if (funktion(j) < 0 || funktion(j) > m)
	{
		exception e;
		throw e;
	}

	int pos = funktion(j); //calculez Hashwert-ul (dupa coloana)
	Node* current;
	current = elements[pos];

	//daca elementul de pe pos e elementul pe care il caut
	if (current != NULL && current->Info.zeile == i && current->Info.spalte == j)
		return current->Info.wert;

	//traversez lista de pe pozitia k
	while (current!=NULL)
	{
		if (current->Info.zeile == i && current->Info.spalte == j)
			return current->Info.wert;
		current = current->Next;
	}

	return NULL_TELEM;
}


//Theta(1) pentru calcularea pozitiei
// Best: Theta(1) cand nu am niciun element pe pozitia respectiva, Worst und Average: Theta(1+belegungsfaktor) cand trebuie sa parcurg toata lista pentru cautare (chiar daca inserez la inceputul listei)
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	
	if (i<0 || i>NrLines || j<0 || j>NrCols)
	{
		exception e;
		throw e;
	}

	// ca si cheie pt functia hash folosesc spalte
	// daca hashcode-ul este < 0 sau > m, inseamna ca e pozitie invalida
	if (funktion(j) < 0 || funktion(j) > m)
	{
		exception e;
		throw e;
	}

	/* am o problema la resize si rehash, dar functioneaza bine si fara
	double belegungsfaktor = size / m;
	if (belegungsfaktor >= 1) //resize + rehash
	{
		int oldM = m;
		m = (2 * m) + 1;
		Node** newElements = new Node*[m];
		for (int i = 0; i < m; i++)
		{
			Node* n = NULL;
			newElements[i] = n;
		}
		for (int i = 0; i < oldM; i++)
		{
			Node* n = elements[i];
			while (n != NULL)
			{
				int index = funktion(n->Info.spalte);
				if (newElements[index] == NULL)
				{
					newElements[index] = n;
					n->Next = NULL;
				}
				else
				{
					Node* current = newElements[index];
					while (current->Next != NULL)
						current = current->Next;
					current->Next = n;
				}
				n = n->Next;
			}
		}
		delete[] elements;
		elements = newElements;
	}
	*/

	Tupel t;
	t.spalte = 0;
	t.zeile = 0;
	t.wert = 0;
	Tupel modifiedValue = t;

	int pos = funktion(j); //Hashwert (dupa coloana)
	Node* head;
	head = elements[pos];

	Node* newNode = new Node;
	newNode->Info.zeile = i;
	newNode->Info.spalte = j;
	newNode->Info.wert = e;
	newNode->Next = NULL;

	//vechea valoare = 0
	if (head == NULL)
	{
		//daca nu am niciun pointer in pos si valoarea de inserat e 0 -> nu fac nimic
		if (e == 0)
			return e;
		else
		{
			//inserez un nod nou pe prima poz din lista
			newNode->Next = elements[pos];
			elements[pos] = newNode;
			return modifiedValue.wert;
			size++;
		}
	}
	//vechea valoare != 0
	else if (head != NULL)
	{

		//cazul in care vechiul elem!=0 si nou elem = 0 -> sterg elementul
		if (e == 0)
		{
			Node* current;
			current = elements[pos];
			Node* previous;
			previous = current;
			current = current->Next;

			//am un singur elem in lista
			if (current == NULL && previous->Info.zeile==i && previous->Info.spalte==j)
			{
				modifiedValue=previous->Info;
				delete previous;
				return modifiedValue.wert;
			}
			while (current != NULL)
			{
				if (current->Info.zeile == i && current->Info.spalte == j)
				{
					TElem ret = current->Info.wert;
					Node* after;
					if (current->Next != NULL)
					{
						after = current->Next;
						previous->Next = after;
						current->Next = NULL;
						delete current;
						return ret;
					}
					else
					{
						previous->Next = NULL;
						//current->Next = NULL;
						delete current;
						return ret;
					}
				}
				previous = previous->Next;
				current = current->Next;
			}
		}

		//cazul in care ambele valori sunt !=0 -> modific doar valoarea
		if (e != 0)
		{
			Node* current;
			current = elements[pos];
			TElem ret;

			if (current->Next == NULL && current->Info.zeile==i && current->Info.spalte==j)
			{
				ret = current->Info.wert;
				current->Info.wert = e;
				return ret;
			}
			while (current != NULL && current->Info.zeile != i && current->Info.spalte != j)
			{
				current = current->Next;
				if (current != NULL && current->Info.zeile == i && current->Info.spalte == j)
				{
					ret = current->Info.wert;
					current->Info.wert = e;
					return ret;
				}
			}

			size++;
			newNode->Next = elements[pos];
			elements[pos] = newNode;
			return modifiedValue.wert;

		}

	}
}


//Nu stiam exact cum sa abordez situatia in cazul exceptiilor, avand in vedere ca la functia element() a trebuit sa pun niste conditii pentru cazurile in care nr de randuri/linii sunt mai mari
// pentru ca la testele de exceptii erau necesare aceste conditii
// Astfel imi intra si aici in exceptie
//functia suplimentara
// Best:Theta(1) cand noile dimensiuni sunt egale; Worst und Average: Theta(belegungsfaktor+1) cand trebuie parcursa lista si sterse elemente
void Matrix::neue_dimension(int neue_zeile, int neue_spalte)
{
	int old_zeile = NrLines;
	int old_columns = NrCols;
	NrLines = neue_zeile;
	NrCols = neue_spalte;

	while (neue_spalte < old_columns)
	{
		int pos = funktion(neue_spalte); //calculez functia hash dupa noul nr de coloane
		//cazul in care nr de randuri/ nr de col. e mai mic
		if (neue_zeile < old_zeile || neue_spalte < old_columns)
		{
			Node* current = elements[pos];
			if (current != NULL && (current->Info.zeile >= NrLines || current->Info.spalte >= NrCols)) ///cazul cand e chiar primul din lista
			{
				current->Next = NULL;
				delete current;
			}
			while (current != NULL)
			{
				Node* prev = current;
				current = current->Next;
				if (current->Info.zeile >= neue_zeile || current->Info.spalte >= NrCols) //daca iese din matrice, sterg elementul
				{
					Node* after = current->Next;
					if (after == NULL) //cand e chiar ultimul din lista
					{
						current->Next = NULL;
						delete current;
					}
					else //cand e prin mijlocul listei
					{
						prev->Next = after;
						current->Next = NULL;
						delete current;
					}
				}
			}
		}
		neue_spalte++;
	}
}