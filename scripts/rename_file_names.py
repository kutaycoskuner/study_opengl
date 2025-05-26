# ----------------------------------------------------------------------------------------
#               notes
# ----------------------------------------------------------------------------------------
# '''
# - description
#     This script recursively renames file **names only** (not folders) under a given root
#     directory, using mappings of the form "original → renamed".

# - metadata
#     Author: Kutay Coskuner (adapted by ChatGPT)
#     Version: 1.0
#     Last Updated: 2025-05-27

# - use case
#     Useful for renaming many files in a project without modifying their contents
#     or folder structure.

# - install
#     None required (only built-in modules)

# - usage example
#     py rename_file_names.py "C:\path\to\root_folder" "C:\path\to\rename_list.md"
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
    Returns list of (old_name, new_name) tuples.
    """
    lines = mapping_path.read_text(encoding="utf-8").splitlines()
    mappings = []
    for line in lines:
        if '→' in line:
            original, renamed = map(str.strip, line.split('→', 1))
            mappings.append((original, renamed))
    return mappings

def rename_files(root: Path, mappings: list[tuple[str, str]]) -> int:
    """
    Recursively rename files under root directory using provided mappings.
    Returns number of renamed files.
    """
    renamed_count = 0
    for file in root.rglob("*"):
        if file.is_file():
            for old, new in mappings:
                if file.name == old:
                    new_path = file.with_name(new)
                    try:
                        file.rename(new_path)
                        print(f"📄 Renamed: {file} → {new_path}")
                        renamed_count += 1
                    except Exception as e:
                        print(f"❌ Failed to rename {file}: {e}")
                    break  # Skip further matches for this file
    return renamed_count

# ----------------------------------------------------------------------------------------
#               main
# ----------------------------------------------------------------------------------------
def main():
    if len(sys.argv) != 3:
        print("Usage: python rename_file_names.py path/to/root_folder path/to/rename_list.md")
        return

    root_folder = Path(sys.argv[1]).resolve()
    mapping_file = Path(sys.argv[2]).resolve()

    if not root_folder.is_dir():
        print(f"❌ Error: '{root_folder}' is not a valid directory.")
        return

    if not mapping_file.is_file():
        print(f"❌ Error: Mapping file '{mapping_file}' not found.")
        return

    mappings = parse_mapping(mapping_file)
    if not mappings:
        print(f"⚠️ No valid mappings found in: {mapping_file}")
        return

    print(f"📂 Scanning folder: {root_folder}")
    print(f"🔁 Applying {len(mappings)} file renaming rules...")

    renamed_count = rename_files(root_folder, mappings)

    print(f"🏁 Done. Renamed {renamed_count} files.")

# ----------------------------------------------------------------------------------------
#               start
# ----------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
