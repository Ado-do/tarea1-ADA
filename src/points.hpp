#pragma once

#include <cmath>
#include <string>
#include <vector>

#define MAX_DIST euclidean_distance({0, 0}, {100, 100})

struct Point2D {
    int x, y;

    // Mejora para optimizar el código
    bool operator<(const Point2D &other) const {
            // Funcion que retorn la distancia euclideana entre dos puntos
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

inline double euclidean_distance(const Point2D &p1, const Point2D &p2) { return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)); }

struct ClosestPair {
    double distance;
    Point2D p1;
    Point2D p2;
    ClosestPair() : distance(MAX_DIST) {}
};


extern std::pair<Point2D, Point2D> closest_points;

// Funcion que entrega un vector de puntos leidos desde un archivo de texto
std::vector<Point2D> get_points_from_file(const std::string &file_path);

// Funcion que imprime todos los puntos en el vector dado
void print_points(std::vector<Point2D> &points);

// Funcion que imprime una distancia minima y los puntos involucrados
void print_min_distance(const double min_dist, const Point2D p1, const Point2D p2);
