#pragma once

#include <cmath>
#include <string>
#include <vector>

#define MAX_DIST 141.5

struct Point2D {
    int x, y;

    // Mejora para optimizar el código
    bool operator<(const Point2D &other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

struct ClosestPair {
    double distance;
    std::pair<Point2D, Point2D> pair;
    ClosestPair() : distance(MAX_DIST) {}
};

inline double euclidean_distance(const Point2D &p1, const Point2D &p2) { return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)); }

// Funcion que entrega un vector de puntos leidos desde un archivo de texto
std::vector<Point2D> get_points_from_file(const std::string &file_path);

// Funcion que imprime todos los puntos en el vector dado
void print_points(std::vector<Point2D> &points);

// Funcion que imprime una distancia minima y los puntos involucrados
void print_min_distance(const double min_dist, const Point2D p1, const Point2D p2);
