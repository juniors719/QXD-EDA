/**
 * @file Set.h
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @brief TAD para representar um conjunto de inteiros. O conjunto é implementado utilizando uma árvore AVL.
 * @version 0.1
 * @date 07-05-2024
 *
 *
 */

#ifndef SET_H
#define SET_H

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "AVL.h"

class Set {
   private:
    AVL_Tree<int> tree{};  // Árvore AVL que armazena os elementos do conjunto
    int m_size{};          // Número de elementos no conjunto

    /**
     * @brief Método privado que retorna uma string em ordem da subárvore.
     *
     * @param node Node a ser verificado
     * @return String em ordem da subárvore
     */
    std::string inOrder() {
        return tree.inOrder();
    }

   public:
    /**
     * @brief Construtor padrão da classe Set. Cria um conjunto vazio.
     *
     */
    Set() : m_size(0) {}

    /**
     * @brief Destrutor da classe Set. Libera a memória alocada.
     *
     */
    ~Set() {
        clear();
    }

    /**
     * @brief Remove todos os elementos do conjunto.
     *
     */
    void clear() {
        tree.clear();
        m_size = 0;
    }

    /**
     * @brief Insere um inteiro no conjunto.
     *
     * @param key inteiro a ser inserido
     */
    void insert(int key) {
        tree.add(key);
        m_size++;
    }

    /**
     * @brief Remove um inteiro do conjunto.
     *
     * @param key inteiro a ser removido
     */
    void erase(int key) {
        if (contains(key)) {
            tree.remove(key);
            m_size--;
        }
    }

    /**
     * @brief Verifica se um inteiro está no conjunto.
     *
     * @param key inteiro a ser verificado
     * @return true se o inteiro está no conjunto, false caso contrário
     */
    bool contains(int key) {
        return tree.contains(key);
    }

    /**
     * @brief Troca o conteúdo de dois conjuntos.
     *
     * @param other conjunto a ser trocado
     */
    void swap(Set& other) {
        tree.swap(other.tree);
        std::swap(m_size, other.m_size);
    }

    /**
     * @brief Retorna o menor elemento do conjunto.
     *
     * @return int menor elemento do conjunto
     */
    int& minimum() {
        return tree.minimum();
    }

    /**
     * @brief Retorna o maior elemento do conjunto.
     *
     * @return int maior elemento do conjunto
     */
    int& maximum() {
        return tree.maximum();
    }

    /**
     * @brief Retorna o número de elementos no conjunto.
     *
     * @return int número de elementos no conjunto
     */
    int size() {
        return m_size;
    }

    /**
     * @brief Verifica se o conjunto está vazio.
     *
     * @return true se o conjunto está vazio, false caso contrário
     */
    bool empty() {
        return m_size == 0;
    }

    /**
     * @brief Retorna o sucessor de um elemento no conjunto.
     *
     * @param key elemento a ser verificado
     * @return Sucessor do elemento
     */
    int& successor(const int& key) {
        try {
            return tree.successor(key);
        } catch (std::runtime_error& e) {
            throw std::runtime_error(e.what());
        }
    }

    /**
     * @brief Retorna o predecessor de um elemento no conjunto.
     *
     * @param key elemento a ser verificado
     * @return Predecessor do elemento
     */
    int& predecessor(const int& key) {
        try {
            return tree.predecessor(key);
        } catch (std::runtime_error& e) {
            throw std::runtime_error(e.what());
        }
    }

    /**
     * @brief Método que retorna a união de dois conjuntos.
     *
     * @param other Conjunto a ser unido
     * @return União dos conjuntos
     */
    Set unionSets(Set& other) {
        Set new_set;

        std::string inOrder = tree.inOrder();
        std::istringstream iss(inOrder);
        int key;
        while (iss >> key) {
            new_set.insert(key);
        }

        inOrder = other.tree.inOrder();
        iss.clear();
        iss.str(inOrder);
        while (iss >> key) {
            new_set.insert(key);
        }

        return new_set;
    }

    /**
     * @brief Método que retorna a interseção de dois conjuntos.
     *
     * @param other Conjunto a ser intersecionado
     * @return Interseção dos conjuntos
     */
    Set intersectionSets(Set& other) {
        Set new_set;

        std::string inOrder = tree.inOrder();
        std::istringstream iss(inOrder);
        int key;
        while (iss >> key) {
            if (other.contains(key)) {
                new_set.insert(key);
            }
        }

        return new_set;
    }

    /**
     * @brief Método que retorna a diferença de dois conjuntos.
     *
     * @param other Conjunto a ser comparado
     * @return Diferença dos conjuntos
     */
    Set differenceSets(Set& other) {
        Set new_set;

        std::string inOrder = tree.inOrder();
        std::istringstream iss(inOrder);
        int key;
        while (iss >> key) {
            if (!other.contains(key)) {
                new_set.insert(key);
            }
        }

        return new_set;
    }

    // ********************** Sobrecarga de operadores **********************

    /**
     * @brief Sobrecarga do operador de inserção << para imprimir o conjunto.
     * @return Um objeto ostream com o conjunto formatado.
     *
     */
    friend std::ostream& operator<<(std::ostream& os, Set& set) {
        os << "[ " << set.inOrder() << "]";
        return os;
    }
};

#endif  // SET_H