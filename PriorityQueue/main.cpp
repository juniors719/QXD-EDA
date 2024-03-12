#include <iostream>

#include "priority_queue.h"

using namespace std;

struct Pessoa {
    float nota;
    int id;
    string nome;
};

struct ComparaPeloNome {
    bool operator()(const Pessoa& a, const Pessoa& b) {
        return a.nome < b.nome;
    }
};

struct ComparaPelaNota {
    bool operator()(const Pessoa& a, const Pessoa& b) {
        return a.nota < b.nota;
    }
};

struct ComparaPeloId {
    bool operator()(const Pessoa& a, const Pessoa& b) {
        return a.id < b.id;
    }
};

int main() {
    PriorityQueue<Pessoa, ComparaPelaNota> fila;

    fila.push({7.5, 1, "Joao"});
    fila.push({8.5, 22, "Maria"});
    fila.push({6.5, 31, "Jose"});
    fila.push({9.5, 4, "Ana"});
    fila.push({5.5, 53, "Pedro"});

    while (fila.size() > 0) {
        Pessoa p = fila.pop();
        cout << p.id << ", " << p.nome << ", " << p.nota << endl;
    }
}