import pandas as pd
import matplotlib.pyplot as plt

input_file = "results.csv"
output_file = "plot_bf_dv.png"

try:
    df = pd.read_csv(input_file)

    required_cols = ["n", "bf_time(ns)", "dc_time(ns)"]
    if not all(col in df.columns for col in required_cols):
        missing = [col for col in required_cols if col not in df.columns]
        raise ValueError(f"Missing required columns: {missing}")

    print("Data preview:")
    print(df.head())

    plt.figure(figsize=(8, 5))

    plt.plot(df["n"], df["bf_time(ns)"], label="brute_force", marker="o", linestyle="-")
    plt.plot(df["n"], df["dc_time(ns)"], label="divide_and_conquer", marker="s", linestyle="--")

    plt.xlabel("Input size (n)")
    plt.ylabel("Time (nanoseconds)")
    plt.yscale("log")
    plt.grid(True, which="both", alpha=0.2)
    plt.legend()
    plt.tight_layout()

    plt.savefig(output_file, dpi=150)
    print(f"Plot generated as '{output_file}'")
    plt.show()

except FileNotFoundError:
    print(f"Error: File '{input_file}' not found")
except Exception as e:
    print(f"Error: {e}")
