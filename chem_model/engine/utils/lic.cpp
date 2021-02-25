// sklejony_kod.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <time.h>
#include <fstream>
#include <string.h>
///////////////////////GRAPG_CLASS//////////////////////////////////////////////////////////////
class Graph {
public:
	std::vector<std::vector<int>> single_graph;
	unsigned int level;//potrzebuję wiedzieć ile krawędzi było wstawianych, to jeden int a liczyć to trzebaby wiele razy bo trochę używam, nie krzycz
	//void create_graph(std::vector<std::vector<int>>& single_graph);
	Graph() {

	}
	~Graph() {
		for (int i = 0; i < single_graph.size(); i++) {
			single_graph[i].clear();
		}
		single_graph.clear();
	}
};

///////////////////////UTILS////////////////////////////////////////////////////////////////////
std::vector<std::string> ELEMENTS;
std::vector<int> QUANTITY;

std::vector<std::string> ELEMENTS_TABLE;

std::vector<std::string> HALOGENS = { "F", "Cl", "Br", "I" };
std::vector<std::string> NO_HALOGENS = { "O", "N", "S" };

std::vector<std::string> SN_RULE = { "S", "N" };


std::vector<std::vector<int>> obtain_level(std::vector<std::vector<int>>& graph, int lvl) {
	//std::cout << "uzylem funkcji obtain_level" << std::endl;
	std::vector<std::vector<int>> graph_on_lvl;
	int counter = 0;

	for (int i = 0; i < graph.size(); i++) {
		std::vector<int> help_list;
		for (int j = 0; j < graph[i].size(); j++) {
			if (counter == lvl)
				break;

			help_list.push_back(graph[i][j]);
		}
		graph_on_lvl.push_back(help_list);
		help_list.clear();

		counter++;

		if (counter == lvl)
			break;
	}

	return graph_on_lvl;
}

//----------------------------------------------------------------------------------------------------------------------------

std::vector<std::vector<int>> transform(std::vector<std::vector<int>>& neighbors_list) {
	std::vector<std::vector<int>> edges_list;
	//std::cout << "uzylem funkcji transform" << std::endl;

	for (int i = 0; i < neighbors_list.size(); i++) {
		std::vector<int> help_list;

		for (int j = 0; j < neighbors_list[i].size(); j++) {
			help_list.push_back(i + 1);
			help_list.push_back(neighbors_list[i][j]);
			edges_list.push_back(help_list);
			help_list.clear();
		}
	}

	return edges_list;
}

//----------------------------------------------------------------------------------------------------------------------------

bool check(int number, std::vector<int> u) {
	//std::cout << "uzylem funkcji check" << std::endl;
	bool outcome = true;

	for (int i = 0; i < u.size(); i++)
		if (u[i] == number) {
			outcome = false;
			break;
		}

	return outcome;
}


void recursive(int X, std::vector<int>& w_one, std::vector<int>& w_two,
	std::vector<bool>& bool_w_one, std::vector<bool>& bool_w_two, std::vector<int>& used) {
		//std::cout << "uzylem funkcji recursive" << std::endl;
	int index = 0;

	for (int i = 0; i < w_one.size(); i++) {
		if (w_one[i] == X && bool_w_one[i] == false) {
			bool_w_one[i] = true;
			bool_w_two[i] = true;

			if (check(w_one[i], used))
				used.push_back(w_one[i]);
			recursive(w_two[i], w_one, w_two, bool_w_one, bool_w_two, used);
		}

		if (w_two[i] == X && bool_w_two[i] == false) {
			bool_w_one[i] = true;
			bool_w_two[i] = true;

			if (check(w_two[i], used))
				used.push_back(w_two[i]);
			recursive(w_one[i], w_one, w_two, bool_w_one, bool_w_two, used);
		}
	}

	if (check(X, used))
		used.push_back(X);

	for (int i = 0; i < used.size(); i++)
		if (used[i] == X)
			index = i - 1;

	if (index > -1) {
		recursive(used[index], w_one, w_two, bool_w_one, bool_w_two, used);
	}
}

bool chech_graph_consistency(std::vector<std::vector<int>>& graph) {
	//std::cout << "uzylem funkcji chech_graph_consistency" << std::endl;
	int outcome = true;
	std::vector<int> w_one;
	std::vector<int> w_two;
	std::vector<int> used;

	for (int i = 0; i < graph.size(); i++) {
		w_one.push_back(graph[i][0]);
		w_two.push_back(graph[i][1]);
	}

	std::vector<bool> bool_w_one(w_one.size(), false);
	std::vector<bool> bool_w_two(w_two.size(), false);


	bool_w_one[0] = true;
	bool_w_two[0] = true;

	used.push_back(w_one[0]);
	recursive(w_two[0], w_one, w_two, bool_w_one, bool_w_two, used);

	for (int i = 0; i < bool_w_one.size(); i++) {
		if (bool_w_one[i] == false or bool_w_two[i] == false) {
			outcome = false;
			break;
		}
	}

	return outcome;
}

//----------------------------------------------------------------------------------------------------------------------------
/*
std::string assign_element(int number) {
	std::string element = "";
	int count = 0;

	for (int i = 0; i < QUANTITY.size(); i++) {
		if (i == 0) {
			if (number <= QUANTITY[0]) {
				element = ELEMENTS[0];
				break;
			}
			count += QUANTITY[0];
		}
		else {
			if (number > QUANTITY[i - 1] and number <= QUANTITY[i] + count) {
				element = ELEMENTS[i];
				break;
			}
			count += QUANTITY[i];
		}
	}

	return element;
}
*/

std::string assign_element(int number) {
	//std::cout << "uzylem funkcji assign_element" << std::endl;
	return ELEMENTS_TABLE[number];
}

std::vector<std::string> create_elements_table() {
	std::vector<std::string> tmp;
	//std::cout << "uzylem funkcji create_elements_table" << std::endl;

	for (int i = 0; i < QUANTITY.size(); i++) {
		for (int j = 0; j < QUANTITY[i]; j++) {
			tmp.push_back(ELEMENTS[i]);
		}
	}

	return tmp;
}

//----------------------------------------------------------------------------------------------------------------------------

std::vector<std::vector<int>> transform_edges_to_neighbours(std::vector<std::vector<int>>& edges) {
	std::vector<std::vector<int>> neighbours;
	//std::cout << "uzylem funkcji transform_edges_to_neighbours" << std::endl;
	int max_edge = 0;

	for (int i = 0; i < edges.size(); i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			if (edges[i][j] > max_edge)
				max_edge = edges[i][j];
		}
	}


	for (int i = 0; i <= max_edge; i++) {
		int vertex = i;
		std::vector<int> tmp_vector;

		for (int j = 0; j < edges.size(); j++) {
			for (int k = 0; k < edges[j].size(); k++) {
				if (vertex == edges[j][k]) {
					if (k == 0)
						tmp_vector.push_back(edges[j][k + 1]);
					else
						tmp_vector.push_back(edges[j][k - 1]);
				}
			}
		}

		std::sort(tmp_vector.begin(), tmp_vector.end());
		neighbours.push_back(tmp_vector);
		tmp_vector.clear();
	}

	return neighbours;
}

//----------------------------------------------------------------------------------------------------------------------------

int check_occurence_of_element(std::string element, std::vector<std::string>& vec) {
	//std::cout << "uzylem funkcji check_occurence_of_element" << std::endl;
	int occurs = 0;

	if (std::find(vec.begin(), vec.end(), element) != vec.end())
		occurs = 1;

	return occurs;
}

int check_rules(std::vector<std::vector<int>>& neighbours) {
	//std::cout << "uzylem funkcji check_rules" << std::endl;
	int allow = 1;
	int flag = 0;

	for (int i = 0; i < neighbours.size(); i++) {
		if (flag)
			break;

		if (check_occurence_of_element(assign_element(i), NO_HALOGENS)) { //reguła z halogenkami
			for (int j = 0; j < neighbours[i].size(); j++) {
				if (flag)
					break;

				if (check_occurence_of_element(assign_element(neighbours[i][j]), HALOGENS)) {
					allow = 0;
					flag = 1;
					break;
				}
			}
		}

		if (check_occurence_of_element(assign_element(i), SN_RULE)) { //reguła S nie łączy się z N
			for (int j = 0; j < neighbours[i].size(); j++) {
				if (flag)
					break;

				if (check_occurence_of_element(assign_element(neighbours[i][j]), SN_RULE) && neighbours[i][j] != i) {
					allow = 0;
					flag = 1;
					break;
				}
			}
		}

		if (assign_element(i) == "O") {//reguła C-O-N
			int C_counter = 0;
			int N_counter = 0;

			for (int j = 0; j < neighbours[i].size(); j++) {
				if (assign_element(neighbours[i][j]) == "C")
					C_counter++;

				if (assign_element(neighbours[i][j]) == "N")
					N_counter++;
			}

			if (C_counter && N_counter) {
				allow = 0;
				flag = 1;
				break;
			}
		}
	}

	return allow;
}

/////////////////////////BAŁAGAN BAR/////////////////
int freeing = 0;
int allocating = 0;

struct AllocationMatrics {
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};
static AllocationMatrics s_AllocationMetrics;


void MemoryUsage() {
	std::cout << "Using " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

void* operator new(size_t size) {
	s_AllocationMetrics.TotalAllocated += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size) {
	s_AllocationMetrics.TotalFreed += size;
	//free(memory);
}

///////////////////////LABELING/////////////////////////////////////////////////////////////////
int** matrix;
bool is_table_done = false;

int label_len(int elements) {
	//std::cout << "uzylem funkcji label_len" << std::endl;
	int sum = 0;
	int iteration = elements;
	for (int i = 0; i < iteration; i++) {
		sum += elements;
		elements--;
	}
	return sum;
}

void change_matrix(int** matrix, std::vector<int>elements_order) {
	//std::cout << "uzylem funkcji change_matrix" << std::endl;
	int elements = elements_order.size();
	std::vector<int> no_need_change_again;
	for (int i = 0; i < elements; i++) {
		if (i == elements_order[i]) {//jeśli order mówi że element jest w dobrym miejscu, to patrz kolejny
			continue;
		}
		if (i == elements_order[elements_order[i]]) {
			no_need_change_again.push_back(elements_order[i]);
		}
		std::vector<int>::iterator it;

		it = find(no_need_change_again.begin(), no_need_change_again.end(), i);
		if (it == no_need_change_again.end()) {
			int* tmp1 = new int[elements];
			int* tmp2 = new int[elements];
			for (int m = 0; m < elements; m++) {
				if ((m == i || m == elements_order[i]) && matrix[i][elements_order[i]] > 0) {
					tmp1[m] = matrix[elements_order[i]][m];
					tmp2[m] = matrix[i][m];
					continue;
				}
				tmp1[m] = matrix[i][m];
				tmp2[m] = matrix[elements_order[i]][m];
			}
			for (int m = 0; m < elements; m++) {
				matrix[i][m] = tmp2[m];
				matrix[m][i] = tmp2[m];
				matrix[elements_order[i]][m] = tmp1[m];
				matrix[m][elements_order[i]] = tmp1[m];
			}
			delete[] tmp1;
			delete[] tmp2;
		}
	}
	/*std::cout << "\nprzed zmiania\n";
	for (int i = 0; i < elements; i++) {
		for (int j = 0; j < elements; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}*/
}

//1.3
int compare_labels(std::vector<std::vector<int>>& graph1, std::vector<int>& graph, int elements) {//return: -1(left graph1), 0 equals, 1 (graph)
	//std::cout << "uzylem funkcji compare_labels" << std::endl;
	//graph1 to lista krawedzi, graph to vector kolejnosci pierwiastkow
	//std::cout << "compare labels start "; MemoryUsage(); std::cout << "\n";
	int actual_elements_considered = elements;
	int label_length = label_len(actual_elements_considered);
	std::vector<int> label1;
	label1.reserve(label_length);
	std::vector<int> label2;
	label2.reserve(label_length);
	std::vector<int> label3;
	label3.reserve(label_length);

	if (!is_table_done) {
		matrix = new int* [actual_elements_considered];
		for (int i = 0; i < actual_elements_considered; i++) {
			matrix[i] = new int[actual_elements_considered];
			for (int j = 0; j < actual_elements_considered; j++) {
				matrix[i][j] = 0;
			}
		}
		is_table_done = true;
	}
	else {
		for (int i = 0; i < actual_elements_considered; i++) {
			for (int j = 0; j < actual_elements_considered; j++) {
				matrix[i][j] = 0;
			}
		}
	}

	//tworzenie macierzy aktualnego grafu
	for (int i = 0; i < graph1.size(); i++) {
		matrix[graph1[i][0]][graph1[i][1]]++;//bo mogą być krawędzie wielokrotne
		matrix[graph1[i][1]][graph1[i][0]]++;//bo macierz jest symetryczna
	}

	//zczytanie z matrycy etykiety
	for (int i = 0; i < actual_elements_considered; i++) {
		for (int j = i; j < actual_elements_considered; j++) {//skoro matryca jest symetryczna to wystarczy zczytać połowę
			label1.push_back(matrix[i][j]);
		}
	}

	//zczytanie z matrycy etykiety sposobem piotra
	//for (int i = 0; i < actual_elements_considered; i++) {
	//	for (int j = i; j < actual_elements_considered; j++) {//skoro matryca jest symetryczna to wystarczy zczytać połowę
	//		label3.push_back(matrix[graph[i]][graph[j]]);
	//	}
	//}

	/*std::cout << "\n";
	for (int i = 0; i < actual_elements_considered; i++) {
		for (int j = 0; j < actual_elements_considered; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "taka zmiana\n";
	for (int i = 0; i < graph.size(); i++) {
		std::cout << graph[i] << " ";
	}
	std::cout << "\n";*/

	//std::cout << "before change matrix"; MemoryUsage(); std::cout << "\n";
	change_matrix(matrix, graph);//działa na oryginalnej matrix, dlatego nie potrzebne przypisanie
	//std::cout << "after change matrix"; MemoryUsage(); std::cout << "\n";

	//zczytanie z matrycy zmienionej etykiety
	for (int n = 0; n < actual_elements_considered; n++) {
		for (int m = n; m < actual_elements_considered; m++) {//jak wywali błąd to zmień spowrotem na 0 xD
			label2.push_back(matrix[n][m]);
		}
	}

	/*for (int n = 0; n < label_length; n++) {
		if (label2 != label3) {
			std::cout << "sth wrong\n";

			for (int i = 0; i < label_length; i++) {
				std::cout<<label2[i]<<" ";
			}
			std::cout << "\n";
			for (int i = 0; i < label_length; i++) {
				std::cout << label3[i] << " ";
			}
			std::cout << "\n";
			break;
		}
	}*/

	//sprawdzenie czy etykieta jest mniejsza czy większa
	//std::cout << "\n" << label1 << "\n" << label2 << "\n";
	for (int n = 0; n < label_length; n++) {
		if (label1[n] > label2[n]) {
			//std::cout << "lewa większa\n";
			label1.clear();
			label2.clear();
			return -1;
		}
		else if (label1[n] < label2[n]) {
			label1.clear();
			label2.clear();
			return 1;//skoro nasza obecna etykieta jest mniejsza, to graf nie jest kanoniczny, koniec dyskusji
			//std::cout << "prawa większa\n";
		}
	}

	//usuwanko matrix
	//std::cout << "b matrix delete "; MemoryUsage(); std::cout << std::endl;
	//for (int i = 0; i < actual_elements_considered; i++) {
	//	delete[] matrix[i];
	//}
	//delete[] matrix;
	//std::cout << "a matrix delete "; MemoryUsage(); std::cout << std::endl;

	//std::cout << "before clearing labels in compare labesls "; MemoryUsage(); std::cout << "\n";
	label1.clear();
	label2.clear();
	//std::cout << "after clearing labels in compare labesls "; MemoryUsage(); std::cout << "\n";

	//std::cout << "end of compare labels"; MemoryUsage(); std::cout << "\n";
	return 0;//skoro żadna zmiana nie spowodowała większej etykiety to znaczy że nasz jest największa
}

bool is_label_the_biggest(std::vector<std::vector<int>>& graph_to_check, int elements) {//graph_to_check jest listą krawędzi
	//std::cout << "uzylem funkcji is_label_the_biggest" << std::endl;
	//std::cout << "dupa\n";
	std::vector<int>solution;
	solution.reserve(elements);
	std::vector<int>to_use;
	int last_used = -1;//-1 bo to liczba zawsze mniejsza niż jakikolwiek wierzchołek w grafie
	bool still_counting = true;

	do {
		if (to_use.size() == 0) {
			if (solution.size() == elements) {//gdy nie ma już więcej pierwiastków do dodania
				last_used = solution[solution.size() - 1];
				solution.pop_back();
				to_use.push_back(last_used);
			}
			else {//kolejny rodzaj do doadania
				int element = solution.size();
				std::string type_of_elements = assign_element(element);//przypisanie następnego typu; size() więc nie trzeba +1
				while (element < elements && assign_element(element) == type_of_elements) {
					to_use.push_back(element);
					element++;
				}
			}
		}
		int index = -1;
		std::vector<int>::iterator it = to_use.begin();
		for (int i = 0; i < to_use.size(); i++) {//znajdź na liscie to_use co dalej używamy i zapisz index
			if (to_use[i] > last_used) {
				index = i;
				break;
			}
			it++;
		}
		if (index > -1) {//jeśli został znaleziony jakiś pierwiastek do dodania do rozwiązania
			solution.push_back(to_use[index]);
			to_use.erase(it);//już wykorzystany, więc usuwanko
			last_used = -1;//żeby na nowym poziomie drzewa zaczynać od początku
		}
		else {
			if (solution.size() == elements || (solution.size() > 1 && assign_element(solution.size() - 1) != assign_element(solution.size()))) {
				//w takim razie zaraz usuwając zmienimy blok rodzaju pierwiastków
				to_use.clear();//skoro zmieniamy blok to trzeba zrobić porządki
				last_used = solution[solution.size() - 1];
				to_use.push_back(last_used);
				solution.pop_back();
			}
			else if (solution.size() > 0) {
				//tu poprostu usuwamy
				last_used = solution[solution.size() - 1];
				it = to_use.begin();
				for (int i = 0; i < to_use.size(); i++) {
					if (to_use[i] > last_used) {
						break;
					}
					it++;
				}
				to_use.insert(it, last_used);
				solution.pop_back();
			}
			//jeśli solution.size()==0 to nie mamy co usunąć a może tu takie wpaść (chyba xD)
		}
		if (solution.size() == elements) {
			/*std::cout << "\n";
			for (int n = 0; n < solution.size(); n++) {
				std::cout << solution[n] << " ";
			}
			std::cout << "\n";*/
			//std::cout << "before compare labels"; MemoryUsage(); std::cout << "\n";
			if (compare_labels(graph_to_check, solution, elements) == 1) {//1-czyli znaleziono takie ustawienie pierw, ze jest lepsze niz to co pryszło do funkcji
				solution.clear();
				solution.clear();
				to_use.clear();
				to_use.clear();
				return false;
			}//jeśli znaleziona przez nas jest większa niż grafu przesłanego do funkcji to nie jest on kanoniczny, więc zwracamy false
			//jeśli etykiety są równe lub przesłanego grafu jest większa to szukamy dalej czy istnieje większa
			//std::cout << "after compare labels "; MemoryUsage(); std::cout << "\n";
		}
		if (solution.size() == 0 && assign_element(last_used) != assign_element(last_used + 1)) {
			still_counting = false;
		}

	} while (still_counting);

	solution.clear();
	solution.clear();
	to_use.clear();
	to_use.clear();

	//std::cout << "after delete in is_label_the_biggest "; MemoryUsage(); std::cout << "\n";

	return true;
}
///////////////////////ISOMORPHISM//////////////////////////////////////////////////////////////
bool neighbours_recursive(std::vector<std::vector<int>>& graph1, std::vector<std::vector<int>>& graph2, std::vector<int>& vertexes1, std::vector<int>& vertexes2, int vertex1, int vertex2) {
	//std::cout << "uzylem funkcji neighbours_recursive" << std::endl;
	std::vector<int> neighbours1, neighbours2;
	int multiplicity_of_vertex = 1;//krotność krawędzi do danego sąsiada
	int checked1 = 0;//przechowuje ile sąsiadów wierzchołka grafu1 było już wcześniej sprawdzanych (ile razy continue bo sąsiad w vertexes1) //NEW

	//próba czy to dobre
	//if (vertexes1.end() == (std::find(vertexes1.begin(), vertexes1.end(), vertex1)))//jeżeli tego z którego startujemy nie ma jeszcze a liście rozpatzronych
	//	vertexes1.push_back(vertex1);
	//koniec próby

	for (int i = 0; i < graph1[vertex1].size(); i++) {//dla każdego sąsiada wierzchołka grafu1
		if (vertexes1.end() != (std::find(vertexes1.begin(), vertexes1.end(), graph1[vertex1][i]))) {//jeżeli ten wierzchołek był już rozpatrzony
			checked1++;
			continue;
		}
		vertexes1.push_back(graph1[vertex1][i]); //dodanie do listy rozpatrywanych
		multiplicity_of_vertex = 1;//nowo rozpatrywany -> jedno wystąpienie ma napewno

		if (neighbours1.end() == (std::find(neighbours1.begin(), neighbours1.end(), graph1[vertex1][i]))) {//jeżeli nie ma takiego wierzchołka jeszcze wpisanego na listę sąsiadów1

			neighbours1.push_back(graph1[vertex1][i]);

			while (i != graph1[vertex1].size() - 1 && graph1[vertex1][i] == graph1[vertex1][i + 1]) {//jeśli to nie koniec listy i następny wierzchołek to ten sam
				multiplicity_of_vertex++;
				i++;
			}

			int multiplicity_of_vertex2 = 1;//krotność wierzchołka w drugim grafie

			for (int j = 0; j < graph2[vertex2].size(); j++) {//dla każdego sąsiada wierzchołka grafu2
				if (vertexes2.end() == (std::find(vertexes2.begin(), vertexes2.end(), graph2[vertex2][j]))) {//żeby nie dwa razy ten sam
					vertexes2.push_back(graph2[vertex2][j]); //dodanie do listy rozpatrywanych, musi być tu żeby w kolejnych wywołaniach
															//rekurencji było widać że już jest użyty do czegoś
					multiplicity_of_vertex2 = 1;

					if (neighbours2.end() == (std::find(neighbours2.begin(), neighbours2.end(), graph2[vertex2][j]))) {//jeżeli nie ma takiego wierzchołka jeszcze wpisanego na listę sąsiadów1

						neighbours2.push_back(graph2[vertex2][j]);

						while (j != graph2[vertex2].size() - 1 && graph2[vertex2][j] == graph2[vertex2][j + 1]) {//jeśli to nie koniec listy i następny wierzchołek to ten sam
							multiplicity_of_vertex2++;
							j++;
						}
						if (multiplicity_of_vertex == multiplicity_of_vertex2 && graph1[vertex1].size() == graph2[vertex2].size() && assign_element(graph1[vertex1][i]) == assign_element(graph2[vertex2][j])) {
							if (neighbours_recursive(graph1, graph2, vertexes1, vertexes2, graph1[vertex1][i], graph2[vertex2][j])) {
								break;//wierzchołek 2 grafu dopasowany do wierzchołka z pierwszego
							}
							else if (j == graph2[vertex2].size() - 1) {
								if (vertexes2.size() > 0) {
									vertexes2.pop_back();
									neighbours2.pop_back();//NEW
								}
								return false;//rozpatrzamy go tutaj, ale skoro się nie dopasował to żeby mógł z innym v1 się dopasować to trzeba go zdjac z vec
							}
							else {
								if (vertexes2.size() > 0) {
									vertexes2.pop_back();//bo niedopasowane
									vertexes1.pop_back();//był rozpatrzany, ale nic się do niego nei dopasowało, więc musi mieć możliwość jeszcze raz próbować sie dopasować//NEW
									neighbours2.pop_back();//NEW
								}
							}
						}
						else if (j == graph2[vertex2].size() - 1) {
							/*vertexes1.pop_back();
							vertexes2.pop_back();*/
							if (vertexes2.size() > 0) {
								vertexes2.pop_back();//bo niedopasowane
								neighbours2.pop_back();//NEW
							}
							return false;
						}
						else {
							if (vertexes2.size() > 0) {
								vertexes2.pop_back();//bo niedopasowane
								neighbours2.pop_back();//NEW
							}
						}
					}
					else if (j == graph2[vertex2].size() - 1) {//jeśli żaden z sąsiadów2 nie dopasował się do sąsiada1
							/*vertexes1.pop_back();
							vertexes2.pop_back();*/
						if (vertexes2.size() > 0)
							vertexes2.pop_back();
						return false;
					}
					else {
						if (vertexes2.size() > 0)
							vertexes2.pop_back();
					}
				}
				else if (j == graph2[vertex2].size() - 1) {//jeśli ostatni sąsiad już był rozpatrywany i nic sie nie dopasowało
					return false;
				}
			}
		}
	}
	if (checked1 == graph1[vertex1].size()) {//skoro wszyscy sąsiedzi wierzchołka grafu1 byli już sprawdzeni, to trzeba sprawdzić czy w grafie2 też jest tak samo//NEW
		if (checked1 == graph2[vertex2].size()) {
			for (int j = 0; j < graph2[vertex2].size(); j++) {//dla każdego sąsiada wierzchołka grafu2
				if (vertexes2.end() == (std::find(vertexes2.begin(), vertexes2.end(), graph2[vertex2][j]))) {
					return false;//skoro wszyscy sąsiedzi wg1 byli sprawdzenie to czemu nie byli wszyscy wg2?! grafy nie są takie same!
				}
			}
		}
		else {
			return false;
		}
	}
	return true;
}

int used_vertices(std::vector<std::vector<int>>& graph) {
	//std::cout << "uzylem funkcji used_vertices" << std::endl;
	/*int used_vertices = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (graph.size() > 0) {
			used_vertices++;
		}
	}
	return used_vertices; */
	int used_vertices = 0;
	std::set<int> set1;
	for (int i = 0; i < graph.size(); i++) {
		set1.insert(graph[i][0]);
		set1.insert(graph[i][1]);
	}
	return set1.size();
}


void multiplicity_of_elements(std::vector<std::vector<int>>& graph, std::map<std::string, int>& map_of_degrees, std::vector<std::string>& keys) {
	//std::cout << "uzylem funkcji multiplicity_of_elements" << std::endl;
	for (int i = 0; i < graph.size(); i++) {
		///poprawność przekazywanych parametrów
		if (graph.size() > 0) {//jeśli wierzchołek jest połączony w jaki kolwiek sposób z grafem
			std::string element = assign_element(i);
			if (keys.end() == (std::find(keys.begin(), keys.end(), element))) {
				map_of_degrees[element] = 1;
				//map_of_degrees.insert(std::make_pair(element, 1));
				keys.push_back(element);
			}
			else {
				map_of_degrees[element]++;
			}
		}
	}
}

void multiplicity_of_degrees(std::vector<std::vector<int>>& graph, std::map<int, int>& map_of_degrees, std::vector<int>& keys) {
	//std::cout << "uzylem funkcji multiplicity_of_degrees" << std::endl;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].size() != 0) {//jeśli wierzchołek ma wgl sąsiadów, bo inaczej go traktujemy jako nie istniejący jeszcze w grafie
			if (keys.end() == (std::find(keys.begin(), keys.end(), graph[i].size()))) {//jeśli w kluczach nie ma jeszcze zadanego stopnia
				map_of_degrees[graph[i].size()] = 1;//dodaj taki do mapy
				keys.push_back(graph[i].size());
			}
			else {
				map_of_degrees[graph[i].size()]++;//inkrementuj już istniejący
			}
		}
	}
}

bool isomorphism24(Graph& done, Graph& undone) {
	//std::cout << "uzylem funkcji isomorphism24" << std::endl;
	std::vector<int> vertexes1, vertexes2;
	std::vector<std::vector<int>> graph_lvl = obtain_level(done.single_graph, undone.level);

	if (used_vertices(graph_lvl) == used_vertices(undone.single_graph)) {//jeśli oba grafy mają tyle samo wierzchołków (przy wielokrotnych może być inna liczba
	//if (true) {
		std::map <std::string, int> elements_usage1;
		std::vector<std::string>keys_elements1;
		std::map <std::string, int> elements_usage2;
		std::vector<std::string>keys_elements2;


		std::vector<std::vector<int>> graph_pom = transform_edges_to_neighbours(graph_lvl);
		multiplicity_of_elements(graph_pom, elements_usage1, keys_elements1);
		graph_pom = transform_edges_to_neighbours(undone.single_graph);
		multiplicity_of_elements(graph_pom, elements_usage2, keys_elements2);
		//delete &graph_pom;

		if (keys_elements1.size() == keys_elements2.size()) {//jeśli mają równą liczbę rodzai pierwiastków
			for (int i = 0; i < keys_elements1.size(); i++) {
				if (elements_usage2.find(keys_elements1[i]) == elements_usage2.end())//jeśli pierwiastka z pierwszego grafu nie ma w drugim
					return false;
				if (elements_usage1[keys_elements1[i]] != elements_usage1[keys_elements1[i]])//jeśli nie zgadzają się liczebności pierwiastków w grafach
					return false;
			}
			std::map < int, int > degrees_usage1;
			std::vector<int>keys_degrees1;
			std::map < int, int > degrees_usage2;
			std::vector<int>keys_degrees2;

			graph_pom = transform_edges_to_neighbours(graph_lvl);
			multiplicity_of_degrees(graph_pom, degrees_usage1, keys_degrees1);
			graph_pom = transform_edges_to_neighbours(undone.single_graph);
			multiplicity_of_degrees(graph_pom, degrees_usage2, keys_degrees2);
			//delete &graph_pom;

			if (keys_degrees1.size() == keys_degrees2.size() && keys_degrees1.size() > 0) {//jeśli taka sama ilość różnych stopni
				//int min = keys_degrees1.size();//krotność stopnia
				//int minv = keys_degrees1.size();//stopień
				int min = degrees_usage1[keys_degrees1[0]];
				int minv = keys_degrees1[0];
				for (int i = 0; i < keys_degrees1.size(); i++) {
					if (min > degrees_usage1[keys_degrees1[i]]) {
						min = degrees_usage1[keys_degrees1[i]];
						minv = keys_degrees1[i];
					}
					if (degrees_usage2.find(keys_degrees1[i]) == degrees_usage2.end())//jeśli pierwiastka z pierwszego grafu nie ma w drugim
						return false;
					if (degrees_usage1[keys_degrees1[i]] != degrees_usage2[keys_degrees1[i]])//jeśli nie zgadzają się liczebności pierwiastków w grafach
						return false;
				}
				int v1; //przechowuje wierzchołek startowy pierwszego grafu

				graph_pom = transform_edges_to_neighbours(graph_lvl);
				for (int i = 0; i < graph_pom.size(); i++) {
					if (graph_pom[i].size() == minv) {
						v1 = i;
						break;
					}
				}
				graph_pom = transform_edges_to_neighbours(undone.single_graph);
				for (int i = 0; i < graph_pom.size(); i++) {
					if (graph_pom[i].size() == minv) {//wierzchołki na tym samym st
						if (assign_element(v1) == assign_element(i)) {//te same pierwiastki
							std::vector<std::vector<int>> done_pom = transform_edges_to_neighbours(graph_lvl);
							std::vector<std::vector<int>> undone_pom = transform_edges_to_neighbours(undone.single_graph);
							vertexes1.push_back(v1); vertexes2.push_back(i);
							if (neighbours_recursive(done_pom, undone_pom, vertexes1, vertexes2, v1, i))//i bo index rep wierzchołek to którek jest przyp vector sąsiadów
								return true;//jeśli rekurencyjna zwróciła true
							vertexes1.clear();//żeby na nowo mogło się liczyć dla kolejnej pary
							vertexes2.clear();
						}
					}
				}
			}
		}
	}
	return false;
}

//////////////////////TREE.CPP//////////////////////////////////////////////////////////////////
std::map<std::string, std::vector<int>> elements_bonds = {
	//https://www.thoughtco.com/valences-of-the-elements-chemistry-table-606458
	//https://scientiaeetdidactics.files.wordpress.com/2015/03/surrwcob_setd_2015_ii.pdf
	{ "H", {1} },
	{ "C", {4} },
	{ "O", {2} },
	{ "N", {3, 5} }, //?
	{ "P", {3, 5} },
	{ "Na", {1} },
	{ "K", {1} },
	{ "Br", {1} },
	{ "I", {1} },
	{ "F", {1} },
	{ "Cl", {1} },
	{ "S", {2} },
	{ "Li", {1} }
};

int hydrogens = 0;
int mode = 0;

void set_mode(int mode_to_set) {
	//std::cout << "uzylem funkcji set_mode" << std::endl;
	mode = mode_to_set;
}

int count_hydrogens(int elements) {//H muszą być na końcu wzoru!
	int number = 0;
	for (int i = elements - 1; i >= 0; i--) {
		std::string wodor(1,'H');
		std::string element = assign_element(i);
		element = element.substr(0, element.size()-1);
		if (element == wodor) {
			number++;
		}else{
			break;
		}
	}
	return number;
}

int is_it_promissing(int elements, int hydrogens) {//sprawdzanie czy ilość wodorów łapie się między najmniejszą a największą możliwą ilością dostępnych wiązań
	//std::cout << "uzylem funkcji is_it_promissing" << std::endl;
	int min = 0;
	int max = 0;

	for (int i = 0; i < elements; i++) {
		min += elements_bonds[assign_element(i)][0];
		max += elements_bonds[assign_element(i)][elements_bonds[assign_element(i)].size() - 1];
	}

	if (hydrogens < min) {//wodorów jest mniej niż najmniejsza ilość wiązań
		return -1;
	}
	else if (hydrogens > min && hydrogens < max) {//ilość wodorów może być ok
		return 0;
	}
	else {//wodorów jest więcej niż największa ilość wiązań
		return 1;
	}
}

bool is_it_good(std::vector<int>& solution, int hydrogens) {
	//std::cout << "uzylem funkcji is_it_good" << std::endl;
	int sum = 0;
	for (int i = 0; i < solution.size(); i++) {
		sum += solution[i];
	}
	if (sum == hydrogens) {
		return true;
	}
	return false;
}

void delet_from_set(std::set<int>& vertices, std::vector<int>& vectored, int delet) {
	//std::cout << "uzylem funkcji delet_from_set" << std::endl;
	if (vectored[delet] == 1) {
		vertices.erase(delet);
		vectored[delet]--;
	}
	else {
		vectored[delet]--;
	}
}


void tree_solution(int elements, std::vector<Graph>& good_graphs) {
	//std::cout << "uzylem funkcji tree_solution" << std::endl;
	int tab[2] = { 0, 1 };
	int kroki = 0;
	bool possible_multiple_edge = true;
	Graph current;//= new Graph();
	std::vector<int> edge;
	std::set<int> used_vertices;
	std::vector<int> vertices;//przechowuje ile razy dodawano go do zbioru
	vertices.reserve(elements);

	for (int i = 0; i < elements; i++) {
		vertices.push_back(0);
	}

	while (1) {

		/*if (good_graphs.size() == 2 && current.single_graph.size() == 7 && current.single_graph[6][0] == 2 && current.single_graph[6][1] == 7) {
			std::cout << "dupa\n";
		}
		if (current.single_graph.size() == 4) {
			std::cout << "dupa4\n";
		}
		if (current.single_graph.size() == 5) {
			std::cout << "dupa5\n";
		}
		if (current.single_graph.size() == 6) {
			std::cout << "dupa6\n";
		}
		if (current.single_graph.size() == 7) {
			std::cout << "dupa7\n";
		}
		if (current.single_graph.size() == 8) {
			std::cout << "dupa8\n";
		}*/

		if (possible_multiple_edge) {
			std::string elem1 = assign_element(tab[1]);//sprawdzamy czy aktualna może być zwielokrotniona
			std::string elem2 = assign_element(tab[0]);
			int degree1 = 0;
			int degree2 = 0;

			for (int i = 0; i < current.single_graph.size(); i++) {
				if (current.single_graph[i][0] == tab[1] || current.single_graph[i][1] == tab[1]) {
					degree1++;
				}
				if (current.single_graph[i][0] == tab[0] || current.single_graph[i][1] == tab[0]) {
					degree2++;
				}
			}

			std::vector<int> elem_degrees = elements_bonds[elem2];
			if (elem_degrees[elem_degrees.size() - 1] > degree2) {//jeśli nie przekroczymy stopnia pierwszej części krawędzi
				elem_degrees = elements_bonds[elem1];//to sprawdź drugą
				if (elem_degrees[elem_degrees.size() - 1] > degree1) {//jeśli nie przekroczy
					edge.clear();
					edge.push_back(tab[0]); edge.push_back(tab[1]);
					used_vertices.insert(tab[0]); used_vertices.insert(tab[1]);
					vertices[tab[0]]++; vertices[tab[1]]++;
					kroki++;
					current.single_graph.push_back(edge);//dodaj taką krawędź
					current.level++;
				}
				else {
					possible_multiple_edge = false;//jeśli aktualnie krawędź nie może być zwielokrotniona ustaw boolowska na fałsz
					continue;//żeby rozpatrzył kolejną
				}
			}
			else {
				possible_multiple_edge = false;
				continue;
			}
		}
		else {
			bool next_edge_possible = true;
			//DODAWANIE KRAWĘDZI---------------------------------------------------------------------------------------------------------------------------------------------------------
			if (tab[1] < elements - 1) {//elements to ilość, vector numeruje od zera stąd -1 bo to opcja zeby dodac jeszcze jakas
				if (tab[0] > tab[1] + 1) {//żeby pierwszy składnik krawędzi był mniejszy
					tab[1]++;
					possible_multiple_edge = false;
					continue;
				}
				if (tab[0] == tab[1] + 1) {
					tab[1]++;
					possible_multiple_edge = false;
					continue;
				}
				//żeby nie tworzyły się strukturki typy H-H
				if (elements_bonds[assign_element(tab[0])] == std::vector<int>{1}&& elements_bonds[assign_element(tab[1] + 1)] == std::vector<int>{1}) {
					tab[1]++;
					possible_multiple_edge = false;
					continue;
				}
				std::string elem1 = assign_element(tab[1] + 1);//sprawdza jaki pierwiastek kryje się pod kolejnym wierzchołkiem
				std::string elem2 = assign_element(tab[0]);//pierwiastek w pierwszej części krawędzi
				int degree1 = 0;
				int degree2 = 0;

				for (int i = 0; i < current.single_graph.size(); i++) {
					if (current.single_graph[i][0] == tab[1] + 1 || current.single_graph[i][1] == tab[1] + 1) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi;
						//krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree1++;
					}
					if (current.single_graph[i][0] == tab[0] || current.single_graph[i][1] == tab[0]) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi;
						//krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree2++;
					}
				}

				std::vector<int> elem_degrees = elements_bonds[elem2];
				if (elem_degrees[elem_degrees.size() - 1] > degree2) {//jeśli nie przekroczymy stopnia pierwszej części krawędzi
					elem_degrees = elements_bonds[elem1];//to sprawdź drugą
					if (elem_degrees[elem_degrees.size() - 1] > degree1) {//jeśli nie przekroczy
						edge.clear();
						edge.push_back(tab[0]); edge.push_back(tab[1] + 1);
						used_vertices.insert(tab[0]); used_vertices.insert(tab[1] + 1);
						vertices[tab[0]]++; vertices[tab[1] + 1]++;
						current.single_graph.push_back(edge);//dodaj taką krawędź
						current.level++;
						kroki++;
						tab[1]++;//zaktualizuj ost dod
						possible_multiple_edge = true;
					}
					else {
						tab[1]++;//zmienić żeby wiadomo co ostatnio rozpatrywane, ale nie dodawać
						continue;//żeby rozpatrzył kolejną
					}
				}
				else {
					tab[1]++;
					continue;
				}
			}
			else if (tab[0] + 1 < elements) {//skoro drugiego elementu krawędzi nie da się zmienić bo już ostatni to zmień pierwszy
				if (tab[0] + 1 > 0) {//żeby pierwszy składnik krawędzi był mniejszy
					tab[0]++;
					tab[1] = 0;
					possible_multiple_edge = false;
					continue;
				}
				std::string elem1 = assign_element(tab[0] + 1);//sprawdza jaki pierwiastek kryje się pod kolejnym wierzchołkiem
				std::string elem2 = assign_element(0);//pierwiastek w pierwszej części krawędzi
				int degree1 = 0;
				int degree2 = 0;

				for (int i = 0; i < current.single_graph.size(); i++) {
					if (current.single_graph[i][0] == tab[0] + 1 || current.single_graph[i][1] == tab[0] + 1) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi;
						//krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree1++;
					}
					if (current.single_graph[i][0] == 0 || current.single_graph[i][1] == 0) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi; krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree2++;
					}
				}

				std::vector<int> elem_degrees = elements_bonds[elem1];
				if (elem_degrees[elem_degrees.size() - 1] > degree1) {//jeśli nie przekroczymy stopnia pierwszej części krawędzi
					elem_degrees = elements_bonds[elem2];//to sprawdź drugą
					if (elem_degrees[elem_degrees.size() - 1] > degree2) {//jeśli nie przekroczy
						edge.clear();
						edge.push_back(tab[0] + 1); edge.push_back(0);
						used_vertices.insert(tab[0] + 1); used_vertices.insert(0);
						vertices[tab[0] + 1]++; vertices[0]++;
						current.single_graph.push_back(edge);//dodaj taką krawędź
						current.level++;
						kroki++;
						tab[0]++;//zaktualizuj ost dod
						tab[1] = 0;
						possible_multiple_edge = true;
					}
					else {
						tab[0]++;//zmienić żeby wiadomo co ostatnio rozpatrywane, ale nie dodawać
						tab[1] = 0;
						continue;//żeby rozp kolejną
					}
				}
				else {
					tab[0]++;
					tab[1] = 0;
					continue;
				}
			}
			else {
				if (tab[0] == elements - 1 && tab[1] == elements - 1 && current.single_graph.empty())
					break;

				tab[0] = current.single_graph[current.single_graph.size() - 1][0];//przypisz pierwszą część krawędzi ostatniej jaka jest zapisana w grafie
				tab[1] = current.single_graph[current.single_graph.size() - 1][1];
				delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
				current.single_graph.pop_back();
				current.level--;

				if (tab[0] == elements - 1 && tab[1] == elements - 2) {//skoro to była ostatnia możliwa to tzreba nie tylko ją ale i poprzednią
					//usunąć, żeby dało się rozpatrywać dalej, a do tab wpisać rzeczy z przedostatniej żeby to ją sprawdzać dalej
					tab[0] = current.single_graph[current.single_graph.size() - 1][0];
					tab[1] = current.single_graph[current.single_graph.size() - 1][1];
					delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
					current.single_graph.pop_back();
					current.level--;
				}

				continue;//nie byłą dodana żadna krawędź, więc próbuj dalej
			}
		}

		//---------------------------------------------------------------------------------------------------------------------------------------------------------
		bool sth_isomorphic = false;

		//std::cout << "before switch case "; MemoryUsage(); std::cout << "\n";
		switch (mode)
		{
		case(0)://IZOMORFIZM
			for (int i = 0; i < good_graphs.size(); i++) {
				if (isomorphism24(good_graphs[i], current)) {
					sth_isomorphic = true;
					break;
				}
			}
			break;
		case(1)://ETKIETOWANIE
			if (!is_label_the_biggest(current.single_graph, elements)) {
				sth_isomorphic = true;
			}
			break;
		default:
			std::cout << "wrong mode!\n";
			break;
		}
		//std::cout << "after switch case "; MemoryUsage(); std::cout << "\n\n";

		if (sth_isomorphic) {
			tab[0] = current.single_graph[current.single_graph.size() - 1][0];//przypisz pierwszą część krawędzi ostatniej jaka jest zapisana w grafie
			tab[1] = current.single_graph[current.single_graph.size() - 1][1];
			delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
			current.single_graph.pop_back();//usuń ostatnią krawędź
			possible_multiple_edge = false;//żeby nie podkusiło programu się zapętlić
			current.level--;
			if (current.single_graph.empty())
				break;
			continue;//nie była dodana żadna krawędź, więc próbuj dalej
		}
		else if (used_vertices.size() == elements && chech_graph_consistency(current.single_graph)) {//nie jest izomorficzny z żadnym z powstałych
			bool done = true;

			for (int i = 0; i < elements; i++) {//dla każdego pierwiastka w grafie
				int degree = 0;
				bool proper_degree = false;//moga być problemy bo zmieniłam
				for (int j = 0; j < current.single_graph.size(); j++) {//sprawdź na którym jest stopniu obecnie w grafie
					if (current.single_graph[j][0] == i || current.single_graph[j][1] == i) {
						degree++;
					}
					if (j == current.single_graph.size() - 1) {
						std::vector<int> possible_degrees = elements_bonds[assign_element(i)];
						//bool proper_degree = false;
						for (int k = 0; k < possible_degrees.size(); k++) {
							if (degree == possible_degrees[k]) {//jeśli jest to jeden z dopuszczalnych stopni
								proper_degree = true;
								break;
							}
						}

						if (!proper_degree) {//jesli jest na niewłaściwym stopniu
							done = false;
							break;
						}
					}
				}
				if (!proper_degree) {//jesli jest na niewłaściwym stopniu
					break;
				}
			}

			if (done) {
				Graph good_graph;// = new Graph();//dodawanie poprawnego na listę
				good_graph = current;//
				std::vector<std::vector<int>> good_graph_neighbours = transform_edges_to_neighbours(good_graph.single_graph);
				if (check_rules(good_graph_neighbours)) {//sprawdzanie zasad chemicznych
					good_graphs.push_back(good_graph);
				}
				//good_graphs.push_back(good_graph);
				//usuwanie krawędzi z poprawnego żeby szukać dalej rozwiązań
				tab[0] = current.single_graph[current.single_graph.size() - 1][0];
				tab[1] = current.single_graph[current.single_graph.size() - 1][1];
				delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
				possible_multiple_edge = false; //bo skoro ją odrzucamy to nie można jej jeszcze raz sprawdzać bo pętla!
				current.single_graph.pop_back();
				current.level--;
				good_graph.~Graph();
			}
		}
	}
	edge.clear();
	vertices.clear();
	current.~Graph();
}



void tree_solution_without_hydrogens(int elements, std::vector<Graph>& good_graphs) {
	//std::cout << "uzylem funkcji tree_solution_without_hydrogens" << std::endl;
	hydrogens = count_hydrogens(elements);
	int actual_elements_to_consider = elements - hydrogens;
	int tab[2] = { 0, 1 };
	int kroki = 0;
	bool possible_multiple_edge = true;
	Graph current; // = new Graph();
	std::vector<int> edge;
	std::set<int> used_vertices;
	std::vector<int> vertices;//przechowuje ile razy dodawano go do zbioru
	vertices.reserve(actual_elements_to_consider);

	if (actual_elements_to_consider == 1) {//tak czasem bywa
		std::vector<int> possible_degrees = elements_bonds[assign_element(0)];
		bool good = false;

		for (int i = 0; i < possible_degrees.size(); i++) {
			if (hydrogens == possible_degrees[i]) {//jeśli jest to jeden z dopuszczalnych stopni
				good = true;
				break;
			}
		}

		if (good) {
			Graph good_graph = current;
			int hydrogen_number = 0;//bo w sumie to wierzchołi są ponumerowane <0,actual_ele_to_cons>, więc wodory powinny zaczynać od act_elem...
			for (int j = 0; j < hydrogens; j++) {
				std::vector<int> edge;
				edge.push_back(0);
				edge.push_back(actual_elements_to_consider + hydrogen_number);
				good_graph.single_graph.push_back(edge);
				hydrogen_number++;
			}
			std::vector<std::vector<int>> good_graph_neighbours = transform_edges_to_neighbours(good_graph.single_graph);
			if (check_rules(good_graph_neighbours)) {
				good_graphs.push_back(good_graph);
			}
			//good_graphs.push_back(good_graph);
		}
		return;
	}

	for (int i = 0; i < actual_elements_to_consider; i++) {
		vertices.push_back(0);
	}

	while (1) {
		if (possible_multiple_edge) {
			std::string elem1 = assign_element(tab[1]);//sprawdzamy czy aktualna może być zwielokrotniona
			std::string elem2 = assign_element(tab[0]);
			int degree1 = 0;
			int degree2 = 0;

			for (int i = 0; i < current.single_graph.size(); i++) {
				if (current.single_graph[i][0] == tab[1] || current.single_graph[i][1] == tab[1]) {
					degree1++;
				}
				if (current.single_graph[i][0] == tab[0] || current.single_graph[i][1] == tab[0]) {
					degree2++;
				}
			}

			std::vector<int> elem_degrees = elements_bonds[elem2];
			if (elem_degrees[elem_degrees.size() - 1] > degree2) {//jeśli nie przekroczymy stopnia pierwszej części krawędzi
				elem_degrees = elements_bonds[elem1];//to sprawdź drugą
				if (elem_degrees[elem_degrees.size() - 1] > degree1) {//jeśli nie przekroczy
					edge.clear();
					edge.push_back(tab[0]); edge.push_back(tab[1]);
					used_vertices.insert(tab[0]); used_vertices.insert(tab[1]);
					vertices[tab[0]]++; vertices[tab[1]]++;
					kroki++;
					current.single_graph.push_back(edge);//dodaj taką krawędź
					current.level++;
				}
				else {
					possible_multiple_edge = false;//jeśli aktualnie krawędź nie może być zwielokrotniona ustaw boolowska na fałsz
					continue;//żeby rozpatrzył kolejną
				}
			}
			else {
				possible_multiple_edge = false;
				continue;
			}
		}
		else {
			bool next_edge_possible = true;
			//DODAWANIE KRAWĘDZI---------------------------------------------------------------------------------------------------------------------------------------------------------
			if (tab[1] < actual_elements_to_consider - 1) {//elements to ilość, vector numeruje od zera stąd -1 bo to opcja zeby dodac jeszcze jakas
				if (tab[0] > tab[1] + 1) {//żeby pierwszy składnik krawędzi był mniejszy
					tab[1]++;
					possible_multiple_edge = false;
					continue;
				}
				if (tab[0] == tab[1] + 1) {
					tab[1]++;
					possible_multiple_edge = false;
					continue;
				}
				//żeby nie tworzyły się strukturki typy H-H
				if (elements_bonds[assign_element(tab[0])] == std::vector<int>{1}&& elements_bonds[assign_element(tab[1] + 1)] == std::vector<int>{1}) {
					tab[1]++;
					possible_multiple_edge = false;
					continue;
				}

				std::string elem1 = assign_element(tab[1] + 1);//sprawdza jaki pierwiastek kryje się pod kolejnym wierzchołkiem
				std::string elem2 = assign_element(tab[0]);//pierwiastek w pierwszej części krawędzi
				int degree1 = 0;
				int degree2 = 0;

				for (int i = 0; i < current.single_graph.size(); i++) {
					if (current.single_graph[i][0] == tab[1] + 1 || current.single_graph[i][1] == tab[1] + 1) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi;
						//krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree1++;
					}
					if (current.single_graph[i][0] == tab[0] || current.single_graph[i][1] == tab[0]) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi;
						//krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree2++;
					}
				}

				std::vector<int> elem_degrees = elements_bonds[elem2];
				if (elem_degrees[elem_degrees.size() - 1] > degree2) {//jeśli nie przekroczymy stopnia pierwszej części krawędzi
					elem_degrees = elements_bonds[elem1];//to sprawdź drugą
					if (elem_degrees[elem_degrees.size() - 1] > degree1) {//jeśli nie przekroczy
						edge.clear();
						edge.push_back(tab[0]); edge.push_back(tab[1] + 1);
						used_vertices.insert(tab[0]); used_vertices.insert(tab[1] + 1);
						vertices[tab[0]]++; vertices[tab[1] + 1]++;
						current.single_graph.push_back(edge);//dodaj taką krawędź
						current.level++;
						kroki++;
						tab[1]++;//zaktualizuj ost dod
						possible_multiple_edge = true;
					}
					else {
						tab[1]++;//zmienić żeby wiadomo co ostatnio rozpatrywane, ale nie dodawać
						continue;//żeby rozpatrzył kolejną
					}
				}
				else {
					tab[1]++;
					continue;
				}
			}
			else if (tab[0] + 1 < actual_elements_to_consider) {//skoro drugiego elementu krawędzi nie da się zmienić bo już ostatni to zmień pierwszy
				if (tab[0] + 1 > 0) {//żeby pierwszy składnik krawędzi był mniejszy
					tab[0]++;
					tab[1] = 0;
					possible_multiple_edge = false;
					continue;
				}
				std::string elem1 = assign_element(tab[0] + 1);//sprawdza jaki pierwiastek kryje się pod kolejnym wierzchołkiem
				std::string elem2 = assign_element(0);//pierwiastek w pierwszej części krawędzi
				int degree1 = 0;
				int degree2 = 0;

				for (int i = 0; i < current.single_graph.size(); i++) {
					if (current.single_graph[i][0] == tab[0] + 1 || current.single_graph[i][1] == tab[0] + 1) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi;
						//krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree1++;
					}
					if (current.single_graph[i][0] == 0 || current.single_graph[i][1] == 0) {//jeśli ten wierzchołek pojawił sie w którejś z krawędzi; krawędzie nie mają powtórzeń dlatego trzeba czasem pierwszy elem a czasem drugi sprawdzać
						degree2++;
					}
				}

				std::vector<int> elem_degrees = elements_bonds[elem1];
				if (elem_degrees[elem_degrees.size() - 1] > degree1) {//jeśli nie przekroczymy stopnia pierwszej części krawędzi
					elem_degrees = elements_bonds[elem2];//to sprawdź drugą
					if (elem_degrees[elem_degrees.size() - 1] > degree2) {//jeśli nie przekroczy
						edge.clear();
						edge.push_back(tab[0] + 1); edge.push_back(0);
						used_vertices.insert(tab[0] + 1); used_vertices.insert(0);
						vertices[tab[0] + 1]++; vertices[0]++;
						current.single_graph.push_back(edge);//dodaj taką krawędź
						current.level++;
						kroki++;
						tab[0]++;//zaktualizuj ost dod
						tab[1] = 0;
						possible_multiple_edge = true;
					}
					else {
						tab[0]++;//zmienić żeby wiadomo co ostatnio rozpatrywane, ale nie dodawać
						tab[1] = 0;
						continue;//żeby rozp kolejną
					}
				}
				else {
					tab[0]++;
					tab[1] = 0;
					continue;
				}
			}
			else {
				if (tab[0] == actual_elements_to_consider - 1 && tab[1] == actual_elements_to_consider - 1 && current.single_graph.empty())
					break;

				tab[0] = current.single_graph[current.single_graph.size() - 1][0];//przypisz pierwszą część krawędzi ostatniej jaka jest zapisana w grafie
				tab[1] = current.single_graph[current.single_graph.size() - 1][1];
				delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
				current.single_graph.pop_back();
				current.level--;

				if (tab[0] == actual_elements_to_consider - 1 && tab[1] == actual_elements_to_consider - 2) {//skoro to była ostatnia możliwa to tzreba nie tylko
					//ją ale i poprzednią usunąć, żeby dało się rozpatrywać dalej, a do tab wpisać rzeczy z przedostatniej żeby to ją sprawdzać dalej
					tab[0] = current.single_graph[current.single_graph.size() - 1][0];
					tab[1] = current.single_graph[current.single_graph.size() - 1][1];
					delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
					current.single_graph.pop_back();
					current.level--;
				}

				continue;//nei byłą dodana żadna krawędź, więc próbuj dalej
			}
		}
		//został już dodana jakaś krawędź sprawdźmy czy graf jest ok
		//---------------------------------------------------------------------------------------------------------------------------------------------------------
		bool sth_isomorphic = false;

		switch (mode)
		{
		case(0)://IZOMORFIZM
			for (int i = 0; i < good_graphs.size(); i++) {
				if (isomorphism24(good_graphs[i], current)) {
					sth_isomorphic = true;
					break;
				}
			}
			break;
		case(1)://ETKIETOWANIE
			if (!is_label_the_biggest(current.single_graph, elements)) {
				sth_isomorphic = true;
			}
			break;
		default:
			std::cout << "wrong mode!\n";
			break;
		}

		if (sth_isomorphic) {
			tab[0] = current.single_graph[current.single_graph.size() - 1][0];//przypisz pierwszą część krawędzi ostatniej jaka jest zapisana w grafie
			tab[1] = current.single_graph[current.single_graph.size() - 1][1];
			delet_from_set(used_vertices, vertices, tab[0]); delet_from_set(used_vertices, vertices, tab[1]);
			current.single_graph.pop_back();//usuń ostatnią krawędź
			possible_multiple_edge = false;//żeby nie podkusiło programu się zapętlić
			current.level--;
			if (current.single_graph.empty())
				break;
			continue;//nei byłą dodana żadna krawędź, więc próbuj dalej
		}
		else if (used_vertices.size() == actual_elements_to_consider && chech_graph_consistency(current.single_graph)) {//nie jest izomorficzny z żadnym z powstałych
			//jest spójny i zawiera już wszystkie pierwiastki
			//TO SPRAWDZAJ CZY PROMISSING

			bool done = true;
			std::vector<std::vector<int>> possible_boundaries;
			std::vector<int> biggest_possible;
			biggest_possible.reserve(actual_elements_to_consider);
			std::vector<int> actual_sol;
			actual_sol.reserve(actual_elements_to_consider);
			int last_used = -1;
			int act_vertex = 0;

			for (int i = 0; i < actual_elements_to_consider; i++) {//dla każdego pierwiastka w grafie
				std::vector<int> possibilities;
				int degree = 0;

				for (int j = 0; j < current.single_graph.size(); j++) {//sprawdź na którym jest stopniu obecnie w grafie

					if (current.single_graph[j][0] == i || current.single_graph[j][1] == i) {
						degree++;
					}
					if (j == current.single_graph.size() - 1) {
						std::vector<int> possible_degrees = elements_bonds[assign_element(i)];

						for (int k = 0; k < possible_degrees.size(); k++) {
							if (possible_degrees[k] - degree >= 0) {//jeśli na takim stopniu można jeszcze coś dołączyć lub dołączyć 0 (ale nie mniej)
								possibilities.push_back(possible_degrees[k] - degree);
							}
						}
						if (possibilities.size() == 0) {
							possibilities.push_back(0);
						}
						possible_boundaries.push_back(possibilities);
					}
				}
				//dodanie największej ilości wodorów do vectora największych
				biggest_possible.push_back(possibilities[possibilities.size() - 1]);
			}

			bool still_can = true;
			bool vert_to_check = true;
			int actual_good_graphs_number = good_graphs.size();

			while (still_can) {
				if (possible_boundaries[act_vertex].size() == 1 && possible_boundaries[act_vertex][0] == 0 && vert_to_check) {//jeśli nic ni można dodać do tego pierwiastka
					actual_sol.push_back(0);
					last_used = -1;
					act_vertex++;
				}//jeśli wierzchołek jest zbyt duży lub nie ma już co doddać to wykona się else
				else if (act_vertex < actual_elements_to_consider && possible_boundaries[act_vertex][possible_boundaries[act_vertex].size() - 1] > last_used) {
					for (int i = 0; i < possible_boundaries[act_vertex].size(); i++) {
						if (possible_boundaries[act_vertex][i] > last_used) {
							actual_sol.push_back(possible_boundaries[act_vertex][i]);
							last_used = -1;
							vert_to_check = true;
							act_vertex++;
							break;
						}
					}
				}
				else {
					if (actual_sol.size() == 0) {
						last_used = -1;
					}
					else {
						last_used = actual_sol[actual_sol.size() - 1];//0-1!!!
						vert_to_check = false;
						actual_sol.pop_back();
						act_vertex--;
					}
				}
				if (actual_sol.size() == actual_elements_to_consider) {
					//dodawanie rozwiązania do dobrych rozwiązań jeśli jest dobre xD
					if (is_it_good(actual_sol, hydrogens)) {
						//dodanie wodorów do grafu
						Graph good_graph = current;
						int hydrogen_number = 0;//bo w sumie to wierzchołi są ponumerowane <0,actual_ele_to_cons>, więc wodory powinny zaczynać od act_elem...
						for (int i = 0; i < actual_sol.size(); i++) {
							for (int j = 0; j < actual_sol[i]; j++) {
								std::vector<int> edge;
								edge.push_back(i);
								edge.push_back(actual_elements_to_consider + hydrogen_number);
								good_graph.single_graph.push_back(edge);
								hydrogen_number++;
							}
						}
						///////////podwójne sprawdzanie
						switch (mode)
						{
						case(0)://IZOMORFIZM
							if (actual_good_graphs_number == 0) {
								std::vector<std::vector<int>> good_graph_neighbours = transform_edges_to_neighbours(good_graph.single_graph);
								if (check_rules(good_graph_neighbours)) {
									good_graphs.push_back(good_graph);
								}
							}
							else {
								if (actual_good_graphs_number == good_graphs.size()) {
									std::vector<std::vector<int>> good_graph_neighbours = transform_edges_to_neighbours(good_graph.single_graph);
									if (check_rules(good_graph_neighbours)) {
										good_graphs.push_back(good_graph);
									}
								}
								else {
									for (int i = actual_good_graphs_number; i < good_graphs.size(); i++) {//porównuje grafy tylko tego coru - mniej porównań
										if (isomorphism24(good_graphs[i], current)) {
											std::vector<std::vector<int>> good_graph_neighbours = transform_edges_to_neighbours(good_graph.single_graph);
											if (check_rules(good_graph_neighbours)) {
												good_graphs.push_back(good_graph);
											}
										}
									}
								}
							}
							break;
						case(1)://ETKIETOWANIE
							if (is_label_the_biggest(good_graph.single_graph, elements)) {
								std::vector<std::vector<int>> good_graph_neighbours = transform_edges_to_neighbours(good_graph.single_graph);
								if (check_rules(good_graph_neighbours)) {
									good_graphs.push_back(good_graph);
								}
							}
							break;
						default:
							std::cout << "wrong mode!\n";
							break;
						}
						////////bez sprawdzania
						//good_graphs.push_back(good_graph);
					}
					//sprawdzanie czy to już ostatnia możliwość, jak tak to koniec whilea
					for (int i = 0; i < actual_elements_to_consider; i++) {
						if (actual_sol[i] != biggest_possible[i]) {//usuwańsko ostatniej pozycji
							last_used = actual_sol[actual_sol.size() - 1];
							vert_to_check = false;
							actual_sol.pop_back();
							act_vertex--;//żeby nie przekraczać granicy
							break;
						}
						if (i == actual_elements_to_consider - 1) {
							still_can = false;
						}
					}
				}
			}

		}
	}
}

//#include "isomorphism.h"
//#include "utils.h"
//#include "graph_class.h"
//#include "tree.h"
///////////////////////////////MAIN/////////////////////////////////////////////////////////////
//////////////////////////////UWAGI/////////////////////////////////////////////////////////////
//
//WODORY NA KOŃCU WZORU, W SENSIE TABELI Z KROTNOŚCIAMI POSZCEGÓLNYCH PIERWIASTKÓW!!!
////////////////////////////////////////////////////////////////////////////////////////////////

int quantity_of_elements_in_formula = 0;
clock_t start, stop;
enum modes { isomorphism = 0, labeling = 1 };
std::string filename = "testy";


void show_graphs(std::vector<Graph>& good_graphs) {
//std::cout << "uzylem funkcji show_graphs" << std::endl;
std::ofstream file;
file.open("results.txt");
	for (int s = 0; s < good_graphs.size(); s++) {
		//std::cout << "GRAF " << s << std::endl;
		file << "-" << std::endl;
		for (int i = 0; i < good_graphs[s].single_graph.size(); i++) {
			for (int j = 0; j < good_graphs[s].single_graph[i].size(); j++) {
				file << good_graphs[s].single_graph[i][j] << " ";
			}
			file << "\n";
		}
		file << "\n";
	}
	file << "-" << std::endl;
	for (int i = 0; i < ELEMENTS_TABLE.size(); i++) {
		file << i << " " << ELEMENTS_TABLE[i];
		file << "\n";
	}
	file.close();
}



extern "C" int main()
{
	//odczyt z pliku
	int sum_of_elements = 0;
	std::fstream file;
	std::string line;
	int counter = 0;
	//odczyt z pliku
	file.open("formula.txt", std::ios::in);
	//zapis do pliku
	//std::ofstream outfile;
	//outfile.open("wyniki.txt", std::ios_base::app); // append instead of overwrite


	if (file.is_open()) {
		//std::cout << "odczytalem plik" << std::endl;
		while (!file.eof()) {
			std::getline(file, line);
			//file_out << line << std::endl;
			//outfile << line << '\n';
			std::string tmp;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] != ' ') {
					tmp += line[i];
				}
				else {
					if (counter == 0) {
						ELEMENTS.push_back(tmp);
					}
					else {
						QUANTITY.push_back(std::stoi(tmp));
					}
					tmp.clear();
				}

			}
			if (tmp.size() != 0) {
				if (counter == 0) {
					ELEMENTS.push_back(tmp);
				}
				else {
					QUANTITY.push_back(std::stoi(tmp));
				}
				tmp.clear();
			}
			counter++;
		}
		file.close();
	}

	for (auto& n : QUANTITY)
		sum_of_elements += n;
	quantity_of_elements_in_formula = sum_of_elements;
	ELEMENTS_TABLE = create_elements_table();
	std::vector<Graph> good_graphs;
	set_mode(labeling);
	//std::cout << "po ustawieniu modulu" << std::endl;
	tree_solution_without_hydrogens(quantity_of_elements_in_formula, good_graphs);
	//std::cout << "po calym rozwiazaniu" << std::endl;
	show_graphs(good_graphs);
	ELEMENTS.clear();
	QUANTITY.clear();
	good_graphs.clear();
}
