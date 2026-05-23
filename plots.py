import pandas as pd
import matplotlib.pyplot as plt
import os

df = pd.read_csv("results.csv")

algs = df["algorithm"].unique()
array_types = df["array_type"].unique()
metrics = [("time_ms", "Время, мс"), ("char_cmp", "Посимвольные сравнения")]

os.makedirs("plots", exist_ok=True)

for metric_col, metric_label in metrics:
    for arr_type in array_types:
        plt.figure(figsize=(9, 6))
        sub = df[df["array_type"] == arr_type]
        for alg in algs:
            data = sub[sub["algorithm"] == alg].sort_values("n")
            plt.plot(data["n"], data[metric_col], marker="o", label=alg)
        plt.title(f"{metric_label} — массив: {arr_type}")
        plt.xlabel("n (размер массива)")
        plt.ylabel(metric_label)
        plt.grid(True, alpha=0.3)
        plt.legend()
        out_path = f"plots/{metric_col}_{arr_type}.png"
        plt.savefig(out_path, dpi=120, bbox_inches="tight")
        plt.close()
        print(f"saved {out_path}")

# Сводная таблица: средние значения по алгоритмам
pivot_time = df.pivot_table(index=["array_type", "n"], columns="algorithm",
                            values="time_ms", aggfunc="mean")
pivot_cmp  = df.pivot_table(index=["array_type", "n"], columns="algorithm",
                            values="char_cmp", aggfunc="mean")

pivot_time.to_csv("plots/summary_time.csv")
pivot_cmp.to_csv("plots/summary_cmp.csv")
print("summary CSV written to plots/")
