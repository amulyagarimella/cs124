import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import numpy as np
from scipy.optimize import curve_fit

weights_durations_1 = pd.read_csv("weights_durations_11.csv")
weights_durations_2 = pd.read_csv("weights_durations_12.csv")
# weights_durations_3 = pd.read_csv("weights_durations_14.csv")
# weights_durations_3["max edge weight"] = weights_durations_3["max edge weight"]**(1/2)
weights_durations = pd.concat([weights_durations_1, weights_durations_2]).reset_index()

# avg_over_dim = weights_durations.groupby("size").mean()
for dim in [0,2,3,4]:
    sns.lineplot(data=weights_durations, x="size", y="max edge weight", hue="dim")
    plt.xscale("log", base=2)
    wd_0 = weights_durations[weights_durations.dim==dim]
    popt, pcov = curve_fit(lambda t, a, b, c: a * np.exp(b * np.log2(t)) + c, wd_0.size, wd_0["max edge weight"])
    print(f"dim {dim}: {popt}")
# print(pcov)
plt.show()
plt.clf()

def size_vs(y):
    sns.lineplot(data=weights_durations, x="size", y=y, hue="dim")
    plt.show()
    plt.clf()

size_vs("max edge weight")
size_vs("total MST weight")
size_vs("avg edge weight")
