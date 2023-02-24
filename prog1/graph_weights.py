import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import numpy as np
from scipy.optimize import curve_fit

"""weights_durations_1 = pd.read_csv("weights_durations_11.csv")
weights_durations_2 = pd.read_csv("weights_durations_12.csv")
weights_durations_3 = pd.read_csv("weights_durations_9.csv")
weights_durations_3 = weights_durations_3[weights_durations_3["size"]==16384]
weights_durations_4 = pd.read_csv("weights_durations_15.csv")
weights_durations_4["max edge weight"] = weights_durations_4["max edge weight"]**(2)
# todo sqrt avg edge weight and recalculate MST size
weights_durations = pd.concat([weights_durations_1, weights_durations_2, weights_durations_3, weights_durations_4]).reset_index()"""
weights_durations = pd.read_csv("final_data.csv")

# avg_over_dim = weights_durations.groupby("size").mean()
# weights_durations = weights_durations[weights_durations["size"] > 64]
sns.lineplot(data=weights_durations, marker = "o", x="size", y="max edge weight", hue="dim")
# plt.yscale("log", base=2)
# plt.xscale("log", base=2)
for dim in [0,2,3,4]:
    wd_0 = weights_durations[weights_durations.dim==dim]
    # wd_0 = wd_0[wd_0['size'] > 64]
    print(wd_0)
    popt, pcov = curve_fit(lambda x, a, b, c: a * np.exp(-b * x) + c, wd_0.size, wd_0["max edge weight"])
    
    print(f"dim {dim}: {popt}")
# print(pcov)
plt.title("Max edge weight vs. size")
plt.show()
plt.clf()

weights_durations = weights_durations[weights_durations["size"] < 100000]
def size_vs(y, name = None):
    if name is None:
        name = y
    for dim in [0,2,3,4]:
        wd_d = weights_durations[weights_durations.dim==dim]
        # wd_0 = wd_0[wd_0['size'] > 64]
        print(wd_d)
        sns.lineplot(data=wd_d, marker="o", x="size", y=y)
        popt, pcov = curve_fit(lambda x, a, b: pow(x,2) * np.log2(a * pow(x,2)) * a + b, wd_0.size, wd_0[y])
        print(popt)
        plt.title(f"{name} vs. size (nodes)\ndimension {dim}")
        plt.savefig(name + str(dim) + ".png")
        plt.show()
        plt.clf()

# size_vs("max edge weight")
# size_vs("total MST weight", "weight")
# size_vs("avg edge weight")
size_vs("duration (s)", "cut_duration")
