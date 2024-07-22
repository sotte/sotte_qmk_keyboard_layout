"""Frequency of characters for the given files."""

from collections.abc import Callable
import string
import sys
from collections import Counter
from pathlib import Path
from rich.progress import track


def count_chars(files: list[str]) -> tuple[Counter, Counter]:
    char_counter = Counter()
    bigram_counter = Counter()

    for f in track(files, description="Counting..."):
        p = Path(f)
        if p.is_file():
            text = p.read_text().lower()
            char_counter.update(text)
            bigram_counter.update((text[i : i + 2] for i in range(len(text) - 1)))

    return char_counter, bigram_counter


def print_stats(
    counter: Counter, predicate: Callable[[str], bool], topk: int = 1000
) -> None:
    tmp = [(k, v) for k, v in counter.items() if predicate(k)]
    total_chars = sum([v for _, v in tmp])
    tmp = [(k, v / total_chars) for k, v in tmp]
    tmp = sorted(tmp, key=lambda x: x[1], reverse=True)

    for i, (k, v) in enumerate(tmp[:topk]):
        k = k.replace(" ", "󱁐")
        k = k.replace("\n", "")
        k = k.replace("\t", "")
        print(f"{i:<4}{k}    {v:.2%}")


def main():
    files = sys.argv[1:]
    print(f"Counting characters in {len(files)} files: {files}")

    char_counter, bigram_counter = count_chars(files)
    topk = 50

    print("BIGRAMS just alpha")
    print_stats(
        bigram_counter,
        predicate=lambda k: len(set(k).intersection(string.ascii_lowercase)) == 2,
        topk=30,
    )
    print()

    print("BIGRAMS without alpha keys")
    print_stats(
        bigram_counter,
        predicate=lambda k: k not in ("  ", "\n ", "\n\n")
        and not bool(set(k).intersection(string.ascii_lowercase)),
        topk=topk,
    )
    print()

    print("BIGRAMS without alphanum and whitespace")
    print_stats(
        bigram_counter,
        predicate=lambda k: not bool(
            set(k).intersection(
                string.ascii_lowercase + string.digits + string.whitespace
            )
        ),
        topk=topk,
    )
    print()

    print("ALL")
    print_stats(char_counter, predicate=lambda _: True, topk=50)
    print()

    print("ALPHA")
    print_stats(char_counter, predicate=lambda x: x.isalpha(), topk=50)
    print()

    print("DIGIT")
    print_stats(char_counter, predicate=lambda x: x.isdigit(), topk=50)
    print()

    print("OTHER")
    print_stats(char_counter, predicate=lambda x: not x.isalnum(), topk=50)
    print()


if __name__ == "__main__":
    main()
