#!/usr/bin/env python3

from pathlib import Path

ROOT = Path(__file__).parent.parent

START_MARKER = "<!-- REPLACE_MARKER_START -->"
END_MARKER = "<!-- REPLACE_MARKER_END -->"


def read_text_from_c_file() -> list[str]:
    keymap_path = ROOT / "keyboards/crkbd/keymaps/sotte/keymap.c"
    print(f"# Reading '{keymap_path}'")
    return [
        line.strip().removeprefix("/// ").removeprefix("///")
        for line in keymap_path.read_text().splitlines()
        if "///" in line
    ]


def replace_markers(markdown_lines: list[str]):
    readme_path = ROOT / "README.md"
    print(f"# Updating '{readme_path}'")
    readme = readme_path.read_text().splitlines()
    final_lines = [
        *readme[: readme.index(START_MARKER) + 1],
        *markdown_lines,
        *readme[readme.index(END_MARKER) :],
    ]
    new_readme = "\n".join(final_lines)
    readme_path.write_text(new_readme)


def main():
    markdown_text = read_text_from_c_file()
    replace_markers(markdown_text)


if __name__ == "__main__":
    main()
