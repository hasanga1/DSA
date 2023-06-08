//
// Created by Hasanga Ranasinghe on 2023-06-07.
//

#include <vector>
#include <iostream>

using namespace std;

template<typename V>
class Vertex {
private:
    V value;
    vector< pair<Vertex<V> *, double> > neighbours;

public:
    Vertex(V value) {
        this->value = value;
    }

    V getValue() {
        return value;
    }

    void addNeighbour(pair<Vertex<V> *, double> *neighbour) {
        this->neighbours.push_back(*neighbour);
    }

    vector<pair<Vertex<V>*, double>> getNeighbours() {
        return neighbours;
    }
};

template<typename V>
class Graph {
private:
    vector<Vertex<V>*> vertices;
    long size = 0;

    bool isDirected;
    bool isWeighted;

public:
    Graph(bool isDirected, bool isWeighted) {
        this->isDirected = isDirected;
        this->isWeighted = isWeighted;
    }

    void addVertex(Vertex<V> *vertex) {
        this->vertices.push_back(vertex);
    }

    void addConnection(Vertex<V> *v1, Vertex<V> *v2, double weight) {
        if (!isWeighted) {
            weight = 0;
        }

        v1->addNeighbour(new pair<Vertex<V> *, double>(v2, weight));
        if (!isDirected) {
            v2->addNeighbour(new pair<Vertex<V> *, double>(v1, weight));
        }
    }

    void addConnection(Vertex<V> *v1, Vertex<V> *v2) {
        v1->addNeighbour(new pair<Vertex<V> *, double>(v2, 0));
        if (!isDirected) {
            v2->addNeighbour(new pair<Vertex<V> *, double>(v1, 0));
        }
    }

    bool removeVertex(Vertex<V> *vertex) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == vertex) {
                this->vertices.erase(vertices.begin() + i, vertices.begin() + i + 1);
                size--;
                return true;
            }
        }
        return false;
    }

    void BFS()

    void print() {
        cout << "Vertex\t\tNeighbours" << endl;
        string weight = "";
        for (Vertex<V>* vertex: vertices) {
            cout << vertex->getValue() << "\t\t\t";
            for (pair<Vertex<V>*, double> neighbour: vertex->getNeighbours()) {
                cout << neighbour.first->getValue();
                if (this->isWeighted) {
                    cout << "(" << neighbour.second << ")";
                }
                if (neighbour != vertex->getNeighbours()[vertex->getNeighbours().size() - 1]) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

};

int main() {
    Graph<int> *graph = new Graph<int>(true, false);

    Vertex<int> *v0 = new Vertex<int>(0);
    Vertex<int> *v1 = new Vertex<int>(1);
    Vertex<int> *v2 = new Vertex<int>(2);

    graph->addVertex(v0);
    graph->addVertex(v1);
    graph->addVertex(v2);

    graph->print();

    graph->addConnection(v0, v1, 5);
    graph->addConnection(v2, v1, 10);
    graph->addConnection(v0, v2, 8);

    graph->removeVertex(v2);

    graph->print();
}