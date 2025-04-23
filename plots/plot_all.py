import pandas as pd
import matplotlib.pyplot as plt

input_file = "results.csv"
output_file = "plot_all.png"

try:
    df = pd.read_csv(input_file)

    # Revisar columnas especificadas
    required_cols = ["n", "bf_time(ns)", "dc_time(ns)", "sbf_time(ns)", "sdc_time(ns)"]
    if not all(col in df.columns for col in required_cols):
        missing = [col for col in required_cols if col not in df.columns]
        raise ValueError(f"Faltan columnas requeridas: {missing}")

    print("Vista previa de los datos:")
    print(df.head())

    # Configurar el gráfico
    plt.figure(figsize=(8, 5))

    # Graficar cada algoritmo
    plt.plot(df["n"], df["bf_time(ns)"], label="brute_force", marker="o", linestyle="-")
    plt.plot(df["n"], df["dc_time(ns)"], label="divide_and_conquer", marker="s", linestyle="--")
    plt.plot(df["n"], df["sbf_time(ns)"], label="super_brute_force", marker="^", linestyle="-.")
    plt.plot( df["n"], df["sdc_time(ns)"], label="super_divide_and_conquer", marker="x", linestyle=":")

    # Personalizar el gráfico
    plt.xlabel("Tamaño de entrada (n)")
    plt.ylabel("Tiempo (nanosegundos)")
    plt.yscale("log")
    plt.grid(True, which="both", alpha=0.2)
    plt.legend()
    plt.tight_layout()

    plt.savefig(output_file, dpi=150)
    print(f"Gráfico generado como '{output_file}'")
    plt.show()

except FileNotFoundError:
    print(f"Error: No se encontró el archivo '{input_file}'")
except Exception as e:
    print(f"Error: {e}")
