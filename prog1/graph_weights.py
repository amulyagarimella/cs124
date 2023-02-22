import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

weights_durations = pd.read_csv("weights_durations.csv")
# avg_over_dim = weights_durations.groupby("size").mean()
sns.lineplot(data=weights_durations, x="size", y="total MST weight", hue="dim")
plt.show()
plt.clf()

sns.lineplot(data=weights_durations, x="size", y="avg edge weight", hue="dim")
plt.show()
plt.clf()