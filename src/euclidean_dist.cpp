#include "points.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Uso: " << argv[0] << " <p1.x> <p1.y> <p2.x> <p2.y>\n";
        return 1;
    }

    Point2D p1, p2;
    try {
        p1 = {stoi(argv[1]), stoi(argv[2])};
        p2 = {stoi(argv[3]), stoi(argv[4])};
    } catch (invalid_argument const& excep) {
        cerr << "std::invalid_argument::what(): " << excep.what() << std::endl;
        return 1;
    } catch (out_of_range const& excep) {
        cerr << "std::out_of_range::what(): " << excep.what() << std::endl;
        return 1;
    }

    printf("euclidean_dist({%d, %d}, {%d, %d}) = %lf\n", p1.x, p1.y, p2.x, p2.y, (double)euclidean_distance(p1, p2));

    return 0;
}
