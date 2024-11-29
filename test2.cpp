#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

//design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode {
  private:
    std::string data;
    std::vector<SuffixTreeNode *> *suffix;

  public:

    SuffixTreeNode ( std::string d ) : data(d) {
      suffix = new std::vector<SuffixTreeNode *>;
    }
    SuffixTreeNode () : data("") {
      suffix = new std::vector<SuffixTreeNode *>;
    }

    std::string const getString () {
      return data;
    }

    void setString ( const std::string d ) {
      data = d;
    }

    std::vector<SuffixTreeNode *> *getSuffix () {
      return suffix;
    }


};

class SuffixTree {

  private:

      SuffixTreeNode *root;
      std::string text;

      void findRightPlace ( SuffixTreeNode *nowplace , std::string searchword ) {

        if ( nowplace == root && searchword == "$" ) {
          SuffixTreeNode * newOne = new SuffixTreeNode(searchword);
          nowplace->getSuffix()->push_back( newOne );
          return;
        }

        if ( searchword == "" ) return;

        for ( int i = 0 ; i < nowplace->getSuffix()->size() ; i++ ) {

            std::string pre = comparePrefix( searchword, (*nowplace->getSuffix())[i]->getString() );
            SuffixTreeNode *temp = (*nowplace->getSuffix())[i];
            
            if ( pre == "" ) {
              continue;
            }
            else {

              if ( temp->getSuffix()->empty() ) {

                std::string reg = temp->getString();
                temp->setString(pre);
                reg = reg.substr( pre.length() , reg.length() - pre.length() );
                SuffixTreeNode * cutstring = new SuffixTreeNode(reg);
                temp->getSuffix()->push_back( cutstring );
                
              }

              searchword = searchword.substr( pre.length() , searchword.length() - pre.length() );

              findRightPlace( (*nowplace->getSuffix())[i], searchword );

              return;
              
            }

        }
        SuffixTreeNode * newOne = new SuffixTreeNode(searchword);
        nowplace->getSuffix()->push_back( newOne );
          
      }

      std::string comparePrefix ( std::string a , std::string b ) {

        int smallLength = ( a.length() > b.length() )? b.length() : a.length();
        std::string MaxPrefix = "";
        for ( int i = 1 ; i <= smallLength ; i++ ) {
          if ( a.substr(0,i) == b.substr(0,i) ) {
            MaxPrefix = a.substr(0,i);
            continue;
          }
          else {
            return MaxPrefix;
          }

        }
        if ( !MaxPrefix.empty() ) {
          return  MaxPrefix;
        }
        else return "";
        
      }

      

  public:

      SuffixTree(const std::string &text) : text(text) {
        root = new SuffixTreeNode();
        builSuffixTree();
      }

      void builSuffixTree () {
        if ( text == "" ) return;
        else { 
          text += "$";
        }

        std::vector<std::string> word;
        std::string temp = text;

        while ( temp != "" ) {

          word.push_back(temp);
          temp.erase(0,1);

        }

        if ( root->getSuffix()->empty() && !word.empty() ) {
          SuffixTreeNode *temp = new  SuffixTreeNode(word[0]);
          root->getSuffix()->push_back( temp );
        }

        int count = 1;
        while ( count != word.size() ) {
          
          findRightPlace(root , word[count]);
          count++;
        
        }

      }

      void print () {
        for ( int i = 0 ; i < root->getSuffix()->size() ; i++ ) {
          std::cout << (*root->getSuffix())[i]->getString() << std::endl;
        }
      }

      int countHelper(SuffixTreeNode *node, const std::string &substring) {
    if (substring.empty()) {
        return countLeaves(node);
    }

    for (SuffixTreeNode *child : *(node->getSuffix())) {
        std::string nodeString = child->getString();
        if (substring.find(nodeString) == 0) { // 如果節點的字串是子字串的前綴
            return countHelper(child, substring.substr(nodeString.length()));
        }
    }
    return 0;
}

int countLeaves(SuffixTreeNode *node) {
    if (node->getSuffix()->empty()) return 1;

    int total = 0;
    for (SuffixTreeNode *child : *(node->getSuffix())) {
        total += countLeaves(child);
    }
    return total;
}

      bool exist(const std::string &substring) {
        return existHelper(root, substring);
      }

      int count(const std::string &substring) {
         return countHelper(root, substring);
      }


bool existHelper(SuffixTreeNode *node, const std::string &substring) {
    if (substring.empty()) return true;

    for (SuffixTreeNode *child : *(node->getSuffix())) {
        std::string nodeString = child->getString();
        if (substring.find(nodeString) == 0) { // 如果節點的字串是子字串的前綴
            return existHelper(child, substring.substr(nodeString.length()));
        }
    }
    return false;
}

      ~SuffixTree() {
        delete root;
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
