import pandas as pd
import time as t
import subprocess

names = ["dim", "size", "total MST weight", "avg edge weight", "max edge weight", "MST size", "duration (s)"]
times = pd.DataFrame(columns=names)
size = 262144
ntrials = 1
while (size <= 262144):
    if size == 131072:
        dims = [2,3,4]
    else:
        dims = [0,2,3,4]
    for dim in dims:
        start_time = t.time()
        output = subprocess.run(["./randmst", "0", str(size), str(ntrials), str(dim)], stdout=subprocess.PIPE)
        weight = output.stdout.decode('utf-8').split(",")
        print(weight)
        duration = t.time() - start_time
        new_row = pd.DataFrame([dim, size, weight[0], weight[1], weight[2], weight[3], duration]).T
        new_row.columns = names
        times = pd.concat([times, new_row],ignore_index=True)
        print(times)
        print("\n")
    size *= 2
    times.to_csv("weights_durations_17.csv")
