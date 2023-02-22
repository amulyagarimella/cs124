import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

weights_durations = pd.read_csv("weights_durations_2.csv")
# avg_over_dim = weights_durations.groupby("size").mean()
def size_vs (y): 
    sns.lineplot(data=weights_durations, x="size", y=y, hue="dim")
    plt.show()
    plt.clf()

size_vs("max edge weight")
size_vs("total MST weight")
size_vs("avg edge weight")
