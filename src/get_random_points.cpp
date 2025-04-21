#include <iostream>
#include <fstream>
#include <random>

using namespace std;

const string output_file_name = "points.txt";


void validate_input(int argc, char *argv[], int &n_points) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <n_points>\n";
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
        cerr << "<n_points> debe de estar en el rango [8 (2^3), 512 (2^9)].\n";
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int n_points;
    validate_input(argc, argv, n_points);

    int min_coord = 0, max_coord = 100;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min_coord, max_coord);

    ofstream out(output_file_name);
    if (!out) {
        cerr << "No se pudo abrir el archivo " << output_file_name << "\n";
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n_points; i++) {
        int x = distrib(gen), y = distrib(gen);
        out << x << ' ' << y << '\n';
    }

    printf("Archivo \"%s\" con %d puntos aleatorios creado!\n", output_file_name.c_str(), n_points);
    out.close();

    return 0;
}

