#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Vertice {
public:
    string nombre;
    float costo; // Puedes añadir más atributos según sea necesario

    Vertice(string n, float c = 0.0) : nombre(n), costo(c) {}
};

class Grafo {
private:
    vector<vector<float>> M;
    vector<Vertice> vertices; // Cambiado a Vertice
    int numVertices;
    int contadorVertices;

public:
    Grafo(int n) {
        numVertices = n;
        M.resize(n, vector<float>(n, 0));
        contadorVertices = 0;
    }

    void agregarVertice(string nombre, float costo = 0.0) {
        if (contadorVertices < numVertices) {
            vertices.emplace_back(nombre, costo); // Añadimos un nuevo objeto Vertice
            contadorVertices++;
        } else {
            cout << "No se pueden agregar más vértices. Límite alcanzado." << endl;
        }
    }

    void agregarArista(string v1, string v2, float costo) {
        int indice1 = -1, indice2 = -1;

        for (int i = 0; i < contadorVertices; ++i) {
            if (vertices[i].nombre == v1) {
                indice1 = i;
            }
            if (vertices[i].nombre == v2) {
                indice2 = i;
            }
        }

        if (indice1 != -1 && indice2 != -1) {
            M[indice1][indice2] = costo;
            M[indice2][indice1] = costo;  // Para grafos no dirigidos
        } else {
            cout << "Uno o ambos vértices no encontrados." << endl;
        }
    }

    void mostrarMatriz() {
        cout << "Matriz de Adyacencia:" << endl;
        cout << "  ";
        for (int i = 0; i < contadorVertices; ++i) {
            cout << vertices[i].nombre << "  ";
        }
        cout << endl;

        for (int i = 0; i < contadorVertices; ++i) {
            cout << vertices[i].nombre << " ";
            for (int j = 0; j < contadorVertices; ++j) {
                cout << M[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void DFS(int startVertex, vector<bool>& visited) {
        visited[startVertex] = true;
        cout << vertices[startVertex].nombre << " ";

        for (int i = 0; i < contadorVertices; ++i) {
            if (M[startVertex][i] != 0 && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    void BFS(int startVertex) {
        queue<int> q;
        vector<bool> visited(numVertices, false);
        q.push(startVertex);
        visited[startVertex] = true;

        cout << "Recorrido BFS desde " << vertices[startVertex].nombre << ": ";

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            cout << vertices[currentVertex].nombre << " ";

            for (int i = 0; i < contadorVertices; ++i) {
                if (M[currentVertex][i] != 0 && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void seleccionarRecorrido() {
        string tipoRecorrido, verticeInicial;
        cout << "Elija el tipo de recorrido (DFS o BFS): ";
        cin >> tipoRecorrido;
        cout << "Elija el vértice inicial: ";
        cin >> verticeInicial;

        int startIndex = -1;
        for (int i = 0; i < contadorVertices; ++i) {
            if (vertices[i].nombre == verticeInicial) {
                startIndex = i;
                break;
            }
        }

        if (startIndex == -1) {
            cout << "Vértice no encontrado." << endl;
            return;
        }

        vector<bool> visited(numVertices, false); // Marcamos los vértices visitados

        if (tipoRecorrido == "DFS" || tipoRecorrido == "dfs") {
            cout << "Recorrido DFS desde " << verticeInicial << ": ";
            DFS(startIndex, visited);
            cout << endl;

            cout << "Recorrido BFS desde " << verticeInicial << ": ";
            BFS(startIndex);
        } else if (tipoRecorrido == "BFS" || tipoRecorrido == "bfs") {
            cout << "Recorrido BFS desde " << verticeInicial << ": ";
            BFS(startIndex);

            cout << "Recorrido DFS desde " << verticeInicial << ": ";
            DFS(startIndex, visited);
            cout << endl;
        } else {
            cout << "Tipo de recorrido no válido." << endl;
        }
    }
};

int main() {
    Grafo g1(6);
    g1.agregarVertice("A");
    g1.agregarVertice("B");
    g1.agregarVertice("C");
    g1.agregarVertice("D");
    g1.agregarVertice("E");
    g1.agregarVertice("F");

    g1.agregarArista("A", "B", 2);
    g1.agregarArista("A", "D", 8);
    g1.agregarArista("B", "E", 6);
    g1.agregarArista("B", "D", 5);
    g1.agregarArista("C", "E", 9);
    g1.agregarArista("C", "F", 3);
    g1.agregarArista("E", "F", 1);
    g1.agregarArista("D", "F", 2);
    g1.agregarArista("D", "E", 3);
    g1.mostrarMatriz();
    g1.seleccionarRecorrido();

    Grafo g2(7);
    g2.agregarVertice("A");
    g2.agregarVertice("U");
    g2.agregarVertice("I");
    g2.agregarVertice("D");
    g2.agregarVertice("C");
    g2.agregarVertice("Y");
    g2.agregarVertice("T");

    g2.agregarArista("A", "U", 4);
    g2.agregarArista("A", "I", 7);
    g2.agregarArista("U", "I", 6);
    g2.agregarArista("U", "D", 3);
    g2.agregarArista("D", "C", 4);
    g2.agregarArista("I", "C", 4);
    g2.agregarArista("I", "Y", 4);
    g2.agregarArista("C", "T", 5);
    g2.agregarArista("Y", "T", 5);
    g2.mostrarMatriz();
    g2.seleccionarRecorrido();

    return 0;
}