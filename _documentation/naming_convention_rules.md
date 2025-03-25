---
template: 1.6
revision: 0.6.0
title: Code Standards [Draft]
description: A self-defined standard for naming conventions in programming to ensure quality, cohesion, and consistency in code.
category:
  - repository
tags:
  - organization
  - programming
  - discipline
created: 2023-04-18
updated: 2025-03-12
author: lichzelg
translator: null
editor: null
image: first-blog-post.jpg
image_credit: null
language: en
visibility: true
sort_order: 2
---

This document is a self-defined standard developed from various sources and experiences to ensure cohesive and consistent code quality. It considers key parameters such as readability, consistency, aesthetics, writing/editing efficiency, and platform independence.

---

## Terminology

- Naming Conventions

  - **flatcase**: `myvariablename`
  - **snake_case**: `my_variable_name`
  - **PascalCase**: `MyVariableName`
  - **camelCase**: `myVariableName`
  - **kebab-case**: `my-variable-name`
  - **mixed_caseNaming**: `My_variableName`

- Letter Cases

  - **lower case**: `all lowercase`
  - **upper case / capital case**: `ALL UPPER CASE`
  - **proper case / title case**: `All Proper Case`
  - **sentence case**: `First word capitalized.`

- Programming Languages and Abbreviations

  - **C** `c`
  - **C++** `cpp`
  - **JavaScript** `js`
  - **Python** `py`
  - **Cascading Style Sheets** `css`

- Brackets

  - () `Parantheses`
  - {} `Curly braces`
  - [] `Square braces`
  - <> `Angle brackets`

- Indentation Styles

  - Allman (BSD Style)   
  ```cpp
    function do_things()
    {
    }
  ```

  - K&R Style (Kernighan & Ritchie)
  ```cpp
    function do_things() {
    }
  ```

- Special Character Names
  - \- `dash`
  - ; `semicolon`
  - \` `backtick`
  - & `ampersand`
  - : `colon`
  - &nbsp; `whitespace`
  - \_ `underscore`

---

## Broad Guidelines for Naming Things

1. **Use U.S. English spelling and grammar in all code and comments.**

   - **Good**: `color`, `initialize`
   - **Bad**: `colour`, `initialise`

2. **Consider the reader’s perspective, not the writer’s.**

   - **Good**: `calculateDistance()` - clear and meaningful
   - **Bad**: `calcDst()` - too abbreviated

3. **Avoid ambiguous names, analogies, or context-specific terms.**

   - **Good**: `totalUsers`
   - **Bad**: `stuff` or `data123`

4. **Use abbreviations only when the meaning is clear and consistent as it helps with aligned code editing.**

   - **Good**: `vrtx` for vertex
   - **Bad**: `col` for color (collision with "column")

5. **Prepositions are not included in capitalization or words separation.**

   - **Good**: `distancetoNextNode`
   - **Bad**: `DistanceToNextNode`

---

## Broad Guidelines for Formatting

1. **Be consistent on maximum character length on rows including comments.**  
  Reason: this will provide a standard view for various platforms and monitors.

2. **Imports are on separate lines.**  
  Reason: allows code editing disabling / enabling.
   - **Good**:
     ```python
     import os
     import sys
     ```
   - **Bad**:
     ```python
     import os, sys
     ```

3. **Use 4 spaces or 8 spaces for indentation.**  
  Reason: Passively preventing you from over-indentation; thus increasing code readability.

   - **Good**:
     ```python
     def my_function():
         print("Hello, world!")
     ```
   - **Bad**:
     ```python
     def my_function():
       print("Hello, world!")
     ```

4. **Use white space for readability.**  
  Reason: Increasing readability.
   - **Good**:
     ```cpp
     int result = (value1 + value2) / (total - count);
     ```
   - **Bad**:
     ```cpp
     int result=value1+value2/(total-count);
     ```

5. **Use Allman or K&D Style Indentation**  
  Reason: This is mainly personal preference. I find Allman much more readable but increasing code length as a trade off.

6. Favor and use alignment for better readability.  
  Reason: Code is easier to read and edit.

## - Commenting and Commit messages
**Commit messages**

- should be concise, descriptive, and written in **lowercase** separated by commas  
  Examples:  
  `fix memory leak, optimize loop`  
  `add validation for user input; remove unused imports`

**Comments**  
- Should follow **lowercase** or **sentence case**.  
- Some suggested usage of comments `license, metadata, citation, link, descriptive, separator, marker or visual`

1. **Descriptive Comments**:

- Used to explain the purpose of code blocks, algorithms, or logic.
  ```cpp
  // Initialize the matrix with default values
  ```

2. **Separator Comments**:

- Used to visually group sections of code.
  ```cpp asd
  // -----------------------------------------------------------------------------------
  //         Data Preprocessing Section
  // -----------------------------------------------------------------------------------
  ```

3. **Marker Comments**:

- Highlights critical parts, such as TODOs or FIXMEs. Usually aimed to be searched.
  ```cpp
  // TODO: Add validation for empty inputs
  // todo: Add validation for empty inputs
  ```

4. **Visual Description Comments**:

- Uses ASCII art or other visualization to represent concepts or improve code readability.
  ```python
  #   Cosine function visualization
  #
  #                *
  #             *     *
  #           *         *
  #         *             *
  #       *                 *
  # ---*---*---*---*---*---*---*--> x
  #     0   π/2   π    3π/2  2π
  ```

## - Files and Directories
**Directories / Folders**

1. Use **snake_case** for folder names.  
  Examples:
  ```
  user_profiles/
  data_processing/
  api_endpoints/
  ```

**File names**

1. Use **snake_case** for simple code file names (slugs) unless they contain.  
  Examples:
  ```
  user_profile_handler.py
  data_processing_service.cpp
  api_handler.js
  ```

2. Sometimes name of file could contain more various information about the data instead of just name or slug. In that case various metadata types should be separated by a dash (-)   

    **Rationale**: whitespace ( ) may cause some errors on commands. Underscore(_) does not allow to jump word to word by control and is already reserved for replacing white space ( ) on slug.
Examples:
```
1.3-axes-vrtx_shader.glsl               a name for shader file
4.1-bloom-test_scene.cpp                a code file with metadata
tex-linegrid_16-white-2k-color.jpg      a texture file metadata 
core-ui.cpp                             use dash if you are using prefix instead of directories
(fileprefix-slug-detail-resolution-type)
```


3. File names could hold **prefix** or **abbreviated keywords** to sort related file together.   
  Examples:
  ```
  abst      abstract data types    (structs / classes)
  data      data                   (models, scenes, vertices, materials input in general)
  map       mapping                (how to associate data / mappings ex. shader with file names)
  core      core                   (main file)
  util      utililities            (self written library functions, parsers / calculators etc.)
  test      testing                (test files)
  ```

4. For static third party library folders: version number attached via "-"   
  Example(s):  
  ```
  glm-0.9.9.8
  ```

---

## - Variables
- Use **snake_case** for variables and constants.  
  Reason of choice over `camelCase` better readability and writing efficiency. Tradeoffs: long naming, unable to provide categorization on names.

    Single character prefixes avoided to use because it has collision for certain naming.

  Examples:
  ```cpp
    int user_age = 25;
  ```

- Certain data types could be marked with prefixes.  But not with single characters due to collision on naming such as `v_tex_coords` (vertex texture coordinates) `g_buffer` etc.  
Examples:  
```
  global              : gl_variable                         (important for distinction)
  bools               : is_visible, has_alpha, use_shadows  (has verb that answers yes/no question)
  constants           : VARIABLE                            (CAPITALIZED_SNAKE_CASE)
  pointers            : ptr_variable                        (important for distinction)
  const char pointer  : PTR_VARIABLE                        (combination of const and pointer)       
  private variable    : _private                            (underscore as prefix to indicate private variable)
```

### -- Constants
- Use **snake_case** with a leading underscore for private members.  
  Examples:
  ```cpp
  const int MAX_LIGHT_COUNT = 100;
  ```

### -- Private Members
- Use **snake_case** with a leading underscore for private members.  
  Examples:
  ```cpp
  class UserProfile {
  private:
    std::string _name;
  };
  ```

### -- Enums
- Use **UPPER_SNAKE_CASE** for enum values.  
  Examples:
  ```cpp
  enum class Color {
    RED,
    GREEN,
    BLUE
  };
  ```

## - Functions
- Use **snake_case** for naming functions.  
- Starts with verb, as functions reflect some action.
- Try to describe what function does precisely and shortly as much as possible.
- Avoid ambiguities, meaning dualities or names with context.
  Examples:
  ```cpp
  void calculate_total(int price, int quantity) {
    return price * quantity;
  }
  ```

## - Data Structures: Classes, Structs
- Use **PascalCase** for data structures.  
- Try to use phrases rather than single words if you are not using namespaces to avoid possible collisions.  
  Examples:
  ```cpp
  class UserProfile {
  public:
    UserProfile(std::string name) : name(name) {}
  private:
    std::string name;
  };
  ```
  ```
  ObjToDraw
  ShaderCompileData
  MyClass
  ```

## Sources and Links

|      |      |
| :--- | :--- |
| pep 8 – style guide for python code | https://peps.python.org/pep-0008/                                                                            |
| google styles guide                 | https://google.github.io/styleguide/                                                                         |
| nasa c style                        | http://cnl.sogang.ac.kr/cnlab/lectures/programming/c/nasa-c-style_1994.pdf                                   |
| gnu coding standards                | https://www.gnu.org/prep/standards/                                                                          |
| linux kernel                        | https://www.kernel.org/doc/html/v4.10/process/coding-style.html                                              |
| epic games                          | https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine |


Additionally, I recommend to use [clang-format tool](https://clang.llvm.org/docs/ClangFormat.html) for customizable, reproducable automated formatting for `cpp` code.
