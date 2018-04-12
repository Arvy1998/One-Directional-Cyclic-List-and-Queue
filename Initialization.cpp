#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace std::this_thread; // funkcijos, reikalingos valdyti vartotojo sasajai (laiko valdymas)
using namespace std::chrono;

struct node { // node - virsune, data - duomenys virsuneje, next ir last - rodykles
	int data;
	struct node *next;
} *last;

class vienkryptis_ciklinis_sarasas { // inicializuojami svarbiausiu funkciju prototipai
	public: 
		void add_element(int value, int position);
		void delete_element(int value);
		void create_list(vector <int> vektorius);
		void display();
		vienkryptis_ciklinis_sarasas() { // kai sarasas yra tuscias, paskutinioji rodykle nukreipta i reiksme NULL
			last = NULL;
		}
};
