#include <chrono>
#include <iostream>
#include <vector>

#include "points.hpp"

using namespace std;

ClosestPair brute_force(vector<Point2D> &points) {
#ifdef DEBUG
    printf("Calculando con fuerza bruta las distancias entre todos los puntos:\n");
#endif

    ClosestPair result;

    size_t n = points.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double dist = euclidean_distance(points[i], points[j]);

#ifdef DEBUG
            printf("\tdist(p%zu, p%zu) = %6.2lf\n", i, j, dist);
#endif

            if (dist < result.distance) {
                result.distance = dist;
                result.pair = {points[i], points[j]};
            }
        }
    }
    return result;
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

    ClosestPair result = brute_force(points);
    print_min_distance(result.distance, result.pair.first, result.pair.second);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Tiempo de ejecución:\n\t" << duration.count() << " ns\n";

    return 0;
}
