#include <chrono>
#include <iostream>
#include <set>
#include <vector>

#include "points.hpp"

using namespace std;

pair<Point2D, Point2D> closest_points;

bool detectorDuplicas(const vector<Point2D> &points) {
    set<Point2D> puntosUnicos;
    for (const auto &p : points) {
        if (!puntosUnicos.insert(p).second) {
            closest_points = {p, p};
            return true;
        }
    }
    return false;
}

double brute_force(vector<Point2D> &points) {
    bool duplicaExiste = detectorDuplicas(points);

    if (duplicaExiste == true) {
        return 0.0;
    }

    double min_dist = euclidean_distance({0, 0}, {100, 100});
    size_t n = points.size();

#ifdef DEBUG
    cout << "Calculando con fuerza bruta las distancias entre todos los puntos:\n";
#endif

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double dist = euclidean_distance(points[i], points[j]);
#ifdef DEBUG
            printf("\tdist(%zu, %zu) = %6.2lf\n", i, j, dist);
#endif
            if (dist < min_dist) {
                closest_points = {points[i], points[j]};
                min_dist = dist;
            }
        }
    }
    return min_dist;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <points_file>.txt\n";
        return EXIT_FAILURE;
    }

    vector<Point2D> points = get_points_from_file(argv[1]);
#ifdef DEBUG
    print_points(points);
#endif

    auto start = std::chrono::high_resolution_clock::now();

    double min_dist = brute_force(points);
    print_min_distance(min_dist, closest_points.first, closest_points.second);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Tiempo de ejecución:\n\t" << duration.count() << " ns\n";

    return 0;
}
