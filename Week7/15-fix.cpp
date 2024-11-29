#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

//design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode {
    private:
        string data;
        unordered_map<string , SuffixTreeNode*> *suffix;
    public:
        SuffixTreeNode ( std::string d ) : data(d) {
            suffix = new unordered_map<string , SuffixTreeNode*>();
        }
        SuffixTreeNode () : data("") {
            suffix = new unordered_map<string , SuffixTreeNode*>();
        }

        std::string const getString () {
            return data;
        }

        void setString ( const std::string d ) {
            data = d;
        }

        unordered_map<string , SuffixTreeNode*> *getSuffix () {
            return suffix;
        }
};

class SuffixTree {
    private:

        SuffixTreeNode *root;
        std::string text;

        void buildSuffixTree() {
        if (text.empty()) {
            return;
        }

        // Build tree for all possible suffixes
        for (size_t i = 0; i < text.length(); i++) {
            string suffix = text.substr(i);
            insertSuffix(suffix);
        }
        }

        void insertSuffix(const string &suffix) {
            SuffixTreeNode *current = root;
            string remainingSuffix = suffix;
            
            while (!remainingSuffix.empty()) {
                string currentChar = remainingSuffix.substr(0, 1);
                auto suffixMap = current->getSuffix();
                
                // If character path doesn't exist, create new node
                if (suffixMap->find(currentChar) == suffixMap->end()) {
                    (*suffixMap)[currentChar] = new SuffixTreeNode(remainingSuffix);
                    break;
                }
                
                // Move to next node
                current = (*suffixMap)[currentChar];
                remainingSuffix = remainingSuffix.substr(1);
            }
        }

    public:
        SuffixTree(const std::string &text) : text(text) {
            root = new SuffixTreeNode();
            buildSuffixTree();
        }

        bool exist(const string &substring) {
            if (substring.empty()) return true;
            
            SuffixTreeNode *current = root;
            string remaining = substring;
            
            while (!remaining.empty()) {
                string currentChar = remaining.substr(0, 1);
                auto suffixMap = current->getSuffix();
                
                if (suffixMap->find(currentChar) == suffixMap->end()) {
                    return false;
                }
                
                current = (*suffixMap)[currentChar];
                remaining = remaining.substr(1);
            }
            return true;
        }

        int count(const string &substring) {
            if (substring.empty()) return text.length();
            
            int count = 0;
            for (size_t i = 0; i < text.length(); i++) {
                if (text.substr(i).find(substring) == 0) {
                    count++;
                }
            }
            return count;
        }

        ~SuffixTree() {
        }
};

int main() {
    std::string text = "";
    while(true) {
      std::string temp;
      getline(std::cin, temp);
      if(temp == "")
        break;
      text += temp;
    }
    SuffixTree tree(text);

    std::string query;
    while(true) {
      getline(std::cin, query);
      if(query == "")
        break;
      std::cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
      std::cout << "Count of '" << query << "': " << tree.count(query) << std::endl;
    }
    return 0;
}