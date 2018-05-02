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
