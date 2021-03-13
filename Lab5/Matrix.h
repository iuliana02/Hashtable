#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem ;
#define NULL_TELEM 0
typedef int TKey;

struct Tupel {
	int zeile;
	int spalte;
	TElem wert;
};

struct Node {
	Tupel Info;
	Node* Next;
};


class Matrix {

private:
	//TODO - Representation
	
	Node** elements; //array de pointeri
	int m ; //lungimea arrayului de pointeri
	int size = 0;
	int funktion(TKey key) const //functia hash
	{
		if (key < 0)
			return (-1) * (key % m);
		return (key % m);
	}

	int NrLines;
	int NrCols;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);


	//functia suplim.
	void neue_dimension(int neue_zeile, int neue_spalte);

};
