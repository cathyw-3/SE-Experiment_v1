#ifndef DEF_USE_H
#define DEF_USE_H

#include <string>
#include <string.h>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <utility>

class element {
public:
  
  element() {
    ;
  }

  void add_lncol(int def, int use) {
    std::pair<int, int> pr(def, use);
    ln_col = pr;
  }

  std::pair<int, int> get_lncol() {
    return ln_col;
  }

  void output_element() {
    std::cout << ln_col.first << " " << ln_col.second << "\n";
  }
 

private:
  std::pair<int, int> ln_col;

};

class def_use {
public:

  def_use() {
      ;
  }

  void add_lncol(int def, int use) {
    std::pair<int, int> pr(def, use);
    if (du.size() > 0) {
      auto i = du.begin();
      for (; i != du.end(); ++i) {
        if (pr == (*i).get_lncol()) {
          break;
        }
      }
      if (pr != (*i).get_lncol()) {
        element p;
        p.add_lncol(def, use);
        du.push_back(p);
      }
    }
    else {
      element p;
      p.add_lncol(def, use);
      du.push_back(p);
    }
  }

  void output_all() {
    for (int i = 0; i < du.size(); ++i) {
      du[i].output_element();
    }
  }

  std::vector<element> get_du() {
    return du;
  }

private:
  std::vector<element> du;
  
};

class defuse_node {
public:
  
  defuse_node() {
      ;
  }

  void add_var(std::string var) {
    du_node[var] = def_use();
  }

  void add_du(std::string var, int def, int use) {
    du_node[var].add_lncol(def, use);
  }

  void output_node() {
    for (auto b = du_node.begin(); b != du_node.end(); ++b) {
      std::cout << (*b).first << "  ";
      (*b).second.output_all();
    }
  }

  std::map<std::string, def_use> get_node() {
    return du_node;
  }

private:
  std::map<std::string, def_use> du_node;
};

#endif //DEF_USE_H