#!/bin/bash

echo "n,tiempo_fuerza_bruta(ns),tiempo_dividir_conquistar(ns),tiempo_Superdividir_conquistar,tiempo_Super_fuerza_bruta" > resultados.csv

for ((n=8; n<=512; n*=2)); do
    echo "Generando $n puntos..."
    ./get_random_points $n > points.txt

    echo "Ejecutando brute_force..."
    tiempo_fb=$(./brute_force < points.txt | grep "Tiempo de ejecución" | awk '{print $4}')

    echo "Ejecutando dividir..."
    tiempo_dyq=$(./DividirYConquistar points.txt | grep "Tiempo de ejecución" | awk '{print $4}')

    echo "Ejecutando Super_brute_force..."
    tiempo_sfb=$(./Super_brute_force < points.txt | grep "Tiempo de ejecución" | awk '{print $4}')

    echo "Ejecutando Super dividir..."
    tiempo_sdyq=$(./SuperDividirYConquistar points.txt | grep "Tiempo de ejecución" | awk '{print $4}')

    echo "$n,$tiempo_fb,$tiempo_dyq,$tiempo_sfb,$tiempo_sdyq" >> resultados.csv
done
