#include <iostream>
#include <random>

using namespace std;
using uint = unsigned int;


void validate_input(int argc, char *argv[], uint &n_points) {
    if (argc != 2) {
        cerr << "Usage: ./build/gen_random_2dpoints <n_points>\n";
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
        cerr << "<n_points> must be between 2^3 (8) and 2^9 (512), inclusive (item 4).\n";
    }
}

int main(int argc, char *argv[]) {
    uint n_points;
    validate_input(argc, argv, n_points);

    // Plano 100x100
    int min_coord = 0, max_coord = 100;

    // Create a random number generator
    random_device rd;   // Obtain a random number from hardware
    mt19937 gen(rd());  // Seed the generator
    uniform_int_distribution<> distrib(min_coord, max_coord); // Specify uniform distribution

    // Print "n_points" random points
    while (n_points--) {
        int x = distrib(gen), y = distrib(gen);
        cout << x << ' ' << y << '\n';
    }

    return 0;
}
