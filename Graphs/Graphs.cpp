//
// Created by Hasanga Ranasinghe on 2023-06-07.
//

#include <vector>
#include <iostream>
#include <map>
#include <list>

using namespace std;

template<typename V>
class Vertex {
private:
    V value;

public:
    map<Vertex<V> *, double> neighbours;

    Vertex(V value) {
        this->value = value;
    }

    V getValue() {
        return value;
    }

    void addNeighbour(Vertex<V> *vertex, double weight) {
        this->neighbours.insert(pair<Vertex<V>*, double>(vertex, weight));
    }

    map<Vertex<V>*, double> getNeighbours() {
        return neighbours;
    }
};

template<typename V>
class Graph {
private:
    map<Vertex<V>*, bool> vertices;
    long size = 0;

    bool isDirected;
    bool isWeighted;

    void DFS(Vertex<V> *root) {
        Vertex<V> *current = root;
        for (pair<Vertex<V>*, double> neighbour: current->neighbours) {
            if (!vertices.at(neighbour.first)) {
                cout << neighbour.first->getValue() << " ";
                vertices.at(neighbour.first) = true;
                print_BFS(neighbour.first);
            }

        }
    }

public:
    Graph(bool isDirected, bool isWeighted) {
        this->isDirected = isDirected;
        this->isWeighted = isWeighted;
    }

    void addVertex(Vertex<V> *vertex) {
        this->vertices.insert(pair<Vertex<V>*, bool>(vertex, false));
        this->size++;
    }

    void addConnection(Vertex<V> *v1, Vertex<V> *v2, double weight) {
        if (!isWeighted) {
            weight = 0;
        }

        v1->addNeighbour(v2, weight);
        if (!isDirected) {
            v2->addNeighbour(v1, weight);
        }
    }

    void addConnection(Vertex<V> *v1, Vertex<V> *v2) {
        v1->addNeighbour(v2, 0);
        if (!isDirected) {
            v2->addNeighbour(v1, 0);
        }
    }

    bool removeVertex(Vertex<V> *vertex) {
        auto pos = this->vertices.find(vertex);
        if (pos != this->vertices.end()) {
            vertices.erase(vertex);
            this->size--;
            for (auto keyVal: vertices) {
                auto posNeighbour = keyVal.first->neighbours.find(vertex);
                if (posNeighbour != keyVal.first->neighbours.end()) {
                    keyVal.first->neighbours.erase(posNeighbour);
                }
            }
            return true;
        }
        return false;
    }

    void removeConnection(Vertex<V> *v1, Vertex<V> *v2) {
        auto pos = v1->neighbours.find(v2);
        if (pos != v1->neighbours.end()) {
            v1->neighbours.erase(pos);
        }
        if (!isDirected) {
            pos = v2->neighbours.find(v1);
            if (pos != v2->neighbours.end()) {
                v2->neighbours.erase(pos);
            }
        }
    }

    void print_BFS(Vertex<V> *root) {
        for (auto keyVal: vertices) {
            keyVal.second = false;
        }

        list<Vertex<V>*> queue;
        queue.push_back(root);

        while (!queue.empty()) {
            Vertex<V> *current = queue.front();
            queue.pop_front();
            for (pair<Vertex<V>*, double> neighbour: current->neighbours) {
                if (!vertices.at(neighbour.first)) {
                    cout << neighbour.first->getValue() << " ";
                    vertices.at(neighbour.first) = true;
                    queue.push_back(neighbour.first);
                }
            }
        }
    }

    void print_DFS(Vertex<V> *root) {
        for (auto keyVal: vertices) {
            keyVal.second = false;
        }
        DFS(root);
    }



    void print() {
        cout << "Vertex\t\tNeighbours" << endl;
        string weight = "";
        for (auto keyVal: vertices) {
            cout << keyVal.first->getValue() << "\t\t\t";
            for (pair<Vertex<V>*, double> neighbour: keyVal.first->getNeighbours()) {
                cout << neighbour.first->getValue();
                if (this->isWeighted) {
                    cout << "(" << neighbour.second << ")";
                }
                cout << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph<int> *graph = new Graph<int>(true, true);

    Vertex<int> *v0 = new Vertex<int>(0);
    Vertex<int> *v1 = new Vertex<int>(1);
    Vertex<int> *v2 = new Vertex<int>(2);

    graph->addVertex(v0);
    graph->addVertex(v1);
    graph->addVertex(v2);

    graph->addConnection(v0, v1, 5);
    graph->addConnection(v2, v1, 10);
    graph->addConnection(v0, v2, 8);
    graph->addConnection(v1, v0, 9);

    graph->print();

    cout << endl;

    graph->print_DFS(v0);
}