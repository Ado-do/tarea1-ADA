#!/bin/bash

# Definir colores
VERDE='\e[32m'
RESET='\e[0m'

# Compilación
echo -e "${VERDE}* Compilando, en caso de que haga falta:${RESET}"
make

# Contruyendo archivo csv
output_file="results.csv"

echo "n,bf_time(ns),dc_time(ns),sbf_time(ns),sdc_time(ns)" >"$output_file"
for ((n = 8; n <= 512; n *= 2)); do
    ./build/get_random_points $n > /dev/null # Quitar output de get_random_points

    bf_time=$(./build/brute_force points.txt | sed -n '/Tiempo de ejecución:/!b;n;s/^[ \t]*//;s/ ns//;p')
    dc_time=$(./build/divide_and_conquer points.txt | sed -n '/Tiempo de ejecución:/!b;n;s/^[ \t]*//;s/ ns//;p')
    sbf_time=$(./build/super_brute_force points.txt | sed -n '/Tiempo de ejecución:/!b;n;s/^[ \t]*//;s/ ns//;p')
    sdc_time=$(./build/super_divide_and_conquer points.txt | sed -n '/Tiempo de ejecución:/!b;n;s/^[ \t]*//;s/ ns//;p')

    echo "$n,$bf_time,$dc_time,$sbf_time,$sdc_time" >>"$output_file"
done
echo -e "${VERDE}* Resultados de benchmark guardades en archivo \"$output_file!\"${RESET}"

# Mostrando archivo csv
python src/plot.py 2> /dev/null
