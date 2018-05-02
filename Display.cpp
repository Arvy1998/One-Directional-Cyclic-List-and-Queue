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
