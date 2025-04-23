#!/bin/bash

# Definir colores
R='\e[31m' # rojo
G='\e[32m' # verde
Y='\e[33m' # amarillo
RESET='\e[0m'

# Verificar el input de número entero entre 8 y 512
if [ "$#" -ne 1 ] || ! [[ "$1" =~ ^-?[0-9]+$ ]] || [ "$1" -lt 8 ] || [ "$1" -gt 512 ]; then
    echo -e "${R}* Uso: $0 <num_points>${RESET}"
    echo -e "${R}<num_points> es un número entero entre 8 y 512${RESET}"
    exit 1
fi

set -e  # Detener el script si hay un error

# Compilación
echo -e "${G}* Compilando, en caso de que haga falta:${RESET}"
make

# Generación de puntos aleatorios
echo -e "\n${G}* Generando nuevo archivo points con $1 puntos aleatorios:${RESET}"
./build/get_random_points "$1"

# Ejecución de programas compilados
echo -e "\n${G}* Ejecutando todos los algoritmos compilados:${RESET}"

echo -e "${Y}./build/brute_force points.txt${RESET}"
./build/brute_force points.txt
echo -e "${Y}./build/divide_and_conquer points.txt${RESET}"
./build/divide_and_conquer points.txt
echo -e "${Y}./build/super_brute_force points.txt${RESET}"
./build/super_brute_force points.txt
echo -e "${Y}./build/super_divide_and_conquer points.txt${RESET}"
./build/super_divide_and_conquer points.txt
