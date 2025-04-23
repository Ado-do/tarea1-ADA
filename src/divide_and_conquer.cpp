#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "points.hpp"

using namespace std;

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
 get_random_points.cpp para la generacion del archivo
 .txt de puntos aleatorios, pues los metodos fueron hechos para recibir
 los puntos del siguiente formato:

    'xx yy \n
     aa bb \n'

o sea, que las coordenadas estan separadas por un espacio
y los puntos por salto de linea. De querer generar puntos propios
tomar en cuenta el formato de entrada por favor.
*/

/*
Función DividirParaConquistar recibe un vector de puntos cargados, crea 2 vectores de
punteros, llama a la función que OrdenarPuntosX e OrdenaPuntosY y llama a la función
recursiva para inicializar el algoritmo.
*/
ClosestPair DividirParaConquistar(vector<Point2D> &P);

/*
Función distanciaMinRecursiva recibe los vectores de punteros a puntos X e Y, junto a la
posición en el vector del inicio y del final.
*/
ClosestPair distanciaMinRecursiva(vector<Point2D *> &X, vector<Point2D *> &Y, int inicio,
                                  int final);

/*
Función DistanciaMinFranja recibe un vector "Franja" de punteros a puntos que incluye
solo aquellos puntos cuya coordenada x se encuentra a una distancia menor a "d" de
la línea divisoria vertical del espacio de búsqueda.

La franja esta ordenada en forma creciente según la coordenada Y desde la función
"DividirParaConquistar".

La función hace que cada punto "i" se compara solo con los puntos "j" tales que la
diferencia en la coordenada "y" entre i y j sea menor que d. Aunque y según la teoría
descrita en el libro de de "Introduction to Algorithms" ya mencionado solo es
necesario revisar 7 puntos "j" por punto i en la franja.
Finalmente devuelve la distancia mínima.
*/
ClosestPair DistanciaMinFranja(const vector<Point2D *> &franja,
                                const ClosestPair &current_closest);

/*
Función fuerza bruta para encontrar la distancia mínima entre todos los pares de puntos en
un rango dado
*/
ClosestPair FuerzaBruta(const vector<Point2D *> &P, int start, int end) {
    ClosestPair result;
    result.distance = numeric_limits<double>::max();

    for (int i = start; i < end; i++) {
        for (int j = i + 1; j < end; j++) {
            double d = euclidean_distance(*P[i], *P[j]);
            if (d < result.distance) {
                result.distance = d;
                result.pair = {*P[i], *P[j]};
            }
        }
    }
    return result;
}

/*
Función OrdenarPuntosX ordena vector de puntos según orden creciente de la coordenada x.
*/
void OrdenarPuntosX(vector<Point2D *> &X) {
    sort(X.begin(), X.end(), [](Point2D *a, Point2D *b) {
        // cout << "Comparando X: (" << a->x << ", " << a->y << ") con (" << b->x << ", "
        // << b->y <<
        // ")\n";
        return a->x < b->x;
    });
}

/*
Función OrdenarPuntosY ordena vector de puntos
según orden creciente de la coordenada y.
*/
void OrdenarPuntosY(vector<Point2D *> &Y) {
    sort(Y.begin(), Y.end(), [](Point2D *a, Point2D *b) {
        // cout << "Comparando Y: (" << a->x << ", " << a->y << ") con (" << b->x << ", "
        // << b->y <<
        // ")\n";
        return a->y < b->y;
    });
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
ClosestPair DistanciaMinFranja(const vector<Point2D *> &franja,
                               const ClosestPair &current_closest) {
    ClosestPair result = current_closest;

    for (size_t i = 0; i < franja.size(); ++i) {
        // Check only the next 7 points as per the algorithm
        for (size_t j = i + 1;
             j < franja.size() && (franja[j]->y - franja[i]->y) < result.distance && j <= i + 7;
             ++j) {
            double distanciaActual = euclidean_distance(*franja[i], *franja[j]);
            if (distanciaActual < result.distance) {
                result.distance = distanciaActual;
                result.pair = {*franja[i], *franja[j]};
            }
        }
    }
    return result;
}

/*
Función distanciaMinRecursiva recibe los vectores de punteros a puntos X e Y, junto a la
posición en el vector del inicio y del final.
*/
ClosestPair distanciaMinRecursiva(vector<Point2D *> &X, vector<Point2D *> &Y, int inicio,
                                  int final) {
    int cantidad = final - inicio;
    ClosestPair result;

    // Caso base si hay 3 puntos o menos.
    if (cantidad <= 3) {
        return FuerzaBruta(X, inicio, final);
    }

    int mitad = inicio + cantidad / 2;
    Point2D *puntoMedio = X[mitad];

    // Separar puntos ordenados por Y en dos mitades según su posición relativa al punto
    // medio en X
    vector<Point2D *> Y_izq, Y_der;
    for (auto *p : Y) {
        if (p->x < puntoMedio->x || (p->x == puntoMedio->x && p->y <= puntoMedio->y))
            Y_izq.push_back(p);
        else
            Y_der.push_back(p);
    }

    // Llamadas recursivas para cada mitad
    ClosestPair dist_izq = distanciaMinRecursiva(X, Y_izq, inicio, mitad);
    ClosestPair dist_der = distanciaMinRecursiva(X, Y_der, mitad, final);

    // Elegir la menor distancia entre las mitades
    result = (dist_izq.distance < dist_der.distance) ? dist_izq : dist_der;

    // Construcción de la franja
    vector<Point2D *> franja;
    for (auto *p : Y) {
        if (abs(p->x - puntoMedio->x) < result.distance) {
            franja.push_back(p);
        }
    }

    // Revisar distancia minima en la franja
    ClosestPair franja_result = DistanciaMinFranja(franja, result);
    return (franja_result.distance < result.distance) ? franja_result : result;
}

/*
Función DividirParaConquistar recibe un vector de puntos cargados, crea 2 vectores de
punteros, llama a la función que OrdenarPuntosX e OrdenaPuntosY y llama a la función
recursiva para inicializar el algoritmo.
*/
ClosestPair DividirParaConquistar(vector<Point2D> &P) {
    ClosestPair result;

    if (P.size() < 2) {
        cerr << "Se necesitan al menos 2 puntos\n";
        return result;
    }

    if (P.size() == 2) {
        result.distance = euclidean_distance(P[0], P[1]);
        result.pair = {P[0], P[1]};
        return result;
    }

    vector<Point2D *> X, Y;
    for (auto &p : P) {
        X.push_back(&p);
        Y.push_back(&p);
    }

    OrdenarPuntosX(X);
    OrdenarPuntosY(Y);

    return distanciaMinRecursiva(X, Y, 0, X.size());
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <points_file>.txt\n";
        return 1;
    }

    vector<Point2D> puntos = get_points_from_file(argv[1]);

    if (puntos.size() < 2) {
        cerr << "El archivo debe contener al menos 2 puntos\n";
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();

    ClosestPair result = DividirParaConquistar(puntos);
    print_min_distance(result.distance, result.pair.first, result.pair.second);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Tiempo de ejecución:\n\t" << duration.count() << " ns\n";

    return 0;
}
