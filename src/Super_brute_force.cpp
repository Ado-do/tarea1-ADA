#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using uint = unsigned int;

struct Point2D {
    int x, y;

    bool operator<(const Point2D& other) const { // Mejora para optimizar el código
        
        if (x != other.x){
            return x < other.x;
        }

        return y < other.y;
    }

};

bool detectorDuplicas(const std::vector<Point2D>& points) {
   
    std::set<Point2D> puntosUnicos;
    for (const auto& p : points) {
        if (!puntosUnicos.insert(p).second) {
            return true;
        }
    }
    return false; // No se encontraron duplicados
}

pair<int, int> closest_points;


void print_points(vector<Point2D> &points) {
    size_t n = points.size();

    printf("* %zu puntos recibidos:\n", n);
    for (size_t i = 0; i < n; i++) {
        int x = points[i].x, y = points[i].y;
        printf("\t %3zu : ", i);
        printf("(%3d, %3d)\n", x, y);
    }
}

double euclidean_distance(Point2D p1, Point2D p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double brute_force_distances(vector<Point2D> &points) {

    bool duplicaExiste = detectorDuplicas(points);
    
    if(duplicaExiste == true){
        return 0.0;
    }


    double min_dist = euclidean_distance({0, 0}, {100, 100});
    size_t n = points.size();

    cout << "* Calculando con fuerza bruta las distancias entre todos los puntos:\n";
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double dist = euclidean_distance(points[i], points[j]);
            printf("\tdist(%zu, %zu) = %6.2lf\n", i, j, dist);
            if (dist < min_dist) {
                min_dist = dist;
                closest_points = {i, j};
            }
        }
    }
    return min_dist;
}

int main() {
    vector<Point2D> points;

    // Recibir puntos desde entrada estándar (idealmente desde points.txt)
    int x, y;
    while (points.size() < 512 && cin >> x >> y) {
        points.push_back({x, y});
    }

    // Check input
    if (points.size() == 0 || (cin.fail() && !cin.eof())) {
        cerr << "Error: Entrada no válida.\n";
        return EXIT_FAILURE;
    }

    // Mostrar puntos recibidos
    print_points(points);

    auto start = std::chrono::high_resolution_clock::now();
    
    // Calcular distancia entre todos los puntos
    double min_dist = brute_force_distances(points);

    // Mostrar la minima distancia entre puntos encontrada
    cout << "* Distancia minima encontrada:\n";
    printf("\tdist(%d, %d) = %.2lf\n", closest_points.first, closest_points.second, min_dist);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Tiempo de ejecución: " << duration.count() << " ns\n";
    
    return 0;
}