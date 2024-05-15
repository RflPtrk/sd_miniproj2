#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>
#include "priority_queue_list.h"
#include "priority_queue_heap.h"

void fillPriorityQueueAndSaveToFile(const std::string& filename, int elem_num) {
    // Tworzymy obiekt kolejki priorytetowej
    priority_queue_heap pq;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int32_t> elem_dist(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()); // Zakres liczb pseudolosowych dla elementów
    std::uniform_int_distribution<int32_t> priori_dist(0, (elem_num*5)); // Zakres liczb pseudolosowych dla priorytetów

    // Wypełniamy kolejkę liczbami pseudolosowymi
    for (int i = 0; i < elem_num; ++i) {
        int value = elem_dist(rng);
        int priority = priori_dist(rng);
        pq.insert(value, priority);
    }

    // Otwieramy plik do zapisu
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Zapisujemy zawartość kolejki do pliku
    while (!pq.is_empty()) {
        int priority = pq.peek_priori();
        int value = pq.extract_max();
        outputFile << value << " " << priority << "\n";
    }

    // Zamykamy plik
    outputFile.close();

    std::cout << "Queue contents saved to file: " << filename << std::endl;
}

void readPriorityQueueFromFile(const std::string& filename, priority_queue_list& pq) {
    //Otwarcie pliku
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //Wczytanie zawartości pliku do kolejki
    int value, priority;
    while (inputFile >> value >> priority) {
        pq.insert(value, priority);
    }

    inputFile.close(); //Zamknięcie pliku
    std::cout << "Queue contents loaded from file: " << filename << std::endl;
}

double methods_test(priority_queue_list& pq, int value, int priority) {
    auto start_time = std::chrono::steady_clock::now();
    pq.insert(value, priority);
    auto end_time = std::chrono::steady_clock::now();

    double elapsed_time = std::chrono::duration<double, std::micro>(end_time - start_time).count();
    return elapsed_time;

}

/*int main() {
    priority_queue_list pq;
    fillPriorityQueueAndSaveToFile("priority_queue_contents.txt", 20000);
    readPriorityQueueFromFile("priority_queue_contents.txt", pq);
    double e_time[10];
    double sum = 0.0;
    for (int i = 0; i < 10; i++) {
        e_time[i]= methods_test(pq, (12867 - 12*i), (4211 +5*i));
        sum += e_time[i];
    }
    double average = sum / 10;
    std::cout << "Average execution time: " << average << " microseconds" << std::endl;
    return 0;
}*/

void method_choice(priority_queue* pq) {
    bool cond = true;
    while (cond) {
        unsigned int wybor;
        std::cout << "Wybierz jedną z opcji: (1-6) \n";
        std::cout << "1. Dodaj element do kolejki. \n2. Usun element o najwiekszym priorytecie. \n3. Podejrzyj element o najwiekszym priorytecie. \n4. Zmien priorytet elementu. \n5. Sprawdz wielkosc kolejki. \n6. Wypisz zawrtość kolejki. \n";
        std::cin >> wybor;

        int element, priority;
        switch (wybor) {
        case 1:
            std::cout << "Podaj wartosc elementu: \n";
            std::cin >> element;
            std::cout << "Podaj priorytet elementu: \n";
            std::cin >> priority;
            pq->insert(element, priority);
            break;
        case 2:
            pq->extract_max();
            break;
        case 3:
            pq->peek();
            break;
        case 4:
            std::cout << "Podaj element, ktorego priorytet chcesz zmienic: \n";
            std::cin >> element;
            std::cout << "Podaj nowy priorytet: \n";
            std::cin >> priority;
            pq->modify_key(element, priority);
            break;
        case 5:
            pq->return_size();
            break;
        case 6:
            pq->print();
            break;
        default:
            std::cout << "Powrot do menu. \n";
            cond = false;
            break;
        }
    }
}

void implem_choice() {
    std::cout << "Wybierz rodzaj implementacji: (1-2)\n";
    std::cout << "1. Lista \n2. Kopiec binarny \n";
    unsigned int wybor;
    std::cin >> wybor;
    priority_queue* pq = nullptr;

    switch (wybor) {
    case 1:
        std::cout << "Lista. \n";
        pq = new priority_queue_list;
        method_choice(pq);
        delete pq;
        break;

    case 2:
        std::cout << "Kopiec binarny. \n";
        pq = new priority_queue_heap;
        method_choice(pq);
        delete pq;
        break;
        
    default:
        std::cout << "Opuszczanie programu. \n";
        return;
    }
}

int main() {
    while (true) {
        implem_choice();
    }
    return 0;
}
