# ----------------------------------------------------------------------------------------
#               notes
# ----------------------------------------------------------------------------------------
'''
- description
    This script takes a folder scope and a mapping file with lines in the format
    "original → renamed", then replaces all instances of `original` with `renamed`
    inside all `.cpp` and `.h` files under the scope folder (recursively).

- metadata
    Author: Kutay Coskuner (adapted by ChatGPT)
    Version: 1.0
    Last Updated: 2025-05-24

- use case
    Useful for bulk-refactoring filenames or identifiers in C++ source files.

- install
    None required (only built-in modules)

- todo
    - Add backup option before rewriting files
    - Add extension list as a configurable parameter
'''
# ----------------------------------------------------------------------------------------
#               libraries
# ----------------------------------------------------------------------------------------
import sys
from pathlib import Path

# ----------------------------------------------------------------------------------------
#               functions
# ----------------------------------------------------------------------------------------
def parse_mapping(mapping_path: Path) -> list[tuple[str, str]]:
    """
    Parse mapping lines of the form "original → renamed".
    """
    lines = mapping_path.read_text(encoding="utf-8").splitlines()
    mappings = []
    for line in lines:
        if '→' in line:
            original, renamed = map(str.strip, line.split('→', 1))
            mappings.append((original, renamed))
    return mappings

def find_source_files(folder: Path, exts={".cpp", ".h"}) -> list[Path]:
    """
    Recursively find files under folder with matching extensions.
    """
    return [p for p in folder.rglob("*") if p.suffix in exts and p.is_file()]

def apply_replacements(file_path: Path, mappings: list[tuple[str, str]]):
    """
    Read file content, apply all replacements, and write back if changes occurred.
    """
    content = file_path.read_text(encoding="utf-8")
    original_content = content

    for old, new in mappings:
        content = content.replace(old, new)

    if content != original_content:
        file_path.write_text(content, encoding="utf-8")
        print(f"✅ Modified: {file_path}")

# ----------------------------------------------------------------------------------------
#               main
# ----------------------------------------------------------------------------------------
def main():
    if len(sys.argv) != 3:
        print("Usage: python apply_renaming.py path/to/scope_folder path/to/renamed_list.md")
        return

    scope_folder = Path(sys.argv[1])
    mapping_file = Path(sys.argv[2])

    if not scope_folder.is_dir():
        print(f"Error: '{scope_folder}' is not a valid directory.")
        return

    if not mapping_file.is_file():
        print(f"Error: Mapping file '{mapping_file}' not found.")
        return

    mappings = parse_mapping(mapping_file)
    if not mappings:
        print(f"No valid mappings found in: {mapping_file}")
        return

    files = find_source_files(scope_folder)

    print(f"🔍 Found {len(files)} source files. Applying replacements...")

    for file in files:
        apply_replacements(file, mappings)

    print("🏁 All done.")

# ----------------------------------------------------------------------------------------
#               start
# ----------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
