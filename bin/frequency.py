"""Frequency of characters for the given files."""
from pathlib import Path
from collections import Counter
import sys


def count_chars(files) -> Counter:
    c = Counter()
    for f in files:
        p = Path(f)
        if p.is_file():
            c.update(Counter(p.read_text().lower()))
    return c


def print_stats(c: Counter, filter):
    tmp = [(k, v) for k, v in c.items() if filter(k)]
    total_chars = sum([v for _, v in tmp])
    tmp = [(k, v / total_chars) for k, v in tmp]
    tmp = sorted(tmp, key=lambda x: x[1], reverse=True)
    for k, v in tmp:
        print(f"{k}: {v:.3%}")


if __name__ == "__main__":
    files = sys.argv[1:]
    print(f"Counting characters in {len(files)} files: {files}")

    c = count_chars(files)

    print("ALPHA")
    print_stats(c, filter=lambda x: x.isalpha())

    print()
    print("DIGIT")
    print_stats(c, filter=lambda x: x.isdigit())

    print()
    print("OTHER")
    print_stats(c, filter=lambda x: not x.isalnum())
