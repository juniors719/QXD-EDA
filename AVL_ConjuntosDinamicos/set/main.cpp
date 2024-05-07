/**
 * @file main.cpp
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @brief Arquivo principal do programa.
 * @version 0.1
 * @date 07-05-2024
 *
 *
 */

#include <iostream>
#include <sstream>
#include <vector>

#include "Set.h"

using namespace std;

/*

Comandos:

- create : Cria um novo conjunto vazio.
- insert <set_index> <element> : Adiciona um elemento ao conjunto.
- erase <set_index> <element> : Remove um elemento do conjunto.
- contains <set_index> <element> : Verifica se um elemento pertence ao conjunto.
- clear <set_index> : Remove todos os elementos do conjunto.
- swap <set_index1> <set_index2> : Troca os elementos de dois conjuntos.
- min <set_index> : Retorna o menor elemento do conjunto.
- max <set_index> : Retorna o maior elemento do conjunto.
- succ <set_index> <element> : Retorna o sucessor de um elemento no conjunto.
- pred <set_index> <element> : Retorna o antecessor de um elemento no conjunto.
- empty <set_index> : Verifica se o conjunto está vazio.
- size <set_index> : Retorna o número de elementos do conjunto.

- uni <set_index1> <set_index2> : Cria um novo conjunto com a união dos elementos de dois conjuntos.
- int <set_index1> <set_index2> : Cria um novo conjunto com a interseção dos elementos de dois conjuntos.
- dif <set_index1> <set_index2> : Cria um novo conjunto com a diferença dos elementos de dois conjuntos.



*/

// Vector global que armazena os conjuntos
vector<Set> sets(3, Set());

/**
 * @brief Função que verifica se um índice é válido. Se não for, imprime uma mensagem de erro.
 *
 * @param index Índice a ser verificado
 * @return True se o índice é válido, false caso contrário
 */
bool checkIndex(int index) {
    if (index >= 0 && index < sets.size())
        return true;
    cout << "Índice inválido." << endl;
    return false;
}

int main() {
    cout << "Digite \"help\" para ver os comandos disponíveis." << endl;
    istringstream iss;
    string line;

    while (true) {
        iss.clear();

        cout << "--------------------" << endl;
        for (int i = 0; i < sets.size(); i++) {
            cout << "Conjunto " << i << ": " << sets[i] << endl;
        }
        cout << "--------------------" << endl;

        getline(cin, line);
        iss.str(line);

        string cmd;
        iss >> cmd;

        // *** CREATE *** //
        if (cmd == "create") {
            sets.push_back(Set());
        }

        // *** INSERT *** //
        else if (cmd == "insert") {
            int set_index, element;
            iss >> set_index >> element;
            if (checkIndex(set_index))
                sets[set_index].insert(element);
        }

        // *** ERASE *** //
        else if (cmd == "erase") {
            int set_index, element;
            iss >> set_index >> element;
            if (checkIndex(set_index))
                sets[set_index].erase(element);
        }

        // *** CONTAINS *** //
        else if (cmd == "contains") {
            int set_index, element;
            iss >> set_index >> element;
            if (checkIndex(set_index))
                cout << (sets[set_index].contains(element) ? "sim" : "nao") << endl;
        }

        // *** CLEAR *** //
        else if (cmd == "clear") {
            int set_index;
            iss >> set_index;
            if (checkIndex(set_index))
                sets[set_index].clear();
        }

        // *** SWAP *** //
        else if (cmd == "swap") {
            int set_index1, set_index2;
            iss >> set_index1 >> set_index2;
            if (checkIndex(set_index1) && checkIndex(set_index2))
                sets[set_index1].swap(sets[set_index2]);
        }

        // *** MINIMUM *** //
        else if (cmd == "min") {
            int set_index;
            iss >> set_index;
            if (checkIndex(set_index)) {
                if (sets[set_index].empty())
                    cout << "Conjunto vazio." << endl;
                else
                    cout << sets[set_index].minimum() << endl;
            }
        }

        // *** MAXIMUM *** //
        else if (cmd == "max") {
            int set_index;
            iss >> set_index;
            if (checkIndex(set_index)) {
                if (sets[set_index].empty())
                    cout << "Conjunto vazio." << endl;
                else
                    cout << sets[set_index].maximum() << endl;
            }
        }

        // *** SUCCESSOR *** //
        else if (cmd == "succ") {
            int set_index, element;
            iss >> set_index >> element;
            if (checkIndex(set_index)) {
                try {
                    cout << sets[set_index].successor(element) << endl;
                } catch (const std::runtime_error &e) {
                    cout << e.what() << endl;
                }
            }
        }

        // *** PREDECESSOR *** //
        else if (cmd == "pred") {
            int set_index, element;
            iss >> set_index >> element;
            if (checkIndex(set_index)) {
                try {
                    cout << sets[set_index].predecessor(element) << endl;
                } catch (const std::runtime_error &e) {
                    cout << e.what() << endl;
                }
            }
        }

        // *** EMPTY *** //
        else if (cmd == "empty") {
            int set_index;
            iss >> set_index;
            if (checkIndex(set_index))
                cout << (sets[set_index].empty() ? "sim" : "nao") << endl;
        }

        // *** SIZE *** //
        else if (cmd == "size") {
            int set_index;
            iss >> set_index;
            if (checkIndex(set_index))
                cout << sets[set_index].size() << endl;
        }

        // *** UNION *** //
        else if (cmd == "uni") {
            int set_index1, set_index2;
            iss >> set_index1 >> set_index2;
            if (checkIndex(set_index1) && checkIndex(set_index2)) {
                Set new_set = sets[set_index1].unionSets(sets[set_index2]);
                cout << "União dos conjuntos " << set_index1 << " e " << set_index2 << ": " << new_set << endl;
            }
        }

        // *** INTERSECTION *** //
        else if (cmd == "int") {
            int set_index1, set_index2;
            iss >> set_index1 >> set_index2;
            if (checkIndex(set_index1) && checkIndex(set_index2)) {
                Set new_set = sets[set_index1].intersectionSets(sets[set_index2]);
                cout << "Interseção dos conjuntos " << set_index1 << " e " << set_index2 << ": " << new_set << endl;
            }
        }

        // *** DIFFERENCE *** //
        else if (cmd == "dif") {
            int set_index1, set_index2;
            iss >> set_index1 >> set_index2;
            if (checkIndex(set_index1) && checkIndex(set_index2)) {
                Set new_set = sets[set_index1].differenceSets(sets[set_index2]);
                cout << "Diferença dos conjuntos " << set_index1 << " e " << set_index2 << ": " << new_set << endl;
            }
        }

        // *** HELP *** //
        else if (cmd == "help") {
            // cout << "Comandos: \n- create : Cria um novo conjunto vazio.\n- insert <set_index> <element> : Adiciona um elemento ao conjunto.\n- erase <set_index> <element> : Remove um elemento do conjunto.\n- contains <set_index> <element> : Verifica se um elemento pertence ao conjunto.\n- clear <set_index> : Remove todos os elementos do conjunto.\n- swap <set_index1> <set_index2> : Troca os elementos de dois conjuntos.\n- min <set_index> : Retorna o menor elemento do conjunto.\n- max <set_index> : Retorna o maior elemento do conjunto.\n- succ <set_index> <element> : Retorna o sucessor de um elemento no conjunto.\n- pred <set_index> <element> : Retorna o antecessor de um elemento no conjunto.\n- empty <set_index> : Verifica se o conjunto está vazio.\n- size <set_index> : Retorna o número de elementos do conjunto.\n- print <set_index> : Imprime os elementos do conjunto.\n\n- uni <set_index1> <set_index2> : Cria um novo conjunto com a união dos elementos de dois conjuntos.\n- int <set_index1> <set_index2> : Cria um novo conjunto com a interseção dos elementos de dois conjuntos.\n- dif <set_index1> <set_index2> : Cria um novo conjunto com a diferença dos elementos de dois conjuntos.\n\n- end : Encerra o programa\n"
            //      << endl;
            cout << "Comandos:\n";
            cout << "- create : Cria um novo conjunto vazio.\n";
            cout << "- insert <set_index> <element> : Adiciona um elemento ao conjunto.\n";
            cout << "- erase <set_index> <element> : Remove um elemento do conjunto.\n";
            cout << "- contains <set_index> <element> : Verifica se um elemento pertence ao conjunto.\n";
            cout << "- clear <set_index> : Remove todos os elementos do conjunto.\n";
            cout << "- swap <set_index1> <set_index2> : Troca os elementos de dois conjuntos.\n";
            cout << "- min <set_index> : Retorna o menor elemento do conjunto.\n";
            cout << "- max <set_index> : Retorna o maior elemento do conjunto.\n";
            cout << "- succ <set_index> <element> : Retorna o sucessor de um elemento no conjunto.\n";
            cout << "- pred <set_index> <element> : Retorna o antecessor de um elemento no conjunto.\n";
            cout << "- empty <set_index> : Verifica se o conjunto está vazio.\n";
            cout << "- size <set_index> : Retorna o número de elementos do conjunto.\n\n";
            cout << "- uni <set_index1> <set_index2> : Imprime a união dos elementos de dois conjuntos.\n";
            cout << "- int <set_index1> <set_index2> : Imprime a interseção dos elementos de dois conjuntos.\n";
            cout << "- dif <set_index1> <set_index2> : Imprime a diferença dos elementos de dois conjuntos.\n\n";
            cout << "- end : Encerra o programa\n"
                 << endl;
        }

        // *** END *** //
        else if (cmd == "end") {
            break;
        }

        // *** INVALID COMMAND *** //
        else {
            cout << "Comando inválido." << endl;
        }
    }
    return 0;
}