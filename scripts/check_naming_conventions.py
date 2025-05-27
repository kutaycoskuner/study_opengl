# ----------------------------------------------------------------------------------------
#               notes
# ----------------------------------------------------------------------------------------
'''
- description
    This script recursively scans a folder for C++ files (.cpp, .h) and checks
    naming conventions for functions and variables. It ignores files in libs/ or lib/
    directories and writes validation results to an output file using full paths.
    Results are ordered (variables first, then functions) with duplicates removed,
    and sorted by status (x first, then v) for easier problem identification.

    Scope folder and output file path are provided as command-line arguments.

- metadata
    Author: Kutay Coskuner (adapted from original template)
    Version: 1.3
    Last Updated: 2025-05-27

- use case
    Useful for checking C++ code naming conventions in large codebases with full path references.

- install
    None required (only built-in modules)

- todo
    - Add support for class member detection
    - Improve enum detection
    - Add configuration file for custom rules
'''
# ----------------------------------------------------------------------------------------
#               libraries
# ----------------------------------------------------------------------------------------
import os
import sys
import re

# ----------------------------------------------------------------------------------------
#               functions
# ----------------------------------------------------------------------------------------
def extract_type_names(content):
    """
    Extract user-defined type names like structs, classes, and templates.
    Returns a set of names.
    """
    type_names = set()
    
    # Match struct/class names: struct MyStruct { or class MyClass {
    pattern = r'\b(?:struct|class)\s+(\w+)\s*\{'
    matches = re.finditer(pattern, content)
    for match in matches:
        type_names.add(match.group(1))
    
    # Match templates: template<typename T> class MyTemplate { ... }
    template_pattern = r'template\s*<[^>]*>\s*(?:class|struct)\s+(\w+)\s*\{'
    template_matches = re.finditer(template_pattern, content)
    for match in template_matches:
        type_names.add(match.group(1))

    return type_names


def remove_comments(content):
    """
    Remove C++ style comments from the content.
    Handles both single-line (//) and multi-line (/* */) comments.
    """
    # Remove multi-line comments /* ... */
    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
    
    # Remove single-line comments // ...
    lines = content.split('\n')
    cleaned_lines = []
    
    for line in lines:
        # Find // not inside string literals
        in_string = False
        escaped = False
        i = 0
        
        while i < len(line):
            if escaped:
                escaped = False
            elif line[i] == '\\' and in_string:
                escaped = True
            elif line[i] == '"' and not escaped:
                in_string = not in_string
            elif line[i:i+2] == '//' and not in_string:
                line = line[:i]
                break
            i += 1
        
        cleaned_lines.append(line)
    
    return '\n'.join(cleaned_lines)

def is_snake_case(name):
    """Check if a name follows snake_case convention."""
    return re.match(r'^[a-z][a-z0-9_]*$', name) is not None

def is_constant_case(name):
    """Check if a name follows CONSTANT_CASE convention."""
    return re.match(r'^[A-Z][A-Z0-9_]*$', name) is not None

def is_private_variable(name):
    """Check if a name is a private variable (starts with underscore)."""
    return name.startswith('_')

def should_ignore_path(file_path):
    """Check if the file path should be ignored (contains libs/ or lib/)."""
    path_parts = file_path.lower().split(os.sep)
    return 'libs' in path_parts or 'lib' in path_parts \
    or 'artifacts' in path_parts \
    or 'build' in path_parts

def is_iterator_variable(content, var_name):
    """Check if a variable is likely an iterator in a loop."""
    # Common iterator patterns
    iterator_patterns = [
        rf'\bfor\s*\([^;]*\b{re.escape(var_name)}\b[^;]*;',  # for(int i = 0; ...)
        rf'\bfor\s*\(\s*auto\s+{re.escape(var_name)}\s*:',   # for(auto i : ...)
        rf'\bfor\s*\(\s*\w+\s+{re.escape(var_name)}\s*:',    # for(int i : ...)
        rf'\bwhile\s*\([^)]*\b{re.escape(var_name)}\b[^)]*\)', # while(i < n)
    ]
    
    for pattern in iterator_patterns:
        if re.search(pattern, content, re.IGNORECASE):
            return True
    
    # Common iterator variable names
    common_iterators = {'i', 'j', 'k', 'idx', 'index', 'it', 'iter'}
    return var_name in common_iterators

def extract_functions(content):
    """Extract function names from C++ content."""
    functions = []
    
    # Pattern for function definitions
    # Matches: return_type function_name(parameters) or return_type function_name()
    function_pattern = r'\b(?:void|int|float|double|char|bool|string|auto|[\w:]+)\s+(\w+)\s*\([^)]*\)\s*\{'
    
    matches = re.finditer(function_pattern, content, re.MULTILINE)
    for match in matches:
        func_name = match.group(1)
        # Skip common library functions and keywords
        if func_name not in ['main', 'if', 'for', 'while', 'switch', 'return']:
            functions.append(func_name)
    
    return functions

def extract_variables(content):
    """Extract variable names from C++ content."""
    variables = []
    
    # Pattern for variable declarations
    # Matches: type variable_name; or type variable_name = value;
    var_pattern = r'\b(?:int|float|double|char|bool|string|auto|const\s+\w+|\w+)\s+(\w+)(?:\s*=\s*[^;]+)?;'
    
    matches = re.finditer(var_pattern, content, re.MULTILINE)
    for match in matches:
        var_name = match.group(1)
        # Skip common keywords and function calls
        if var_name not in ['if', 'for', 'while', 'switch', 'return', 'class', 'struct']:
            # Skip iterator variables
            if not is_iterator_variable(content, var_name):
                variables.append(var_name)
    
    return variables

def is_likely_constant(content, var_name):
    """Check if a variable is likely a constant based on context."""
    # Look for const keyword or #define
    const_pattern = rf'\bconst\s+\w+\s+{re.escape(var_name)}\b'
    define_pattern = rf'#define\s+{re.escape(var_name)}\b'
    
    return (re.search(const_pattern, content, re.IGNORECASE) or 
            re.search(define_pattern, content, re.IGNORECASE))

def validate_naming(name, name_type, content="", is_likely_const=False):
    """
    Validate naming convention.
    
    Args:
        name: The function or variable name
        name_type: 'fun' or 'var'
        content: File content for context checking
        is_likely_const: Whether the variable is likely a constant
    
    Returns:
        'v' for valid, 'x' for invalid
    """
    if name_type == 'fun':
        # Functions should follow snake_case
        return 'v' if is_snake_case(name) else 'x'
    
    elif name_type == 'var':
        # Constants should be UPPERCASE
        if is_likely_const:
            return 'v' if is_constant_case(name) else 'x'
        
        # Private variables should start with _ and follow snake_case
        if is_private_variable(name):
            return 'v' if is_snake_case(name[1:]) else 'x'
        
        # Regular variables should follow snake_case
        return 'v' if is_snake_case(name) else 'x'
    
    return 'x'

def process_cpp_file(file_path):
    type_names = extract_type_names(content)
    """Process a single C++ file and extract functions and variables."""
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        content = remove_comments(content)
        
        results = []
        
        # Extract variables first
        variables = extract_variables(content)
        for var_name in variables:
            is_const = is_likely_constant(content, var_name)
            validity = validate_naming(var_name, 'var', content, is_const)
            results.append((validity, 'var', var_name, file_path))
        
        # Then extract functions
        functions = extract_functions(content)
        for func_name in functions:
            validity = validate_naming(func_name, 'fun')
            results.append((validity, 'fun', func_name, file_path))
        
        return results
    
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
        return []

def sort_results(all_variables, all_functions):
    """
    Sort results to show problematic items (x) first, then valid items (v).
    Within each status group, maintain the original order (variables, then functions).
    
    Args:
        all_variables: List of variable tuples (validity, type, name, path)
        all_functions: List of function tuples (validity, type, name, path)
    
    Returns:
        Sorted list of all results
    """
    # Separate by validity status
    invalid_vars = [item for item in all_variables if item[0] == 'x']
    valid_vars = [item for item in all_variables if item[0] == 'v']
    invalid_funcs = [item for item in all_functions if item[0] == 'x']
    valid_funcs = [item for item in all_functions if item[0] == 'v']
    
    # Combine in order: invalid vars, invalid funcs, valid vars, valid funcs
    return invalid_vars + invalid_funcs + valid_vars + valid_funcs

def check_naming_conventions(scope_folder, output_file_path):
    """
    Scan scope_folder for C++ files and check naming conventions.

    Args:
        scope_folder (str): Root folder to scan for C++ files.
        output_file_path (str): Full path to the output file where results will be written.
    """
    if not os.path.exists(scope_folder):
        print(f"Error: Scope folder '{scope_folder}' does not exist.")
        return

    # Convert to absolute paths
    scope_folder = os.path.abspath(scope_folder)
    output_file_path = os.path.abspath(output_file_path)

    output_root_folder = os.path.dirname(output_file_path)
    if output_root_folder and not os.path.exists(output_root_folder):
        os.makedirs(output_root_folder)

    cpp_extensions = {'.cpp', '.h', '.hpp', '.cc', '.cxx'}
    total_items = 0
    
    # Sets to track already processed names
    processed_variables = set()
    processed_functions = set()
    
    # Collect all results first
    all_variables = []
    all_functions = []
    
    for root, dirs, files in os.walk(scope_folder):
        # Skip lib and libs directories
        if should_ignore_path(root):
            continue
        
        for filename in files:
            file_ext = os.path.splitext(filename)[1].lower()
            if file_ext in cpp_extensions:
                full_path = os.path.abspath(os.path.join(root, filename))
                
                results = process_cpp_file(full_path)
                for validity, item_type, name, path in results:
                    if item_type == 'var':
                        if name not in processed_variables:
                            processed_variables.add(name)
                            all_variables.append((validity, item_type, name, full_path))
                    elif item_type == 'fun':
                        if name not in processed_functions:
                            processed_functions.add(name)
                            all_functions.append((validity, item_type, name, full_path))

    # Sort results: problematic (x) first, then valid (v)
    sorted_results = sort_results(all_variables, all_functions)

    # Write sorted results
    with open(output_file_path, "w", encoding="utf-8") as f:
        # Write header
        f.write("Status\tType\tName\tFullPath\n")
        f.write("-" * 80 + "\n")
        
        # Write sorted results
        for validity, item_type, name, path in sorted_results:
            f.write(f"{validity}\t{item_type}\t{name}\t{path}\n")
            total_items += 1

    # Count problematic vs valid items
    invalid_count = sum(1 for item in sorted_results if item[0] == 'x')
    valid_count = sum(1 for item in sorted_results if item[0] == 'v')

    print(f"Naming convention check completed. {total_items} unique items analyzed.")
    print(f"Variables found: {len(all_variables)}")
    print(f"Functions found: {len(all_functions)}")
    print(f"Problematic items (x): {invalid_count}")
    print(f"Valid items (v): {valid_count}")
    print(f"Results written to: {output_file_path}")
    print(f"Scope folder (full path): {scope_folder}")
    print(f"Output file (full path): {output_file_path}")

# ----------------------------------------------------------------------------------------
#               main
# ----------------------------------------------------------------------------------------
def main():
    if len(sys.argv) != 3:
        print("Usage: python check_naming_conventions.py <SCOPE_FOLDER> <OUTPUT_FILE>")
        print("Example: python check_naming_conventions.py /path/to/cpp/project /path/to/output/results.txt")
        print("")
        print("Note: Both scope folder and output file will use full absolute paths.")
        print("Results are ordered with problematic items (x) first, then valid items (v).")
        return

    scope_folder = sys.argv[1]
    output_file = sys.argv[2]

    check_naming_conventions(scope_folder, output_file)

# ----------------------------------------------------------------------------------------
#               start
# ----------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()