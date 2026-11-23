#include <iostream>
#include <string>
using namespace std;

struct Libro {
    int isbn;
    string titulo;
    string autor;
    bool disponible;
};

struct NodoLista {
    Libro libro;
    NodoLista* siguiente;
};

class ListaLibros {
private:
    NodoLista* cabeza;
    int total;

public:
    ListaLibros() : cabeza(nullptr), total(0) {}

    void agregar(Libro l) {
        NodoLista* nuevo = new NodoLista();
        nuevo->libro = l;
        nuevo->siguiente = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            NodoLista* temp = cabeza;
            while (temp->siguiente != nullptr)
                temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
        total++;
    }

    bool eliminar(int isbn) {
        if (cabeza == nullptr) return false;

        if (cabeza->libro.isbn == isbn) {
            NodoLista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            total--;
            return true;
        }

        NodoLista* actual = cabeza;
        while (actual->siguiente != nullptr) {
            if (actual->siguiente->libro.isbn == isbn) {
                NodoLista* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                total--;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    Libro* buscar(int isbn) {
        NodoLista* temp = cabeza;
        while (temp != nullptr) {
            if (temp->libro.isbn == isbn)
                return &temp->libro;
            temp = temp->siguiente;
        }
        return nullptr;
    }

    void mostrarTodos() {
        if (cabeza == nullptr) {
            cout << "  [El catalogo esta vacio]\n";
            return;
        }
        NodoLista* temp = cabeza;
        int i = 1;
        while (temp != nullptr) {
            cout << "  " << i++ << ". ISBN: " << temp->libro.isbn
                 << " | " << temp->libro.titulo
                 << " - " << temp->libro.autor
                 << " | " << (temp->libro.disponible ? "Disponible" : "Prestado")
                 << "\n";
            temp = temp->siguiente;
        }
    }

    int getTotal() { return total; }
};

struct NodoBST {
    int isbn;
    string titulo;
    NodoBST* izquierda;
    NodoBST* derecha;
};

class ArbolBST {
private:
    NodoBST* raiz;

    NodoBST* insertar(NodoBST* nodo, int isbn, string titulo) {
        if (nodo == nullptr) {
            NodoBST* nuevo = new NodoBST();
            nuevo->isbn = isbn;
            nuevo->titulo = titulo;
            nuevo->izquierda = nuevo->derecha = nullptr;
            return nuevo;
        }
        if (isbn < nodo->isbn)
            nodo->izquierda = insertar(nodo->izquierda, isbn, titulo);
        else if (isbn > nodo->isbn)
            nodo->derecha = insertar(nodo->derecha, isbn, titulo);
        return nodo;
    }

    NodoBST* buscar(NodoBST* nodo, int isbn) {
        if (nodo == nullptr || nodo->isbn == isbn)
            return nodo;
        if (isbn < nodo->isbn)
            return buscar(nodo->izquierda, isbn);
        return buscar(nodo->derecha, isbn);
    }

    NodoBST* minValor(NodoBST* nodo) {
        while (nodo->izquierda != nullptr)
            nodo = nodo->izquierda;
        return nodo;
    }

    NodoBST* eliminar(NodoBST* nodo, int isbn) {
        if (nodo == nullptr) return nullptr;
        if (isbn < nodo->isbn)
            nodo->izquierda = eliminar(nodo->izquierda, isbn);
        else if (isbn > nodo->isbn)
            nodo->derecha = eliminar(nodo->derecha, isbn);
        else {
            if (nodo->izquierda == nullptr) {
                NodoBST* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                NodoBST* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            NodoBST* sucesor = minValor(nodo->derecha);
            nodo->isbn = sucesor->isbn;
            nodo->titulo = sucesor->titulo;
            nodo->derecha = eliminar(nodo->derecha, sucesor->isbn);
        }
        return nodo;
    }

    void inorden(NodoBST* nodo) {
        if (nodo == nullptr) return;
        inorden(nodo->izquierda);
        cout << "  ISBN: " << nodo->isbn << " - " << nodo->titulo << "\n";
        inorden(nodo->derecha);
    }

public:
    ArbolBST() : raiz(nullptr) {}

    void insertar(int isbn, string titulo) {
        raiz = insertar(raiz, isbn, titulo);
    }

    bool existe(int isbn) {
        return buscar(raiz, isbn) != nullptr;
    }

    string buscarTitulo(int isbn) {
        NodoBST* nodo = buscar(raiz, isbn);
        if (nodo) return nodo->titulo;
        return "";
    }

    void eliminar(int isbn) {
        raiz = eliminar(raiz, isbn);
    }

    void mostrarOrdenado() {
        if (raiz == nullptr) {
            cout << "  [Arbol vacio]\n";
            return;
        }
        inorden(raiz);
    }
};


struct NodoCola {
    string nombreUsuario;
    int isbnSolicitado;
    NodoCola* siguiente;
};

class Cola {
private:
    NodoCola* frente;
    NodoCola* fin;
    int cantidad;

public:
    Cola() : frente(nullptr), fin(nullptr), cantidad(0) {}

    void encolar(string nombre, int isbn) {
        NodoCola* nuevo = new NodoCola();
        nuevo->nombreUsuario = nombre;
        nuevo->isbnSolicitado = isbn;
        nuevo->siguiente = nullptr;

        if (fin == nullptr) {
            frente = fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        cantidad++;
    }

   
    bool desencolar(string& nombre, int& isbn) {
        if (frente == nullptr) return false;
        nombre = frente->nombreUsuario;
        isbn = frente->isbnSolicitado;
        NodoCola* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) fin = nullptr;
        delete temp;
        cantidad--;
        return true;
    }

    bool estaVacia() { return frente == nullptr; }
    int getCantidad() { return cantidad; }

    void mostrar() {
        if (frente == nullptr) {
            cout << "  [No hay solicitudes en espera]\n";
            return;
        }
        NodoCola* temp = frente;
        int pos = 1;
        while (temp != nullptr) {
            cout << "  " << pos++ << ". " << temp->nombreUsuario
                 << " espera ISBN: " << temp->isbnSolicitado << "\n";
            temp = temp->siguiente;
        }
    }
};

class Biblioteca {
private:
    ListaLibros catalogo;
    ArbolBST indice;
    Cola listaEspera;

    int nextIsbn;

    void limpiarPantalla() {
        cout << "\n" << string(55, '=') << "\n";
    }

public:
    Biblioteca() : nextIsbn(1001) {

        agregarLibro("El Retrato de Dorian Grey", "Oscar");
        agregarLibro("Cien Anos de Soledad", "Garcia Marquez");
        agregarLibro("1984", "George Orwell");
        agregarLibro("El Principito", "Antoine de Saint-Exupery");
    }

    void agregarLibro(string titulo, string autor) {
        Libro l;
        l.isbn = nextIsbn++;
        l.titulo = titulo;
        l.autor = autor;
        l.disponible = true;

        catalogo.agregar(l);
        indice.insertar(l.isbn, l.titulo);
        cout << "  >> Libro agregado: \"" << titulo << "\" (ISBN: " << l.isbn << ")\n";
    }

    void eliminarLibro(int isbn) {
        Libro* l = catalogo.buscar(isbn);
        if (l == nullptr) {
            cout << "  >> ERROR: No se encontro libro con ISBN " << isbn << "\n";
            return;
        }
        if (!l->disponible) {
            cout << "  >> ERROR: El libro esta prestado, no se puede eliminar\n";
            return;
        }
        string titulo = l->titulo;
        catalogo.eliminar(isbn);
        indice.eliminar(isbn);
        cout << "  >> Libro eliminado: \"" << titulo << "\"\n";
    }

    void prestarLibro(int isbn, string usuario) {
        Libro* l = catalogo.buscar(isbn);
        if (l == nullptr) {
            cout << "  >> ERROR: Libro no encontrado\n";
            return;
        }
        if (!l->disponible) {
            cout << "  >> Libro no disponible. Agregando a lista de espera...\n";
            listaEspera.encolar(usuario, isbn);
            cout << "  >> " << usuario << " agregado a la cola (posicion " << listaEspera.getCantidad() << ")\n";
            return;
        }
        l->disponible = false;
        cout << "  >> Prestamo exitoso: \"" << l->titulo << "\" a " << usuario << "\n";
    }

    void devolverLibro(int isbn) {
        Libro* l = catalogo.buscar(isbn);
        if (l == nullptr) {
            cout << "  >> ERROR: Libro no encontrado\n";
            return;
        }
        if (l->disponible) {
            cout << "  >> El libro ya estaba disponible\n";
            return;
        }
        l->disponible = true;
        cout << "  >> Devolucion registrada: \"" << l->titulo << "\"\n";

        if (!listaEspera.estaVacia()) {
            string nombre;
            int isbnEspera;
            listaEspera.desencolar(nombre, isbnEspera);
            if (isbnEspera == isbn) {
                l->disponible = false;
                cout << "  >> Libro prestado automaticamente a " << nombre << " (de la cola)\n";
            }
        }
    }

    void buscarPorISBN(int isbn) {
        if (!indice.existe(isbn)) {
            cout << "  >> ISBN " << isbn << " no encontrado en el indice\n";
            return;
        }
        Libro* l = catalogo.buscar(isbn);
        if (l) {
            cout << "  >> Encontrado:\n";
            cout << "     Titulo : " << l->titulo << "\n";
            cout << "     Autor  : " << l->autor << "\n";
            cout << "     Estado : " << (l->disponible ? "Disponible" : "Prestado") << "\n";
        }
    }

    void mostrarCatalogo() {
        cout << "\n  --- CATALOGO COMPLETO (" << catalogo.getTotal() << " libros) ---\n";
        catalogo.mostrarTodos();
    }

    void mostrarIndiceOrdenado() {
        cout << "\n  --- INDICE BST (ordenado por ISBN) ---\n";
        indice.mostrarOrdenado();
    }

    void mostrarCola() {
        cout << "\n  --- LISTA DE ESPERA (" << listaEspera.getCantidad() << " solicitudes) ---\n";
        listaEspera.mostrar();
    }

    void menu() {
        int opcion;
        do {
            limpiarPantalla();
            cout << "    SISTEMA DE GESTION DE BIBLIOTECA\n";
            limpiarPantalla();
            cout << "  1. Ver catalogo completo\n";
            cout << "  2. Agregar libro\n";
            cout << "  3. Eliminar libro\n";
            cout << "  4. Prestar libro\n";
            cout << "  5. Devolver libro\n";
            cout << "  6. Buscar libro por ISBN\n";
            cout << "  7. Ver indice BST ordenado\n";
            cout << "  8. Ver lista de espera\n";
            cout << "  0. Salir\n";
            limpiarPantalla();
            cout << "  Opcion: ";
            cin >> opcion;

            string titulo, autor, usuario;
            int isbn;

            switch (opcion) {
                case 1:
                    mostrarCatalogo();
                    break;
                case 2:
                    cout << "  Titulo: "; cin.ignore(); getline(cin, titulo);
                    cout << "  Autor : "; getline(cin, autor);
                    agregarLibro(titulo, autor);
                    break;
                case 3:
                    cout << "  ISBN a eliminar: "; cin >> isbn;
                    eliminarLibro(isbn);
                    break;
                case 4:
                    cout << "  ISBN del libro : "; cin >> isbn;
                    cout << "  Nombre usuario : "; cin.ignore(); getline(cin, usuario);
                    prestarLibro(isbn, usuario);
                    break;
                case 5:
                    cout << "  ISBN a devolver: "; cin >> isbn;
                    devolverLibro(isbn);
                    break;
                case 6:
                    cout << "  ISBN a buscar: "; cin >> isbn;
                    buscarPorISBN(isbn);
                    break;
                case 7:
                    mostrarIndiceOrdenado();
                    break;
                case 8:
                    mostrarCola();
                    break;
                case 0:
                    cout << "  >> Saliendo del sistema. Hasta luego!\n";
                    break;
                default:
                    cout << "  >> Opcion invalida\n";
            }

            if (opcion != 0) {
                cout << "\n  Presione Enter para continuar...";
                cin.ignore(); cin.get();
            }

        } while (opcion != 0);
    }
};

int main() {
    Biblioteca bib;
    bib.menu();
    return 0;
}
