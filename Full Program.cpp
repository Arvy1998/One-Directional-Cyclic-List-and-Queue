#include <iostream> // I/O
#include <cstdio>
#include <cstdlib> // atminties valdymo komandai 'free()' ir 'size_t' tipui
#include <chrono> // laiko valdymas (2 bibliotekos)
#include <thread>
#include <fstream> // darbui su failais
#include <vector> // dinamine struktura vektorius
#include <string> // vartotojo sasajai - 'T'/'N' simboliu ivedimui, kol vyksta programos valdymas

using namespace std;
using namespace std::this_thread; // funkcijos, reikalingos valdyti vartotojo sasajai (laiko valdymas)
using namespace std::chrono;

struct node { // inicializuojame ciklinio vienkrypcio saraso elementa (node - virsune, data - duomenys virsuneje, next ir last - rodykles)
	string data;
	struct node *next;
} *last;

ofstream outputFile; // rezultatu failas matomas visoje programoje

class vienkryptis_ciklinis_sarasas { // inicializuojami svarbiausiu funkciju prototipai
	public: 
		void add_element(string value, int position);
		void delete_element(string value);
		void create_list(vector <string> vektorius);
		void display();
		vienkryptis_ciklinis_sarasas() { // kai sarasas yra tuscias, paskutinioji rodykle nukreipta i reiksme NULL
			last = NULL;
		}
};

void vienkryptis_ciklinis_sarasas::create_list(vector <string> vektorius) { // vienkrypcio ciklinio saraso kurimas
	string temporary_vector_element;
	for (size_t x = 0; x < vektorius.size(); x++) { // rodykle katik sukurtos virsunes kaskart nukreipiama i
		struct node *temporary_vector_element;      // kiekvieno sekancio elemento reiksme is dinaminio vektoriaus, kol sukamas ciklas
		temporary_vector_element = new(struct node); // o pasiekus NULL reiksme (vektoriaus pabaiga) - paskutiniojo elemento rodykle
		temporary_vector_element->data = vektorius[x]; // nukreipiama i pirmaji elementa
		if (last == NULL) {
			last = temporary_vector_element;
			temporary_vector_element->next = last;
		}
		else {
			temporary_vector_element->next = last->next;
			last->next = temporary_vector_element;
			last = temporary_vector_element;
		}
	}
}

void vienkryptis_ciklinis_sarasas::display() { // funkcija isspausdinanti vienkrypti ciklini sarasa ekrane bei irasanti ji i rezultatu faila
	struct node *isvedimas;
	if (outputFile.good()) {
		if (last == NULL) { // jeigu pirmojo elemento nera, sarasas tuscias
			cout << "Vienkryptis tiesinis sarasas yra tuscias." << endl;
			outputFile << "Vienkryptis tiesinis sarasas yra tuscias." << endl;
			return;
		}
		else { // kitu atveju sukamas ciklas, einama per visus elementus ir jie spausdinami tol, kol pasiekiama rodykle, rodanti i pirmaji elementa
			isvedimas = last->next;
			while (isvedimas != last)
			{
				cout << isvedimas->data << "->";
				outputFile << isvedimas->data << "->";
				isvedimas = isvedimas->next;
			}
			cout << isvedimas->data << endl;
			outputFile << isvedimas->data << endl;
		}
	}
	else {
		cout << "Nepavyko atidaryti rezultato failo! Isspreskite problema ir meginkite dar karta." << endl;
		return;
	}
}

void vienkryptis_ciklinis_sarasas::add_element(string value, int position) { // elemento iterpimas i vienkrypti ciklini sarasa
	if (last == NULL) { // iterpti elemento i tuscia sarasa negalima
		cout << "Negalima iterpti elemento i tuscia sarasa." << endl;
		return;
	}
	else { // nustatoma elemento pozicija, jis bus iterptas po n-tojo elemento
		struct node *iterpiamas, *laikinas;
		laikinas = last->next;
		for (int z = 0; z < position - 1; z++)
		{
			laikinas = laikinas->next;
			if (laikinas == last->next) // pozicijos indeksas virsitinas (ivestas didesnis skaicius, negu egzistuoja elementu)
			{
				cout << "Pozicijos numeris yra per didelis - ivedete netinkama skaiciu." << endl;
				return;
			}
		}
		iterpiamas = new(struct node);
		iterpiamas->next = laikinas->next;
		iterpiamas->data = value;
		laikinas->next = iterpiamas;
		if (laikinas == last) {
			last = laikinas;
		}
	}
}

void vienkryptis_ciklinis_sarasas::delete_element(string value) { // elemento trynimas is tiesinio saraso
	struct node *trinamas, *laikinas;
	if (last == NULL) { // ar sarasas tuscias
		cout << "Negalima naikinti elemento is jau tuscio saraso..." << endl;
		return;
	}
	trinamas = last->next;
	if (last->next == last && last->data == value) { // tikriname, ar rastas elementas yra vienintelis
		laikinas = last;
		last = NULL;
		free(laikinas);
		cout << "Elementas sekmingai istrintas." << endl;
		return;
	}
	if (trinamas->data == value) { // tikriname, ar rastas elementas yra pirmasis sarase
		laikinas = trinamas;
		last->next = trinamas->next; // paskutiniojo elemento rodykle rodo i uz pirmajo esanti nari
		free(laikinas);
		cout << "Pirmasis elementas sekmingai istrintas." << endl;
		return;
	}
	while (trinamas->next != last) // trinamas viduryje esantis elementas (rodykle rodo ne i paskutini elementa)
	{
		if (trinamas->next->data == value) // jeigu trinamo elemento rodykle rodo i sekanti elementa, kurio informacine dalis sutampa
		{
			laikinas = trinamas->next;
			trinamas->next = laikinas->next;
			free(laikinas);
			cout << "Elementas su informacineje dalyje esanciu skaiciumi " << value << " sekmingai istrintas." << endl;
			return;
		}
		trinamas = trinamas->next;
	}
	if (trinamas->next->data == value) // paskutinio sarase elemento trinimas
	{
		laikinas = trinamas->next;
		trinamas->next = last->next;
		free(laikinas);
		cout << "Paskutinis elementas sekmingai istrintas." << endl;
		last = trinamas;
		return;
	}
	cout << "Elementas su informacine dalimi " << value << " neegzistuoja." << endl;
}

int main() // pagrindine funkcija, kurioje valdomos sub-funkcijos vienkrypciam cikliniam sarasui valdyti
{
	int pasirinkimas, position, ilgis = 0; // inicializacija
	vienkryptis_ciklinis_sarasas vienkryptis_ciklinis_sarasas_struct; // klases objekto inicializacija
	string pradzia, value, temporary_vector_element;
	vector <string> vektorius; // dinaminio vektoriaus inicializacija
	start:
	system("cls"); // isvalomas langas (vartotojo sasajos valdymo patogumui)
	cout << "Sveiki. Si programa atlieka keleta veiksmu su vienkrypciu cikliniu sarasu." << endl;
	cout << "Sis sarasas bus sukurtas is faile \'skaiciu_seka.txt\' surasytos sekos." << endl;
	cout << "Noredami testi ir nuskaityti faila, spauskite 'T', jei norite iseiti - 'N'" << endl;
	cin >> pradzia; // meniu
	if (pradzia == "N") {
		system("cls");
		cout << "Sekmingai isejote." << endl;
		exit(0);
	}
	if (pradzia != "N" && pradzia != "T") {
		system("cls");
		cout << "Netiketa ivestis, isitikinkite, ar ivedete tai, ko programa prase." << endl;
		sleep_for(seconds(2));
		goto start;
	}
	if (pradzia == "T") {
		system("cls");
		ifstream failas;
		failas.open("skaiciu_seka.txt"); // atidaromas failas duomenu nuskaitymui
		if (failas.good()) {            // ar faila pavyko atidaryti ir ar jis egzistuoja?
			failas.seekg(0, ios::end); // ar failas tuscias?
			ilgis = failas.tellg();
			if (ilgis != 0) {
				failas.seekg(0); // zyma buvo nukelta i pabaiga, todel ja reikia vel perkelti i pozicija 0
				while (!failas.eof()) {
					failas >> temporary_vector_element;
					vektorius.push_back(temporary_vector_element);
				}
				failas.close();
				cout << "Failas nuskaitytas sekmingai. Duotoji seka yra: " << endl;
				for (size_t j = 0; j < vektorius.size(); j++) { // vektoriaus spausdinimas
					if (j == vektorius.size() - 1) {
						cout << vektorius[j] << ".";
					}
					else {
						cout << vektorius[j] << " ";
					}
				}
				cout << endl << endl;
			}
			else if (ilgis == 0) { // failas tuscias (zyma pasislinko per 0 poziciju)
				cout << "Failas nuskaitytas sekmingai. Duotoji seka neturi elementu." << endl << endl;
			}
		}
		else if (!failas.is_open()) { // failo atverti nepavyko arba jis neegzistuoja
			cout << "Ivyko klaida atidarant faila!" << endl;
			sleep_for(seconds(2));
			exit(1); // klaida
		}
	}
	vienkryptis_ciklinis_sarasas_struct.create_list(vektorius);
	cout << "Elementai sudeti i vienkrypti ciklini sarasa: " << endl;
	outputFile.open("rezultato_failas.txt");
	outputFile << "Pries pakeitimus jusu saraso turinys yra toks: " << endl;
	vienkryptis_ciklinis_sarasas_struct.display();
	outputFile << endl;
	cout << endl; // meniu veiksmams su vienkrypciu cikliniu sarasu
	cout << "Pasirinkite spausdami atitinkama skaiciu, ka norite atlikti: " << endl;
	cout << "1 - Iterpti elementa i sarasa;" << endl;
	cout << "2 - Pasalinti elementa is saraso." << endl;
	cin >> pasirinkimas;
	switch (pasirinkimas)
	{
	case 1: {
		cout << "Iveskite skaiciaus reiksme ir pozicija naujo elemento: " << endl;
		cin >> value >> position;
		if (outputFile.good()) {
			vienkryptis_ciklinis_sarasas_struct.add_element(value, position);
			cout << endl << "Po pasikeitimo jusu vienkryptis ciklinis sarasas atrodo taip: " << endl;
			outputFile << "Po pasikeitimo jusu vienkryptis ciklinis sarasas atrodo taip: " << endl;
			vienkryptis_ciklinis_sarasas_struct.display();
		}
		else {
			cout << "Programa negali atlikti darbo, failas sugadintas..." << endl;
		}
		cout << "Programa darba baige. Nuspauskite bet kuri klasiva, kad iseitumete.";
		break;
	}
	case 2: {
		cout << "Iveskite elemento informacine dali." << endl;
		cin >> value;
		if (outputFile.good()) {
			vienkryptis_ciklinis_sarasas_struct.delete_element(value);
			cout << endl << "Po pasikeitimo jusu vienkryptis ciklinis sarasas atrodo taip: " << endl;
			outputFile << "Po pasikeitimo jusu vienkryptis ciklinis sarasas atrodo taip: " << endl;
			vienkryptis_ciklinis_sarasas_struct.display();
		}
		else {
			cout << "Programa negali atlikti darbo, failas sugadintas..." << endl;
		}
		cout << "Programa darba baige. Nuspauskite bet kuri klasiva, kad iseitumete.";
		break;
	}
	default: // netiketai ivesciai apdoroti
		cout << "Pasitikrinkite, ar ivedete tai, ko programa paprase ir meginkite dar karta." << endl;
		sleep_for(seconds(3));
		goto start;
	}
    return 0;
}
