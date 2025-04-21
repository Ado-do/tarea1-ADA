#include "points.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

ClosestPair global_closest;

/*
Implementacion Dividir para Vencer (2) para calcular
la minima distancia euclidiana entre dos puntos. Cuenta con las
consideraciones a tomar para realizarse en unba grilla de 100x100

El codigo a continuacion se basa la explicacion del libro:
Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C.
(2001).Introduction to Algorithms (2nd ed.), MIT Press.
\Section 33.4: Finding the closest pair of points.
Donde se aborda el problema a tratar de manera general.


Como recomendacion a la hora de probar el codigo considere usar
get_random_points.cpp para la generacion del archivo .txt de puntos aleatorios, 
pues los metodos fueron hechos para recibir los puntos del siguiente formato:

    'xx yy \n
     aa bb \n'

o sea, que las coordenadas estan separadas por un espacio
y los puntos por salto de linea. De querer generar puntos propios
tomar en cuenta el formato de entrada por favor.
*/

bool detectorDuplicas(const vector<Point2D> &points) {
    set<Point2D> puntosUnicos;
    for (const auto &p : points) {
        if (!puntosUnicos.insert(p).second) {
            global_closest.distance = 0.0;
            global_closest.p1 = p;
            global_closest.p2 = p;
            return true;
        }
    }
    return false;
}

/*
Función fuerza bruta para encontrar la distancia mínima entre todos los pares de puntos en un rango dado
*/
ClosestPair FuerzaBruta(const vector<Point2D *> &P, int inicio, int final) {
    ClosestPair result;

    for (int i = inicio; i < final; i++) {
        for (int j = i + 1; j < final; j++) {
            double d = euclidean_distance(*P[i], *P[j]);
            if (d < result.distance) {
                result.distance = d;
                result.p1 = *P[i];
                result.p2 = *P[j];

                // Update global closest if this pair is closer
                if (d < global_closest.distance) {
                    global_closest = result;
                }
            }
        }
    }
    return result;
}

/*
Función OrdenarPuntosX ordena vector de puntos según orden creciente de la coordenada x.
*/
void OrdenarPuntosX(vector<Point2D *> &X) {
    sort(X.begin(), X.end(), [](Point2D *a, Point2D *b) { return a->x < b->x || (a->x == b->x && a->y < b->y); });
}

/*
Función OrdenarPuntosY ordena vector de puntos según orden creciente de la coordenada y.
*/
void OrdenarPuntosY(vector<Point2D *> &Y) {
    sort(Y.begin(), Y.end(), [](Point2D *a, Point2D *b) { return a->y < b->y || (a->y == b->y && a->x < b->x); });
}

/*
Función DistanciaMinFranja recibe un vector "Franja" de
punteros a puntos que incluye solo aquellos puntos cuya
coordenada x se encuentra a una distancia menor a "d" de
la línea divisoria vertical del espacio de búsqueda.

La franja esta ordenada en forma creciente según la coordenada
Y desde la función "DividirParaConquistar".

La función hace que cada punto "i" se compara solo con los
puntos "j" tales que la diferencia en la coordenada "y"
entre i y j sea menor que d. Aunque y según la teoría descrita
en el libro de de "Introduction to Algorithms" ya mencionado
solo es necesario revisar 7 puntos "j" por punto i en la franja.

Posterior al proceso descrito la función devuelve la distancia
mínima encontrada en la franja.

*/
ClosestPair DistanciaMinFranja(const vector<Point2D *> &franja, double d) {
    ClosestPair result;
    result.distance = d;

    for (size_t i = 0; i < franja.size(); ++i) {
        for (size_t j = i + 1; j < franja.size() && (franja[j]->y - franja[i]->y) < result.distance; ++j) {
            double distanciaActual = euclidean_distance(*franja[i], *franja[j]);
            if (distanciaActual < result.distance) {
                result.distance = distanciaActual;
                result.p1 = *franja[i];
                result.p2 = *franja[j];

                // Update global closest if this pair is closer
                if (distanciaActual < global_closest.distance) {
                    global_closest = result;
                }
            }
        }
    }
    return result;
}

/*
Función distanciaMinRecursiva recibe los vectores de punteros a puntos X e Y, junto a la posición en
el vector del inicio y del final.
*/
ClosestPair distanciaMinRecursiva(vector<Point2D *> &X, vector<Point2D *> &Y, int inicio, int final) {
    int cantidad = final - inicio;
    ClosestPair result;

    if (cantidad <= 3) {
        return FuerzaBruta(X, inicio, final);
    }

    int mitad = inicio + cantidad / 2;
    Point2D *puntoMedio = X[mitad];

    vector<Point2D *> Y_izq, Y_der;
    for (auto *p : Y) {
        if (p->x < puntoMedio->x || (p->x == puntoMedio->x && p->y <= puntoMedio->y))
            Y_izq.push_back(p);
        else
            Y_der.push_back(p);
    }

    ClosestPair dist_izq = distanciaMinRecursiva(X, Y_izq, inicio, mitad);
    ClosestPair dist_der = distanciaMinRecursiva(X, Y_der, mitad, final);

    result = (dist_izq.distance < dist_der.distance) ? dist_izq : dist_der;

    vector<Point2D *> franja;
    for (auto *p : Y) {
        if (abs(p->x - puntoMedio->x) < result.distance) {
            franja.push_back(p);
        }
    }

    ClosestPair franja_result = DistanciaMinFranja(franja, result.distance);
    return (franja_result.distance < result.distance) ? franja_result : result;
}


/*
Función DividirParaConquistar recibe un vector de 
puntos cargados, crea 2 vectores de punteros, 
llama a la función que OrdenarPuntosX e
OrdenaPuntosY y llama a la función recursiva
para inicializar el algoritmo.

Mejoras!: Ahora antes de inicializar el algoritmo
se revisa que no existan duplicas en los puntos
para seguir. Si se detecta duplica se finaliza el
proceso pues la distancia mínima es 0 
*/
double DividirParaConquistar(vector<Point2D> &P) {
    global_closest = ClosestPair();

    if (detectorDuplicas(P)) {
        return 0.0;
    }

    if (P.size() == 2) {
        global_closest.distance = euclidean_distance(P[0], P[1]);
        global_closest.p1 = P[0];
        global_closest.p2 = P[1];
        return global_closest.distance;
    }

    vector<Point2D *> X, Y;
    for (auto &punto : P) {
        X.push_back(&punto);
        Y.push_back(&punto);
    }

    OrdenarPuntosX(X);
    OrdenarPuntosY(Y);

    distanciaMinRecursiva(X, Y, 0, X.size());
    return global_closest.distance;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <points_file>.txt\n";
        return 1;
    }

    vector<Point2D> puntos = get_points_from_file(argv[1]);

    auto start = chrono::high_resolution_clock::now();
    double distanciaMinima = DividirParaConquistar(puntos);
    auto end = chrono::high_resolution_clock::now();

    print_min_distance(distanciaMinima, global_closest.p1, global_closest.p2);

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Tiempo de ejecución:\n\t" << duration.count() << " ns\n";

    return 0;
}
