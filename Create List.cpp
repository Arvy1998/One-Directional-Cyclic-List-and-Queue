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
