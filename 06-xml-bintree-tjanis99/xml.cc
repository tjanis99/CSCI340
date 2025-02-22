//***************************************************************************
//
//  Trevor Janis
//  Z1839641
//  CSCI 340-1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************
// Implement a simple parser for XML that uses a tilted binary tree for storage
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

#include "nodes.h" // Supplied node declarations
#include "bintree.h"
#include "xml.h"

/**
 * @brief Function to convert an xml_element into its string representation.
 * 
 * @param element to be converted to string
 * @param opening if opened
 * @return std::string element processed
 */
std::string to_string(const xml_element &element, bool opening) {
    if (element.type == xml_type::tag) {
        if (opening) {
            // Generate the opening tag
            std::string result = "<" + element.name;
            for (const auto &attr : element.attrs) {
                result += " " + attr.first + "=\"" + attr.second + "\"";
            }
            result += ">";
            return result;
        } else {
            // Generate the closing tag
            return "</" + element.name + ">";
        }
    } else {
        // Handle plain text elements
        return element.fulltext;
    }
}

/**
 * @brief Function to find all nodes with a given name in the XML tree.
 * 
 * @param root to be processed
 * @param name node names
 * @return std::vector<XMLNODE*> vector of results
 */
std::vector<XMLNODE*> xml_find_by_name(XMLNODE* root, const std::string& name) {
    std::vector<XMLNODE*> result;

    if (root) {
        // Check if the current node matches the name
        if (root->data.type == xml_type::tag && root->data.name == name) {
            result.push_back(root);
        }

        // Recursively search in the left subtree
        std::vector<XMLNODE*> left_result = xml_find_by_name(root->left, name);
        result.insert(result.end(), left_result.begin(), left_result.end());

        // Recursively search in the right subtree
        std::vector<XMLNODE*> right_result = xml_find_by_name(root->right, name);
        result.insert(result.end(), right_result.begin(), right_result.end());
    }

    return result;
}

/**
 * @brief Function to find nodes with a specific attribute in the XML tree.
 * 
 * @param root root processed
 * @param attrname attribute to be found
 * @return std::vector<XMLNODE*> vector of results
 */
std::vector<XMLNODE*> xml_find_with_attr(XMLNODE* root, const std::string& attrname) {
    std::vector<XMLNODE*> result;

    if (root) {
        // Check if the current node has the specified attribute
        if (root->data.type == xml_type::tag) {
            auto attrIter = root->data.attrs.find(attrname);
            if (attrIter != root->data.attrs.end()) {
                result.push_back(root);
            }
        }

        // Recursively search in the left subtree
        std::vector<XMLNODE*> left_result = xml_find_with_attr(root->left, attrname);
        result.insert(result.end(), left_result.begin(), left_result.end());

        // Recursively search in the right subtree
        std::vector<XMLNODE*> right_result = xml_find_with_attr(root->right, attrname);
        result.insert(result.end(), right_result.begin(), right_result.end());
    }

    return result;
}

/**
 * @brief Function to add a new node to the XML tree.
 * 
 * @param element to be added
 * @param state tree state
 * @param verbose info providede
 * @return int processed
 */
int xml_add_node(const xml_element &element, xml_tree_state &state, bool verbose) {
    if (!state.root) {
        // If the tree is empty, set the new node as the root
        state.root = new XMLNODE(element);
        state.cur = state.root;
    } else {
        if (!state.cur) {
            if (verbose) {
                // If the current node is nullptr, log an error
                std::cerr << "Error: Current node is nullptr." << std::endl;
            }
            return 1;
        }

        // Create a new node and attach it as a sibling or child
        XMLNODE* new_node = new XMLNODE(element);
        if (state.cur->data.type == xml_type::plain || state.cur->data.closed) {
            // Insert as a sibling
            new_node->left = state.cur;
            state.cur->parent = new_node;
            state.cur = new_node;
        } else {
            // Insert as a child
            new_node->parent = state.cur;
            state.cur->right = new_node;
            state.cur = new_node;
        }
    }

    return 0;
}

/**
 * @brief Function to close an XML tag in the tree.
 * 
 * @param name nametag
 * @param state tree state
 * @param verbose info provided
 * @return int procssed
 */
int xml_close_tag(const std::string name, xml_tree_state &state, bool verbose) {
    if (!state.root) {
        // If the tree is empty, log an error
        if (verbose) {
            std::cerr << "Error: Attempting to close a tag in an empty tree." << std::endl;
        }
        return 1;
    }

    XMLNODE* current = state.cur;
    while (current && (current->data.type != xml_type::tag || current->data.name != name)) {
        // Find the nearest matching open tag by moving up the tree
        current = tilted_find_parent(current);
    }

    if (!current) {
        // If no matching open tag is found, log an error
        if (verbose) {
            std::cerr << "Error: Tag with name '" << name << "' not found." << std::endl;
        }
        return 1;
    }

    // Mark the tag as closed
    current->data.closed = true;
    state.cur = current;
    return 0;
}

/**
 * @brief Function to handle plain text content and add it as a node.
 * 
 * @param plaintext text to proccess in node
 * @param state state of tree
 * @param verbose information provided
 * @return int number proccessed
 */
int xml_handle_plaintext(std::string &plaintext, xml_tree_state &state, bool verbose) {
    xml_element element(xml_type::plain, "", plaintext, {});
    return xml_add_node(element, state);
}

/**
 * @brief Function to handle attributes in an XML tag and store them in a map.
 * 
 * @param input xml tag
 * @param attrs attributes
 * @param verbose verbrosity data provided
 * @return int 
 */
int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    size_t i = 0;
    int count = 0;
    while (i < input.size()) {
        // Find the attribute name
        size_t start = input.find_first_not_of(" \t\n\r", i);
        if (start == std::string::npos) {
            break;
        }

        size_t end = input.find("=", start);
        if (end == std::string::npos) {
            // Invalid input, missing '='
            std::cerr << "  ERROR: xml_handle_attributes done. Invalid string remaining \"" << input << "\"\n";
            return 0;
        }

        std::string attr_name = input.substr(start, end - start);

        // Find the attribute value
        start = input.find_first_of("\"'", end);
        if (start == std::string::npos) {
            // Invalid input, missing attribute value delimiter
            return 0;
        }

        char attr_value_delimiter = input[start];
        end = input.find(attr_value_delimiter, start + 1);
        if (end == std::string::npos) {
            // Invalid input, missing closing attribute value delimiter
            std::cerr << "  ERROR: xml_handle_attributes tag ended before value's quotation ended.\n";
            return 0;
        }

        std::string attr_value = input.substr(start + 1, end - start - 1);

        // Store the attribute in the map
        attrs[attr_name] = attr_value;
        i = end + 1;
        count++;
    }

    return count;
}

/**
 * @brief Function to handle an XML tag, extract tag attributes, and update the tree.
 * 
 * @param tagstring XML tag
 * @param state tree state
 * @param verbose data
 * @return int errors
 */
int xml_handle_tag(std::string &tagstring, xml_tree_state &state, bool verbose) {
    if (tagstring.empty() || tagstring.size() < 3 || tagstring[0] != '<' || tagstring[tagstring.size() - 1] != '>') {
        // Check if the tag is well-formed
        if (verbose) {
            std::cerr << "Error: Invalid tag: " << tagstring << std::endl;
        }
        return 1;
    }

    std::string tag_content = tagstring.substr(1, tagstring.size() - 2);
    std::string tag_name;
    xml_type type = xml_type::tag;
    bool closing_tag = false;
    std::map<std::string, std::string> attrs;

    if (tag_content[0] == '/') {
        // If it's a closing tag
        closing_tag = true;
        tag_name = tag_content.substr(1);
    } else {
        size_t space_pos = tag_content.find_first_of(" \t\n\r");
        if (space_pos != std::string::npos) {
            // Extract tag name and handle attributes
            tag_name = tag_content.substr(0, space_pos);
            xml_handle_attributes(tag_content.substr(space_pos), attrs);
        } else {
            tag_name = tag_content;
        }
    }

    // Create an XML element from the tag information
    xml_element element(type, tag_name, tagstring, attrs);

    if (closing_tag) {
        // If it's a closing tag, close the corresponding open tag.
        return xml_close_tag(tag_name, state);
    } else {
        // If it's an opening tag, add it to the tree.
        return xml_add_node(element, state, verbose);
    }
}

/**
 * @brief Function to recursively print the XML tree to an output stream.
 * 
 * @param root to begin from
 * @param ost output stream
 */
void xml_print_subtree(XMLNODE *root, std::ostream & ost) {
    if (root) {
        const xml_element &element = root->data;

        // Print the element based on its type
        ost << to_string(element, true);

        // Get the children nodes
        std::vector<XMLNODE *> children = tilted_get_children(root);

        // Recursively print the children nodes
        for (XMLNODE *child : children) {
            xml_print_subtree(child, ost);
        }

        // Print the closing tag if it's an opening tag
        if (element.type == xml_type::tag && !element.closed) {
            ost << to_string(element, false);
        }
    }
}
