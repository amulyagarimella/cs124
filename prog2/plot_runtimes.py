import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

even_cutoff = 15
odd_cutoff = 37
runtimes = pd.read_csv(f"runtimes_cutoff_{even_cutoff}_{odd_cutoff}.csv")
runtimes_odd = runtimes[runtimes.n % 2 == 1]
runtimes_even = runtimes[runtimes.n % 2 == 0]

sns.lineplot(data=runtimes_odd,x="n",y="standard runtime (s)", c="r",label="standard - odd")
sns.lineplot(data=runtimes_odd,x="n",y="strassen runtime (s)", c="b",label="strassen - odd")
plt.xlim([100,250])
plt.ylim([0,0.1])
plt.legend()
plt.title("Odd runtimes")
plt.savefig(f"runtimes_odd_{even_cutoff}_{odd_cutoff}.png")
plt.show()
plt.clf()

sns.lineplot(data=runtimes_even,x="n",y="standard runtime (s)", c="r",label="standard - even")
sns.lineplot(data=runtimes_even,x="n",y="strassen runtime (s)", c="b",label="strassen - even")
plt.xlim([100,250])
plt.ylim([0,0.1])
plt.legend()
plt.title("Even runtimes")
plt.savefig(f"runtimes_even_{even_cutoff}_{odd_cutoff}.png")
plt.show()
plt.clf()
