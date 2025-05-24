# ----------------------------------------------------------------------------------------
#               notes
# ----------------------------------------------------------------------------------------
'''
- description
    This script recursively scans a full input folder path and lists all files found,
    then writes their corresponding full output file paths (preserving folder structure)
    into a text file.

    Input folder and output file path are provided as command-line arguments.

- metadata
    Author: Kutay Coskuner (adapted by ChatGPT)
    Version: 1.3
    Last Updated: 2025-05-22

- use case
    Useful for listing all files in a directory tree and mapping them to output paths for batch processing.

- install
    None required (only built-in modules)

- todo
    - Add filtering by file extensions if needed
'''
# ----------------------------------------------------------------------------------------
#               libraries
# ----------------------------------------------------------------------------------------
import os
import sys

# ----------------------------------------------------------------------------------------
#               functions
# ----------------------------------------------------------------------------------------
def scan_files_and_write(input_folder, output_file_path):
    """
    Recursively scan input_folder and write full output file paths preserving folder structure.

    Args:
        input_folder (str): Root input folder to scan.
        output_file_path (str): Path to the output text file where full paths will be written.
    """
    if not os.path.exists(input_folder):
        print(f"Error: Input folder '{input_folder}' does not exist.")
        return

    output_root_folder = os.path.dirname(output_file_path)
    if output_root_folder and not os.path.exists(output_root_folder):
        os.makedirs(output_root_folder)

    with open(output_file_path, "w", encoding="utf-8") as f:
        for root, dirs, files in os.walk(input_folder):
            for filename in files:
                full_input_path = os.path.join(root, filename)
                relative_path = os.path.relpath(full_input_path, input_folder)
                full_output_path = os.path.join(output_root_folder, relative_path)
                f.write(relative_path + "\n")

    print(f"File list written to: {filename}")

# ----------------------------------------------------------------------------------------
#               main
# ----------------------------------------------------------------------------------------
def main():
    if len(sys.argv) != 3:
        print("Usage: python your_script.py <FULL_INPUT_FOLDER> <FULL_OUTPUT_FILE>")
        print("Example: python your_script.py /path/to/input /path/to/output/list.txt")
        return

    input_folder = sys.argv[1]
    output_file = sys.argv[2]

    scan_files_and_write(input_folder, output_file)

# ----------------------------------------------------------------------------------------
#               start
# ----------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
