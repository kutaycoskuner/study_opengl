# ----------------------------------------------------------------------------------------
#               notes
# ----------------------------------------------------------------------------------------
# '''
# - description
#     This script takes a folder scope and a mapping file with lines in the format
#     "original → renamed", then replaces all instances of `original` with `renamed`
#     inside all `.cpp`, `.h`, and `.txt` files under the scope folder (recursively).

# - metadata
#     Author: Kutay Coskuner (adapted by ChatGPT)
#     Version: 1.2
#     Last Updated: 2025-05-27

# - use case
#     Useful for bulk-refactoring filenames or identifiers in C++ source files.

# - install
#     None required (only built-in modules)

# - todo
#     - Add backup option before rewriting files
#     - Add extension list as a configurable parameter
#     - Example:
#         py rename_from_input.py "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl" "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\scripts\_output\output_renamed.md"
# '''
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
    Does literal string parsing only — no path resolving.
    """
    lines = mapping_path.read_text(encoding="utf-8").splitlines()
    mappings = []
    for line in lines:
        if '→' in line:
            original, renamed = map(str.strip, line.split('→', 1))
            mappings.append((original, renamed))
    return mappings

def find_source_files(folder: Path, exts={".cpp", ".h", ".txt"}) -> list[Path]:
    """
    Recursively find files under folder with matching extensions.
    Returns a list of absolute Path objects.
    """
    folder = folder.resolve()
    return [p.resolve() for p in folder.rglob("*") if p.suffix in exts and p.is_file()]

def apply_replacements(file_path: Path, mappings: list[tuple[str, str]]) -> bool:
    """
    Read file content, apply all replacements, and write back if changes occurred.
    Returns True if modified.
    """
    try:
        content = file_path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        try:
            content = file_path.read_text(encoding="latin1")
            print(f"⚠️  Non-UTF8 file read using latin1: {file_path}")
        except Exception as e:
            print(f"❌ Failed to read {file_path}: {e}")
            return False

    original_content = content
    modified = False

    for old, new in mappings:
        if old in content:
            print(f"🔁 {file_path.name}: '{old}' → '{new}'")
            content = content.replace(old, new)
            modified = True

    if modified:
        try:
            file_path.write_text(content, encoding="utf-8")
            print(f"✅ Modified: {file_path}")
        except Exception as e:
            print(f"❌ Failed to write {file_path}: {e}")
            return False
    return modified

# ----------------------------------------------------------------------------------------
#               main
# ----------------------------------------------------------------------------------------
def main():
    if len(sys.argv) != 3:
        print("Usage: python rename_from_input.py path/to/scope_folder path/to/renamed_list.md")
        return

    scope_folder = Path(sys.argv[1]).resolve()
    mapping_file = Path(sys.argv[2]).resolve()

    if not scope_folder.is_dir():
        print(f"❌ Error: '{scope_folder}' is not a valid directory.")
        return

    if not mapping_file.is_file():
        print(f"❌ Error: Mapping file '{mapping_file}' not found.")
        return

    mappings = parse_mapping(mapping_file)
    if not mappings:
        print(f"⚠️ No valid mappings found in: {mapping_file}")
        return

    print(f"📂 Scanning folder: {scope_folder}")
    files = find_source_files(scope_folder)
    print(f"🔍 Found {len(files)} source files. Applying {len(mappings)} replacements...")

    modified_count = 0
    for file in files:
        if apply_replacements(file, mappings):
            modified_count += 1

    print(f"🏁 All done. {modified_count} files modified out of {len(files)}.")

# ----------------------------------------------------------------------------------------
#               start
# ----------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
