# ----------------------------------------------------------------------------------------
#               notes
# ----------------------------------------------------------------------------------------
'''
- description
    This script reads a markdown file containing a list of filenames or paths,
    applies a smart renaming logic to each filename (preserving extensions),
    and writes the mapping "original → renamed" into a new file named
    as the original with '_renamed' suffix.

- metadata
    Author: Kutay Coskuner (adapted by ChatGPT)
    Version: 1.0
    Last Updated: 2025-05-22

- use case
    Useful for renaming lists of filenames following specific naming rules,
    for batch renaming or organization.

- install
    None required (only built-in modules)

- todo
    - Add option to overwrite original file if needed
    - Add filtering or validation of input lines
'''
# ----------------------------------------------------------------------------------------
#               libraries
# ----------------------------------------------------------------------------------------
import sys
import re
from pathlib import Path
import os


# ----------------------------------------------------------------------------------------
#               functions
# ----------------------------------------------------------------------------------------
def smart_split(name: str) -> str:
    """
    Renames a filename to: version-name-type.ext
    - Lowercases everything
    - Extracts version before last '.'
    - Handles 3d-like tokens properly
    - Recognizes and extracts type (geo, vrtx, etc.)
    - Removes 'shader'
    """
    if '.' in name and not name.startswith('.'):
        base, ext = name.rsplit('.', 1)
        if len(ext) <= 4 and ext.isalpha():
            return smart_split(base) + '.' + ext.lower()

    # Step 1: Split by .
    parts = name.split('.')
    if len(parts) > 1:
        version = ".".join(parts[:-1])
        remainder = parts[-1]
    else:
        version = ""
        remainder = parts[0]

    # Step 2: Split remainder by - and _
    tokens = re.split(r'[-_]', remainder)

    # Step 3: Improved token splitting (no camelCase, preserve "3d", "2k", etc.)
    def smart_tokenize(part):
        return re.findall(r'\d+[a-zA-Z]+|[a-zA-Z]+\d+|[A-Z]?[a-z]+|[A-Z]+(?![a-z])|\d+', part)

    flat_parts = []
    for token in tokens:
        flat_parts.extend(smart_tokenize(token))

    # Step 4: Normalize
    flat_parts = [p.lower() for p in flat_parts if p.lower() != 'shader']

    # Step 5: Classify
    type_ = None
    name_parts = []
    special = {"geo", "geom", "vrtx", "frag"}

    for p in flat_parts:
        if p in special:
            type_ = p
        else:
            name_parts.append(p)

    result = []
    if version:
        result.append(version)
    if name_parts:
        result.append("_".join(name_parts))
    if type_:
        result.append(type_)

    return "-".join(result)


def process_file(md_path: Path):
    """
    Read input markdown file, rename filenames line by line, and write results.
    Preserves full paths, only renaming the filename portion.
    Also replaces all backslashes with forward slashes in the output file.

    Args:
        md_path (Path): Path to input markdown file with list of filenames.
    """
    if not md_path.exists():
        print(f"Error: Input file '{md_path}' does not exist.")
        return

    lines = md_path.read_text(encoding="utf-8").splitlines()
    result_lines = []

    for line in lines:
        line = line.strip()
        if not line:
            continue

        original = line
        path = Path(line)

        # Rename only the stem of the file, keep parent directory
        renamed_name = smart_split(path.stem) + path.suffix.lower()
        renamed_path = path.parent / renamed_name

        # Convert path to string with forward slashes
        renamed_path_str = str(renamed_path).replace("\\", "/")

        result_lines.append(f"{original} → {renamed_path_str}")

    output_content = "\n".join(result_lines)

    # Final step: Replace any backslashes in the whole output content with forward slashes
    output_content = output_content.replace("\\", "/")

    output_path = md_path.with_name(md_path.stem + "_renamed.md")
    output_path.write_text(output_content, encoding="utf-8")

    print(f"✅ Renamed list written to: {output_path}")


# ----------------------------------------------------------------------------------------
#               main
# ----------------------------------------------------------------------------------------
def main():
    if len(sys.argv) != 2:
        print("Usage: python generate_renamed_list.py path/to/shader_list.md")
        return

    input_md = Path(sys.argv[1])
    process_file(input_md)

# ----------------------------------------------------------------------------------------
#               start
# ----------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
