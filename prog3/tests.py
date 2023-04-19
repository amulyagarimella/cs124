import pandas as pd
import time as t
import subprocess

times = 50
algos = {
    0 : "kk",
    1 : "rr",
    2 : "hc",
    3 : "sa",
    11 : "pp-rr",
    12 : "pp-hc",
    13 : "pp-sa"
}

res = pd.DataFrame()
for a in list(algos.keys()):
    residues = []
    for _ in range(times):
        residue = subprocess.run(["./partition", "0", str(a)],  stdout=subprocess.PIPE).stdout.decode('utf-8')
        print(residue)
        residues.append(residue)
    algo_res = pd.DataFrame(residues)
    algo_res.columns = [a]
    res = pd.concat([res, algo_res],axis=1,ignore_index=True)
    print(res)

res.to_csv("instances.csv")

# TODO runtimes