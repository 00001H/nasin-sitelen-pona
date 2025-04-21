import os, pathlib
with open(pathlib.Path(os.getenv("HOME"))/"nsp-map") as f:
    w = {}
    for ln in f:
        try:
            lhs,*rhss = ln.strip().split()
        except:
            continue
        for rhs in rhss:
            for i in range(len(rhs)+1):
                if (pref := rhs[:i]) in w:
                    print(f"Conflict {pref} for {w[pref]} <-> {rhs} for {lhs}")
                    break
            else:
                w[rhs] = lhs
