//#ifndef LIGHT_YAML_PARSER_H
//#define LIGHT_YAML_PARSER_H
//
//#include <map>
//#include <sstream>
//#include <string>
//#include <variant>
//#include <vector>
//
//namespace light_yaml_parser
//{
//
//// Define the data structure to handle YAML values
//using YamlValue =
//    std::variant<std::string, std::vector<std::variant<std::string, YamlValue>>, std::map<std::string, YamlValue>>;
//using YamlMap = std::map<std::string, YamlValue>;
//
//class Parser
//{
//   public:
//    explicit Parser() : level_spaces(0), current_level(0) {}
//
//    YamlMap parse(const std::string& yaml_content)
//    {
//        std::istringstream                    stream(yaml_content);
//        std::string                           line;
//        YamlMap                               result;
//        std::vector<std::pair<int, YamlMap*>> context_stack;
//        YamlMap*                              current_map    = &result;
//        int                                   previous_level = 0;
//
//        while (std::getline(stream, line))
//        {
//            if (line.empty())
//            {
//                continue;  // Skip empty lines
//            }
//
//            size_t leading_spaces = countLeadingSpaces(line);
//            if (leading_spaces > 0 && level_spaces == 0)
//            {
//                level_spaces = leading_spaces;  // Set the indentation level on the first indented line
//            }
//
//            int line_level = leading_spaces / level_spaces;
//            line           = trim(line);
//
//            size_t colon_pos = line.find(':');
//            if (colon_pos == std::string::npos)
//            {
//                throw std::runtime_error("Invalid YAML syntax: Missing colon");
//            }
//
//            std::string key   = trim(line.substr(0, colon_pos));
//            std::string value = trim(line.substr(colon_pos + 1));
//
//            if (line_level > previous_level)
//            {
//                // Create a new nested map and add it as the value of the previous key
//                YamlMap nested_map;
//                (*current_map)[key] = YamlValue(nested_map);  // Explicitly assign a YamlValue
//                context_stack.emplace_back(previous_level, current_map);
//                current_map = &std::get<YamlMap>((*current_map)[key]);  // Safely access the nested map
//            }
//            else
//            {
//                // Adjust the context stack for the current level
//                while (!context_stack.empty() && context_stack.back().first >= line_level)
//                {
//                    current_map = context_stack.back().second;
//                    context_stack.pop_back();
//                }
//                (*current_map)[key] = value;
//            }
//
//            previous_level = line_level;
//        }
//
//        return result;
//    }
//
//   private:
//    int level_spaces;   // Stores the number of spaces used for indentation
//    int current_level;  // Tracks the current indentation level
//
//    size_t countLeadingSpaces(const std::string& line)
//    {
//        size_t count = 0;
//        for (char ch : line)
//        {
//            if (ch == ' ')
//            {
//                ++count;
//            }
//            else
//            {
//                break;
//            }
//        }
//        return count;
//    }
//
//    std::string trim(const std::string& str)
//    {
//        const char* whitespace = " \t\n\r";
//        size_t      start      = str.find_first_not_of(whitespace);
//        size_t      end        = str.find_last_not_of(whitespace);
//        return start == std::string::npos ? "" : str.substr(start, end - start + 1);
//    }
//};
//
//}  // namespace light_yaml_parser
//
//#endif  // LIGHT_YAML_PARSER_H
