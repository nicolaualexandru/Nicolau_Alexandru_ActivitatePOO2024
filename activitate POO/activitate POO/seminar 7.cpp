#include <iostream>
using namespace std;

class Carte {
	int nrPagini;
	int nrCarti;
	float pret;
	const int anAparitie;
	static string autor;
	string* listaCarti;

public:
	// GETTERI !!!!!!!!de preferat dai return cu "this"
	int getNrPagini() {
		return this->nrPagini;
	}

	int getNrCarti() {
		return this->nrCarti;
	}

	float getPret() {
		return this->pret;
	}

	int getAnAparitie() {
		return anAparitie;
	}

	static string getAutor() {
		return autor;
	}
	////LA POINTER :
	string* getListaCarti() {
		return this->listaCarti;
	}

	//doar pt o carte din lista!!!!
	string getListaCarte(int index) {
		if (index >= 0 && index < this->nrCarti) {
			return this->listaCarti[index];
		}
		else {
			return "Nu a fost gasita.";
		}
	}


	//SETTERI   !!!nu am * aici observ, nici const (logic), nici static

	void setNrPagini(int nrPagini) {
		if (nrPagini > 0) {
			this->nrPagini = nrPagini;
		}
		else cout << "Cartea nu exista.";
	}

	void setNrCarti(int nrCarti) {
		if (nrCarti > 0) {
			this->nrCarti = nrCarti;
		}
		else cout << "Nu avem carti in lista";
	}

	void setPret(float pret) {
		if (pret > 0 && pret <= 50) {
			cout << "Cartea este ieftina.";
			this->pret = pret;
		}
		else {
			if (pret == 0) {
				cout << "Cartea este gratis.";
				this->pret = 0;
			}
			else {
				cout << "Cartea este scumpa.";
				this->pret = pret;
			}
		}
	}

	//CONSTRUCTORI
	//implicit:  putem sa le dam direct valori sau nu!!!!!!
	Carte() : anAparitie(2020) {
		this->nrPagini = 150;
		this->nrCarti = 3;
		this->pret = 15;
		this->listaCarti = NULL;
	}

	//explicit 1
	Carte(int nrPagini, float pret) : anAparitie(2020) {
		this->nrPagini = nrPagini;
		this->pret = pret;
		this->nrCarti = 0;
		this->listaCarti = NULL;
	}
	//explicit 2
	Carte(int nrPagini, int nrCarti, float pret, string& listaCarti) : anAparitie(2020), nrCarti(3) {
		this->nrPagini = nrPagini;
		this->pret = pret;
		this->listaCarti = new string[nrCarti];
		for (int i = 0; i < nrCarti; i++) {
			this->listaCarti[i] = listaCarti[i];
		}
	}

	//de copiere
	Carte(const Carte& c) : anAparitie(2020) { //parametrul constant ramane
		this->nrPagini = c.nrPagini;
		this->nrCarti = c.nrCarti;
		this->pret = c.pret;
		this->listaCarti = new string[c.nrCarti];
		for (int i = 0; i < c.nrCarti; i++) {
			this->listaCarti[i] = c.listaCarti[i];
		}
	}

	//DESTRUCTOR !!!!!!aici de invatat
	~Carte() {
		if (this->listaCarti != NULL) {
			delete[] this->listaCarti;
		}
	}


	//METODE !!!!!!! exemple
//1.
	void afisare() {
		cout << "Nr pagini:" << this->nrPagini << endl;
		cout << "Nr carti:" << this->nrCarti << endl;
		if (this->listaCarti != NULL) {
			for (int i = 0; i < this->nrCarti; i++) {
				cout << this->listaCarti[i] << ", ";
			}
		}
		cout << endl;
		cout << "Pret:" << this->pret << endl;
		cout << "Autor:" << this->autor << endl;
		cout << "An aparitie:" << this->anAparitie << endl;
	}
	//2.
		/*float calculeazaPretTotal() {
			return this->pret + (this->pret * (Masina::TVA / 100.0f));
		}*/
		//3.
	static void modificaAutor(string noulAutor) {
		if (noulAutor.length() > 0) {
			Carte::autor = noulAutor;
		}
	}


	//OPERATORI !!!!!!!! e aproape la fel ca constructorul de copiere
// "="
	Carte operator=(const Carte& c) {
		if (this != &c) {
			this->nrPagini = c.nrPagini;
			this->nrCarti = c.nrCarti;
			this->pret = c.pret;
			if (this->listaCarti != NULL) delete[] this->listaCarti;
			this->listaCarti = new string[c.nrCarti];

			for (int i = 0; i < c.nrCarti; i++) {
				this->listaCarti[i] = c.listaCarti[i];
			}
		}
		return *this;
	}
	//"cin"
	friend istream& operator>>(istream& input, Carte& c) {
		cout << "Introduceti nr pag:";
		input >> c.nrPagini;
		cout << "Nr Carti:";
		input >> c.nrCarti;
		if (c.listaCarti != NULL) {
			delete[]c.listaCarti;
		}
		if (c.nrCarti > 0) {
			c.listaCarti = new string[c.nrCarti];
			cout << "Carti in lista:";
			for (int i = 0; i < c.nrCarti; i++) {
				input >> c.listaCarti[i];
			}
		}
		else {
			c.listaCarti = NULL;
		}
		cout << "Pret:";
		input >> c.pret;
		return input;
	}
	//"cout"
	friend ostream& operator<<(ostream& output, Carte c);
};

string Carte::autor = "Albert Camus";

//"cout"
ostream& operator<<(ostream& output, Carte c) {
	output << "Nr pag:" << c.nrPagini << endl;
	output << "Nr carti:" << c.nrCarti << ": ";
	if (c.listaCarti != NULL) {
		for (int i = 0; i < c.nrCarti; i++) {
			output << c.listaCarti[i] << ", ";
		}
	}
	output << endl;
	output << "Pret:" << c.pret << endl;
	output << "Autor:" << c.autor << endl;
	output << "An aparitie:" << c.anAparitie << endl;
	return output;
}



int main() {
	Carte c1(130, 15);
	Carte c2(310, 12);

	int lungime = 3;
	Carte* pointer = new Carte(110, 20);
	Carte* vector = new Carte[lungime];

	vector[0] = *pointer;
	vector[1] = c1;

	cout << *pointer << endl << endl;

	for (int i = 0; i < lungime; i++) {
		cout << vector[i] << endl;
	}

	Carte** vectorPointeri = new Carte * [lungime + 1];
	vectorPointeri[0] = pointer;
	vectorPointeri[1] = &c1;
	vectorPointeri[2] = &vector[1];//vector+1
	vectorPointeri[3] = new Carte(56, 5);

	vector[2] = *vectorPointeri[1];


	delete pointer;
	delete[] vector;

	//for (int i = 0; i < lungime; i++) {
	//	delete vectorPointeri[i];
	//}
	delete vectorPointeri[3];

	delete[]vectorPointeri;

	Carte** matrice;
	matrice = new Carte * [lungime];
	for (int i = 0; i < lungime; i++) {
		matrice[i] = new Carte[lungime];
	}

	for (int i = 0; i < lungime; i++) {
		delete[]matrice[i];
	}
	delete[]matrice;

	return 0;
}