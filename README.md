# nasin sitelen pona: a fcitx5 toki pona IME

[nsp.webm](https://github.com/user-attachments/assets/8e178d34-5301-4807-a5f4-a6735de6e47d)

(video has a slightly outdated version of `nsp-map`)

## Installation

Clone the repository, create an empty folder called `bin`, then invoke `make`.

**KNOWN ISSUE: As cp is used instead of install, ~/nsp-map won't be accessibly by default. Manually run `sudo chown <your user> ~/nsp-map`, `sudo chgrp <your group> ~/nsp-map`, and `chmod a+rw ~/nsp-map`.**

Requires `gcc`.  If GCC complains that it doesn't know about `-std=c++26`, try with `-std=c++23` or (untested) `-std=c++20`.

## Usage

The file `nsp-map` should be created in your user home directory. You can customize it however you want. Each line of the file is of the form `nimi ab [cd...]` where `nimi` is a toki pona word (must be supported by UCSUR), and is followed by one or more keystroke sequences.
(Note: You need to restart fcitx every time you change this file.)

To maximize typing efficiency, words are inserted immediately once the keystrokes are typed, meaning that no keystroke sequence can be a prefix of another. The utility script `check-conflicts.py` attempts to check this, but is not perfect. (Specifically, it fails to recognize a sequence that is a prefix of a longer sequence that appeared *earlier* in the file.)

## Planned features

- Normal sitelen Lasina support with an extended dictionary (may be user-supplied)
- Customizable word-to-ucsur mapping
- UI configuration of `nsp-map`
- robust `check-conflicts` script

You are welcome to fork this project and help out.

P.S. If you didn't know, fcitx is [officially pronounced \['faɪtɪks\]](https://fcitx-im.org/wiki/Fcitx_5) (even though I think they actually meant ['fä͜ɪtʰɪkʰs])
