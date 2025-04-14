#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

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

Funcion Ordenar_Puntos ordena los puntos (recibidos del .txt con los puntos aleatorios)
en 3 vectores: 

	P: Vector de todos los puntos.
	X: Vector de punteros a los puntos de P, 
	ordenados de manera creciente segun la coordenada x.
	Y: Vector de punteros a los puntos de P,
	ordenados de manera creciente segun la coordenada y.

*/

void Ordenar_Puntos(std::vector<Point2D> &P,std::vector<Point2D*> &X, std::vector<Point2D*> &Y, std::ifstream &PuntosRandom){

	double x, y;

    	while (PuntosRandom >> x >> y){
                                           // std::cout << "\nIngreso de punto:\n"; // Testeo de funciones    
        P.push_back({x, y});
                                           // std::cout << x << " " << y << std::endl; // Testeo de funciones
    	}


	for (auto& punto : P){

        X.push_back(&punto);
        Y.push_back(&punto);
                                           // std::cout << "Agregando puntero al punto (" << punto.x << ", " << punto.y << ")\n";
   }

    std::sort(X.begin(), X.end(), [](Point2D* a, Point2D* b){
                                           // std::cout << "Comparando X: (" << a->x << ", " << a->y << ") con (" << b->x << ", " << b->y << ")\n";
        return a->x < b->x;
    });

    std::sort(Y.begin(), Y.end(), [](Point2D* a, Point2D* b) {
                                           // std::cout << "Comparando Y: (" << a->x << ", " << a->y << ") con (" << b->x << ", " << b->y << ")\n";
        return a->y < b->y;
    });

}


/*
Funcion Dividir traza una linea imaginaria que como es de esperar
divide la grilla en la mitad, a su vez crea vectores de punteros
que almacenan al igual que su version general referencias a los puntos
ordenados de mayor a menor considerando los cambios en sus limites.
*/


void Dividir(std::vector<Point2D> &P,std::vector<Point2D> &P_i, std::vector<Point2D> &P_d, 
            std::vector<Point2D*> &X, std::vector<Point2D*> &X_i, std::vector<Point2D*> &X_d,
            std::vector<Point2D*> &Y, std::vector<Point2D*> &Y_i, std::vector<Point2D*> &Y_d){


    int n = X.size();
    int mitad = n/2;

    for(int i = 0; i < mitad; i++){
        P_i.push_back(*X[i]);
          X_i.push_back(&P_i.back()); 
    }

    for(int i = mitad; i < n; i++){
        P_d.push_back(*X[i]);
        X_d.push_back(&P_d.back());  
    }

   for (auto *p : Y) {
        
        if (p->x <= X[mitad - 1]->x) {
        
            auto it = std::find_if(P_i.begin(), P_i.end(), [&](Point2D &pi) {
        
                return pi.x == p->x && pi.y == p->y;
            });
        
            if (it != P_i.end()) Y_i.push_back(&(*it));
        
        } else {
        
            auto it = std::find_if(P_d.begin(), P_d.end(), [&](Point2D &pd) {
        
                return pd.x == p->x && pd.y == p->y;
            });
        
            if (it != P_d.end()) Y_d.push_back(&(*it));
        }
    }

}

int main() {
   
    std::ifstream archivo("puntos.txt");

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo puntos.txt" << std::endl;
        return 1;
    }

    std::vector<Point2D> P;
    std::vector<Point2D*> X;
    std::vector<Point2D*> Y;

    Ordenar_Puntos(P, X, Y, archivo);

    std::vector<Point2D> PL, PR;
    std::vector<Point2D*> XL, XR, YL, YR;

    Dividir(P,PL,PR,X,XL,XR,Y,YL,YR);

    std::cout << "\n--- Mitad Izquierda (PL) ---\n";
    for (auto &p : PL) std::cout << "(" << p.x << ", " << p.y << ")\n";

    std::cout << "\n--- Mitad Derecha (PR) ---\n";
    for (auto &p : PR) std::cout << "(" << p.x << ", " << p.y << ")\n";

    std::cout << "\n--- YL ordenado por Y ---\n";
    for (auto *p : YL) std::cout << "(" << p->x << ", " << p->y << ")\n";

    std::cout << "\n--- YR ordenado por Y ---\n";
    for (auto *p : YR) std::cout << "(" << p->x << ", " << p->y << ")\n";

    return 0;
}