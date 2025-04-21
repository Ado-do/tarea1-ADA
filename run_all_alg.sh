#!/bin/bash

# Definir colores
ROJO='\e[31m'
VERDE='\e[32m'
AMARILLO='\e[33m'
RESET='\e[0m'

# Verificar el input de número entero entre 8 y 512
if [ "$#" -ne 1 ] || ! [[ "$1" =~ ^-?[0-9]+$ ]] || [ "$1" -lt 8 ] || [ "$1" -gt 512 ]; then
    echo -e "${ROJO}* Uso: $0 <num_points>${RESET}"
    echo -e "${ROJO}<num_points> es un número entero entre 8 y 512${RESET}"
    exit 1
fi

set -e  # Detener el script si hay un error

# Compilación
echo -e "${VERDE}* Compilando, en caso de que haga falta:${RESET}"
make

# Generación de puntos aleatorios
echo -e "\n${VERDE}* Generando nuevo archivo points con $1 puntos aleatorios:${RESET}"
./build/get_random_points "$1"

# Ejecución de programas compilados
echo -e "\n${VERDE}* Ejecutando todos los algoritmos compilados:${RESET}"

echo -e "${AMARILLO}* ./build/brute_force points.txt${RESET}"
./build/brute_force points.txt
echo -e "${AMARILLO}* ./build/divide_and_conquer points.txt${RESET}"
./build/divide_and_conquer points.txt
echo -e "${AMARILLO}* ./build/super_brute_force points.txt${RESET}"
./build/super_brute_force points.txt
echo -e "${AMARILLO}* ./build/super_divide_and_conquer points.txt${RESET}"
./build/super_divide_and_conquer points.txt
