import pandas as pd
import matplotlib.pyplot as plt

# Abre el archivo CSV
df = pd.read_csv('resultados.csv')

# Imprime las primeras filas para verificar el contenido
print(df.head())

# Grafica cada línea
plt.plot(df['n'], df['tiempo_fuerza_bruta(ns)'], label='Fuerza Bruta', marker='o')
plt.plot(df['n'], df['tiempo_dividir_conquistar(ns)'], label='Dividir y Conquistar', marker='s')
plt.plot(df['n'], df['tiempo_Superdividir_conquistar'], label='Super Dividir y Conquistar', marker='^')
plt.plot(df['n'], df['tiempo_Super_fuerza_bruta'], label='Super Fuerza Bruta', marker='x')

# Etiquetas para los ejes x e y
plt.xlabel('Tamaño de la entrada (n)')
plt.ylabel('Tiempo (nanosegundos)')

# Escala logarítmica en el eje y
plt.yscale('log')

# Mostrar leyenda
plt.legend()

# Guardar el gráfico en un archivo
plt.savefig('plot.png')

# Mostrar el gráfico
plt.show()
