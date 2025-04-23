#include "points.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

vector<Point2D> get_points_from_file(const string &file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        throw runtime_error("Error: No se pudo abrir el archivo " + file_path);
    }

    vector<Point2D> points;
    Point2D p;
    while (file >> p.x >> p.y) {
        points.push_back(p);
    }
    return points;
}

void print_points(vector<Point2D> &points) {
    size_t n = points.size();
    printf("Vector con %zu puntos:\n", n);
    for (size_t i = 0; i < n; i++) {
        int x = points[i].x, y = points[i].y;
        printf("\t%3zu : ", i);
        printf("(%3d, %3d)\n", x, y);
    }
}

void print_min_distance(const double min_dist, const Point2D p1, const Point2D p2) {
    cout << "Distancia minima encontrada:\n";
    printf("\tdist({%d, %d}, {%d, %d}) = %.2lf\n", p1.x, p1.y, p2.x, p2.y, min_dist);
}
