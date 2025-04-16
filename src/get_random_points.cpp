#include <iostream>
#include <fstream>
#include <random>

using namespace std;
using uint = unsigned int;

void validate_input(int argc, char *argv[], uint &n_points) {
    if (argc != 2) {
        cerr << "Usage: ./get_random_points <n_points>\n";
        exit(EXIT_FAILURE);
    }

    try {
        n_points = stoul(argv[1]);
    } catch (invalid_argument const& excep) {
        cerr << "std::invalid_argument::what(): " << excep.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch (out_of_range const& excep) {
        cerr << "std::out_of_range::what(): " << excep.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (n_points < 8 || n_points > 512) {
        cerr << "<n_points> must be between 2^3 (8) and 2^9 (512).\n";
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    uint n_points;
    validate_input(argc, argv, n_points);

    int min_coord = 0, max_coord = 100;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min_coord, max_coord);

    // Abrimos el archivo de salida
    ofstream out("points.txt");
    if (!out) {
        cerr << "No se pudo abrir el archivo points.txt\n";
        return EXIT_FAILURE;
    }

    while (n_points--) {
        int x = distrib(gen), y = distrib(gen);
        out << x << ' ' << y << '\n';
    }

    out.close();
    

    return 0;
}

