# Legacy workflows

Superseded GitHub Actions workflows, kept for reference only. GitHub only runs workflow files placed directly in `.github/workflows/`, so nothing in this folder runs.

| File | What it was | Superseded | Replaced by | Not carried over |
| :--- | :--- | :--- | :--- | :--- |
| `cmake-platform-windows.yml` | Built Release with CMake + Visual Studio 2022 on `windows-latest` through `--GenerateBuildProject.bat`, on pushes and pull requests to `main` (configure/build/test steps commented out) | 11-Oct-2026, xmake migration (after `b89eddb`) | `../xmake-windows.yml`: MSYS2 CLANG64 + xmake build on `main` and `dev`, packs `artifacts/` and uploads it | Nothing; the commented-out `ctest` step was never active |

## Changes
- 20261011 — added `cmake-platform-windows.yml` (moved from `.github/workflows/`)
