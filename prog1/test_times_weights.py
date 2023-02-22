import pandas as pd
import time as t
import subprocess

names = ["dim", "size", "total MST weight", "avg edge weight", "max edge weight", "MST size", "duration (s)"]
times = pd.DataFrame(columns=names)
size = 65536.0
ntrials = 1
while (size < 262144):
    for dim in [0,2,3,4]:
        start_time = t.time()
        output = subprocess.run(["./randmst", "0", str(size), str(ntrials), str(dim)], stdout=subprocess.PIPE)
        weight = output.stdout.decode('utf-8').split(",")
        duration = t.time() - start_time
        new_row = pd.DataFrame([dim, size, float(weight[0]), float(weight[1]), float(weight[2]), float(weight[3]), duration]).T
        new_row.columns = names
        times = pd.concat([times, new_row],ignore_index=True)
        print(times)
        print("\n")
    size *= 2
    times.to_csv("weights_durations_4.csv")
