#!/usr/bin/python
import sys,pathlib
if len(sys.argv) != 4:
    print("Usage: drop-icons input-file name theme-dir")
    sys.exit(1)
src_file = pathlib.Path(sys.argv[1])
with open(src_file) as sf:
    svg = sf.read()
name = sys.argv[2]
theme_dir = pathlib.Path(sys.argv[3])
for size in (16,22,24,32,64):
    dpath = theme_dir/"status"/str(size)
    if dpath.exists():
        dfile = dpath/name
        with open(dfile,"w") as df:
            print(f"Writing {dfile.absolute()}")
            df.write(svg)
    else:
        print(f"Skipping nonexist folder {dpath.absolute()}",file=sys.stderr,flush=True)
