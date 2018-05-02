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
