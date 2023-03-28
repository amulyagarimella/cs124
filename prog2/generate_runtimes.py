import pandas as pd
import time as t
import subprocess

names = ["n", "standard runtime (s)", "strassen runtime (s)"]
times = pd.DataFrame(columns=names)
size = 0
end_size = 500
cutoff_even = 200
cutoff_odd = 225
# ntrials = 1
while (size <= end_size):
    print(size)
    start_standard = t.time()
    subprocess.run(["./strassen", "1", str(size)])
    standard = t.time() - start_standard
    start_strassen = t.time()
    subprocess.run(["./strassen", "0", str(size)])
    strassen = t.time() - start_strassen
    new_row = pd.DataFrame([size, standard, strassen]).T
    new_row.columns = names
    times = pd.concat([times, new_row],ignore_index=True)
    #print(times)
    print("\n")
    times.to_csv(f"runtimes_cutoff_{cutoff_even}_{cutoff_odd}.csv")
    size += 1

print(times)