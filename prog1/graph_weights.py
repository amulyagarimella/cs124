import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

weights_durations_1 = pd.read_csv("weights_durations_6.csv")
weights_durations_2 = pd.read_csv("weights_durations_7.csv")
weights_durations = pd.concat([weights_durations_1, weights_durations_2]).reset_index()

# avg_over_dim = weights_durations.groupby("size").mean()
def size_vs (y): 
    sns.lineplot(data=weights_durations, x="size", y="total MST weight", hue="dim")
    plt.show()
    plt.clf()

size_vs("max edge weight")
size_vs("total MST weight")
size_vs("avg edge weight")
