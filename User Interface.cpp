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
