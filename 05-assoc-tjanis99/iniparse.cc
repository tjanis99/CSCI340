// Implement these functions to make the INI file parsing features work.
// See details in README.md.

// This will be compiled to iniparse.o and linked in when needed by make.

#include "settings.h"
#include "iniparse.h"

/**
 * @brief start with an empty INI_CONFIG, then read all available data 
 * from the input stream a line at a time. 
 * Each line is interpreted in the INI file format:
 * 
 * @param input an input stream to read from. The data read will be interpreted as a file in the INI format.
 * @param verbosity The verbosity level -- controls how much debug information will be shown
 * @return INI_CONFIG config built up from the input file. All of the detected keys should 
 * have values in the maps for their corresponding sections. No empty sections should be kept.
 */
INI_CONFIG read_ini(std::istream &input, int verbosity) {
    INI_CONFIG config;
    std::string current_section;
    std::string line;
    int line_number = 0;

    while (std::getline(input, line)) {
        line_number++;

        // Remove leading and trailing whitespace
        line = line.substr(line.find_first_not_of(" \t"));
        line = line.substr(0, line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            continue;  // Ignore empty lines
        }

        if (line[0] == ';') {
            if (verbosity >= 2) {
                std::cout << "Comment at line " << line_number << ": " << line << std::endl;
            }
            continue;  // Ignore comments
        }

        if (line[0] == '[') {
            size_t end_pos = line.find(']');
            if (end_pos != std::string::npos) {
                current_section = line.substr(1, end_pos - 1);
                add_ini_section(config, current_section);
                if (verbosity >= 1) {
                    std::cout << "Section: " << current_section << std::endl;
                }
            }
        } else {
            size_t equal_pos = line.find('=');
            if (equal_pos != std::string::npos) {
                std::string key = line.substr(0, equal_pos);
                std::string value = line.substr(equal_pos + 1);
                set_ini_key(config, current_section, key, value);
                if (verbosity >= 2) {
                    std::cout << "Key: " << key << " = " << value << " (line " << line_number << ")" << std::endl;
                }
            }
        }
    }

    return config;
}

/**
 * @brief output all of the keys found in config in such a way that the output could be used with read_ini to restore the same config
 * 
 * @param ost output stream to write the INI data to
 * @param config the INI_CONFIG we are writing to the output stream
 * @return true write successful
 * @return false write failed
 */
bool write_ini( std::ostream & ost, const INI_CONFIG & config ) {
  for (const auto &sectionPair : config) {
    ost << "[" << sectionPair.first << "]\n";
    for (const auto &keyValue : sectionPair.second) {
      ost << keyValue.first << " = " << keyValue.second << "\n";
    }
  }
  return true;
}

/**
 * @brief This function prints the configuration data from config with one key per line,
 * 
 * @param ost output stream to print to
 * @param config the INI_CONFIG whose info we would like to print
 */
void print_ini( std::ostream & ost, const INI_CONFIG & config ) {
  if (config.empty()) {
    ost << "Configuration is empty. Nothing to print" << std::endl;
    return;
  }

  for (const auto &sectionPair : config) {
    const std::string &sectionName = sectionPair.first;
    const std::map<std::string, std::string> &sectionData = sectionPair.second;

    if (sectionData.empty()) {
      ost << "Section \"" << sectionName << "\" is empty" << std::endl;
    } else {
      for (const auto &keyValue : sectionData) {
        const std::string &key = keyValue.first;
        const std::string &value = keyValue.second;

        // Print section name, key name, equal sign, and value
        ost << sectionName << "." << key << " = \"" << value << "\"" << std::endl;
      }
    }

    // Print a newline after each section
    ost << std::endl;
  }
}

/**
 * @brief add ini section
 * 
 * @param config The INI_CONFIG to add the section to.
 * @param section A string containing the name of the section to add.
 */
void add_ini_section(INI_CONFIG & config, const std::string &section) {
  if (config.find(section) == config.end())
  {
    config[section] = std::map<std::string, std::string>();
  }
}

/**
 * @brief remove ini section
 * 
 * @param config The INI_CONFIG to remove the section from.
 * @param section A string containing the name of the section to remove.
 */
void remove_ini_section(INI_CONFIG & config, const std::string &section) {
    config.erase(section);
}

/**
 * @brief Get the ini key object
 * 
 * @param config The INI_CONFIG to retrieve the key from.
 * @param section A string containing the name of the section containing the key desired.
 * @param key A string containing the name of the key whose value is desired.
 * @return std::string the given key exists in the given section, return its value, otherwise return an empty string.
 */
std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key) {
  auto sectionIterator = config.find(section);
  if (sectionIterator != config.end()) {
    auto keyIterator = sectionIterator->second.find(key);
    if (keyIterator != sectionIterator->second.end()) {
      return keyIterator->second;
    }
  }
  return "";  // Key or section not found
}

/**
 * @brief Set the ini key object
 * 
 * @param config The INI_CONFIG to set the key in.
 * @param section A string containing the name of the section containing the key desired.
 * @param key A string containing the name of the key whose value should be set.
 * @param value A string for the new value of the key.
 */
void set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value) {
  add_ini_section(config, section);
  config[section][key] = value;
}

/**
 * @brief Remove ini key object
 * 
 * @param config The INI_CONFIG to remove the key from.
 * @param section A string containing the name of the section containing the key.
 * @param key A string containing the name of the key to remove.
 * @return int number of keys actually removed.
 */
int remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key) {
  auto sectionIterator = config.find(section);
  if (sectionIterator != config.end()) {
    auto keyIterator = sectionIterator->second.find(key);
    if (keyIterator != sectionIterator->second.end()) {
      sectionIterator->second.erase(keyIterator);
      return 1;
    }
  }
  return 0;
}
