#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valor;
    struct nodo* izdo;
    struct nodo* dcho;
    struct nodo* padre;
} Nodo;

typedef Nodo Arbol;

Nodo* CrearNodo(int valor, Nodo* padre) {
    Nodo* nuevoNodo = (Nodo* )malloc(sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->izdo = nuevoNodo->dcho = NULL;
    nuevoNodo->padre = padre;
    return nuevoNodo;
}

void DestruirNodo(Nodo* nodo) {
    nodo->izdo = nodo->dcho = NULL;
    free(nodo);
}
static void InsertarConPadre(Nodo** arbol, Nodo* padre, int valor) {
    if (*arbol == NULL) {
        *arbol = CrearNodo(valor, padre);
    } else {
        int valorRaiz = (*arbol )->valor;
        if (valor < valorRaiz) {
            Insertar(&(*arbol)->izdo, *arbol, valor);
        } else {
            InsertarConPadre(&(*arbol)->dcho, *arbol, valor);
        }
    }
}

void Insertar(Nodo**arbol, int valor) {
    InsertarConPadre(arbol, NULL, valor);
}

int Existe(Nodo* arbol, int valor) {
    if(arbol == NULL) {
        return 0;
    } else if(arbol->valor == valor) {
        return 1;
    } else if (valor < arbol->valor) {
        return Existe(arbol->izdo, valor);
    } else {
        return Existe(arbol->dcho, valor);
    }
}
void DeterminarExistencia(Nodo* arbol, int valor) {
    if (Existe(arbol, valor)) {
        printf("El nodo %d existe en el árbol. \n");
    } else {
        printf("El nodo %d  NO existe en el árbol. \n");
    }
}

Nodo* Obtener(Nodo* arbol, int valor) {
    if(arbol == NULL) {
        return NULL;
    } else if(arbol->valor == valor) {
        return arbol;
    } else if ( valor <  arbol->valor) {
        return Obtener(arbol->izdo, valor);
    } else {
        return Obtener(arbol->dcho, valor);
    }
}

 static void Reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
     if(arbol->padre) {
         if(arbol->valor == arbol->padre->valor) {
             arbol->padre->izdo = nuevoNodo;
         } else if( arbol->valor == arbol->padre->dcho->valor) {
             arbol->padre->dcho = nuevoNodo;
         }
     }
     if(nuevoNodo) {
         nuevoNodo->padre = arbol->padre;
     }
 }

 static Nodo* Minimo(Nodo* arbol) {
     if(arbol == NULL) return NULL;
     if(arbol->izdo) {
         return Minimo(arbol->izdo);
     } else {
        return arbol;
     }
 }

 static void EliminarNodo(Nodo* nodoEliminar) {
     if(nodoEliminar->izdo && nodoEliminar->dcho) {
         Nodo* minimo = Minimo(nodoEliminar->dcho);
         nodoEliminar->valor = minimo->valor;
         EliminarNodo(minimo);
     } else if(nodoEliminar->izdo) {
         Reemplazar(nodoEliminar, nodoEliminar->izdo);
         DestruirNodo(nodoEliminar);
     } else if(nodoEliminar->dcho) {
         Reemplazar(nodoEliminar, nodoEliminar->dcho);
         DestruirNodo(nodoEliminar);
     } else {
         Reemplazar(nodoEliminar, NULL);
         DestruirNodo(nodoEliminar);
     }
 }

 void Eliminar(Nodo* arbol, int valor) {
     if(arbol == NULL)
        return;
    else if (valor < arbol->valor)
        Eliminar(arbol->izdo, valor);
    else if (valor > arbol->valor)
        Eliminar(arbol->dcho, valor);
    else
        EliminarNodo(arbol);
 }

void Preorden(Nodo* arbol) {
    if(arbol == NULL) {
        printf("-");
    } else {
        printf(" %d", arbol->valor);
        Preorden(arbol->izdo);
        Preorden(arbol->dcho);
        printf(" )");
    }
}
void Inorden(Nodo* arbol) {
    if(arbol == NULL) {
        printf("-");
    } else {
        printf("( ");
        Inorden(arbol->izdo);
        if (arbol->padre == NULL) {
            printf(" %d {//}", arbol->valor);
        } else {
            printf(" %d {%d} ", arbol->valor, arbol->padre->valor);
        }
        printf(" %d ", arbol->valor);
        Inorden(arbol->dcho);
        printf(" )");
    }
}

void PostOrden(Nodo* arbol) {
    if(arbol == NULL) {
        printf("-");
    } else {
        printf("( ");
        PostOrden(arbol->izdo);
        PostOrden(arbol->dcho);
        printf(" %d ", arbol->valor);
    }
}

int main(int argc, char **argv) {
    Nodo *arbol = NULL;
    Insertar(&arbol, 5);
    Insertar(&arbol, 10);
    Insertar(&arbol, 25);
    Insertar(&arbol, 17);
    Insertar(&arbol, 14);
    Insertar(&arbol, 9);
    Insertar(&arbol, 22);

    DeterminarExistencia(arbol, 10);
    DeterminarExistencia(arbol, 3);
    DeterminarExistencia(arbol, 9);
    return 0;
}