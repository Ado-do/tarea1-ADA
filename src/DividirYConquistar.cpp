#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <cfloat>
#include <chrono> 


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

struct Point2D { // Puntos del Conjunto S

	double x, y;

};


double euclidean_distance(Point2D p1, Point2D p2){  // Distancia euclidiana entre 2 puntos
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}



/*
Función fuerza bruta para encontrar la
distancia mínima entre todos los pares 
de puntos en un rango dado
*/

double FuerzaBruta(const std::vector<Point2D*>& P, int inicio, int final){
    
    double distanciaMinima = DBL_MAX;
    
    for(int i = inicio; i < final; i++){
        for(int j = i + 1; j < final; j++){
            double d = euclidean_distance(*P[i],*P[j]);
                
            if(d < distanciaMinima){
                distanciaMinima = d;
            }
        }
    }
    
    return distanciaMinima;
}

/*
Función CargarPuntos carga los puntos aleatorios
a los vectores de puntos P 
*/

void CargarPuntos(std::vector<Point2D> &P, std::ifstream &PuntosRandom){
    double x, y;

        while (PuntosRandom >> x >> y){
                                           // std::cout << "\nIngreso de punto:\n"; // Testeo de funciones    
        P.push_back({x, y});
                                           // std::cout << x << " " << y << std::endl; // Testeo de funciones
        }
}

/*
Función OrdenarPuntosX ordena vector de puntos
según orden creciente de la coordenada x.
*/

void OrdenarPuntosX(std::vector<Point2D*> &X){
    std::sort(X.begin(), X.end(), [](Point2D* a, Point2D* b){
                                           // std::cout << "Comparando X: (" << a->x << ", " << a->y << ") con (" << b->x << ", " << b->y << ")\n";
        return a->x < b->x;
    });
}

/*
Función OrdenarPuntosY ordena vector de puntos
según orden creciente de la coordenada y.
*/

void OrdenarPuntosY(std::vector<Point2D*> &Y){
    std::sort(Y.begin(), Y.end(), [](Point2D* a, Point2D* b) {
                                           // std::cout << "Comparando Y: (" << a->x << ", " << a->y << ") con (" << b->x << ", " << b->y << ")\n";
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
double DistanciaMinFranja(const std::vector<Point2D*>& franja, double d) {
    double distanciaMinima = d;

    for (size_t i = 0; i < franja.size(); ++i) {
        for (size_t j = i + 1; j < franja.size() && (franja[j]->y - franja[i]->y) < distanciaMinima; ++j) {
            double distanciaActual = euclidean_distance(*franja[i], *franja[j]);
    
            if (distanciaActual < distanciaMinima) {
                distanciaMinima = distanciaActual;
            }
        }
    }
    return distanciaMinima;
}

/*Función distanciaMinRecursiva recibe los vectores 
de punteros a puntos X e Y, junto a la posición en
el vector del inicio y del final.
*/
double distanciaMinRecursiva(std::vector<Point2D*>& X, std::vector<Point2D*>& Y, int inicio, int final) {
    int cantidad = final - inicio;

    // Caso base si hay 3 puntos o menos.
    if (cantidad <= 3) {
        return FuerzaBruta(X, inicio, final);
    }


    int mitad = inicio + cantidad / 2;
    Point2D* puntoMedio = X[mitad];


    // Separar puntos ordenados por Y en dos mitades
    // según su posición relativa al punto medio
    
    std::vector<Point2D*> Y_izq, Y_der;
    for (auto* p : Y) {
        if (p->x <= puntoMedio->x) Y_izq.push_back(p);
        else Y_der.push_back(p);
    }

    // Llamadas recursivas para cada mitad
    double dist_izq = distanciaMinRecursiva(X, Y_izq, inicio, mitad);
    double dist_der = distanciaMinRecursiva(X, Y_der, mitad, final);
    double d = std::min(dist_izq, dist_der);

    // Construcción de la franja a partir de un vector
    // ya ordenados en función de y, de manera creciente
    std::vector<Point2D*> franja;
    for (auto* p : Y) {
        if (std::abs(p->x - puntoMedio->x) < d) {
            franja.push_back(p);
        }
    }

    // Se retorna la mínima distancia encontrada entre mitades
    // o dentro de la franja
    return std::min(d, DistanciaMinFranja(franja, d));
}


/*
Función DividirParaConquistar recibe un vector de 
puntos cargados, crea 2 vectores de punteros, 
llama a la función que OrdenarPuntosX e
OrdenaPuntosY y llama a la función recursiva
para inicializar el algoritmo.
*/

double DividirParaConquistar(std::vector<Point2D> &P){
    std::vector<Point2D*> X, Y;

    for (auto& punto : P){

        X.push_back(&punto);
        Y.push_back(&punto);
                                           // std::cout << "Agregando puntero al punto (" << punto.x << ", " << punto.y << ")\n";
        }

    OrdenarPuntosX(X);
    OrdenarPuntosY(Y);

    return distanciaMinRecursiva(X, Y, 0, X.size());

}
 auto start = std::chrono::high_resolution_clock::now();
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " archivo_de_puntos.txt\n";
        return 1;
    }

    std::ifstream archivo(argv[1]);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << argv[1] << "\n";
        return 1;
    }

    std::vector<Point2D> puntos;
    std::vector<Point2D*> X, Y;

    CargarPuntos(puntos, archivo);

    if (puntos.size() < 2) { // Se varía según la necesidad
        std::cerr << "Error: Se requieren al menos dos puntos para calcular la distancia mínima.\n";
        return 1;
    }
    
    double distanciaMinima = DividirParaConquistar(puntos);
    
    std::cout << "Distancia mínima: " << distanciaMinima << std::endl;
    
    auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
std::cout << "Tiempo de ejecución: " << duration.count() << " ns\n";
    return 0;
}
