import sys
from pathlib import Path
import re

def extract_shader_parts(line):
    pattern = r'\.(vrtx|frag|geom)\s*=\s*"([^"]+)"'
    result = {key: "" for key in ("vrtx", "frag", "geom")}
    for match in re.finditer(pattern, line):
        result[match[1]] = match[2]
    return result

def main():
    if len(sys.argv) != 4:
        print("Usage: python generate_shader_map.py _input/input01.md _input/input02.md _input/input03.md")
        sys.exit(1)

    enums = Path(sys.argv[1]).read_text().splitlines()
    shader_lines = Path(sys.argv[2]).read_text().splitlines()
    geom_flags = Path(sys.argv[3]).read_text().splitlines()
    output_path = Path("_output/output.cpp")

    enums = [e.strip() for e in enums if e.strip()]
    shader_lines = [s.strip() for s in shader_lines if s.strip()]
    geom_flags = [g.strip() for g in geom_flags if g.strip()]

    if not (len(enums) == len(shader_lines) == len(geom_flags)):
        raise ValueError("Input files must have the same number of lines.")

    lines = ["std::map<ShaderID, ShaderResourceDescriptor> shaderMap = {", ""]

    for enum, shader_line, geom_flag in zip(enums, shader_lines, geom_flags):
        parts = extract_shader_parts(shader_line)

        vrtx = parts.get("vrtx", "")
        frag = parts.get("frag", "")
        geom = parts.get("geom", "") if geom_flag == "1" else ""

        lines.append(f"    {{ ShaderID::{enum},")
        lines.append(f"        ShaderResourceDescriptor {{")
        lines.append(f"            .paths = ShaderPaths{{")
        lines.append(f"                .vrtx = \"{vrtx}\",")
        lines.append(f"                .frag = \"{frag}\",")
        lines.append(f"                .geom = \"{geom}\"")
        lines.append(f"            }},")
        lines.append(f"            .renderview_modes = {{")
        lines.append(f"                RenderViewMode::ILLUMINATION")
        lines.append(f"            }}")
        lines.append(f"        }}")
        lines.append(f"    }},")
        lines.append("")

    lines.append("};")
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text("\n".join(lines))
    print(f"✅ Output written to {output_path}")

if __name__ == "__main__":
    main()
