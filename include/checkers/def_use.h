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

  void add_funcname(std::string funcname) {
    func_name = funcname;
  }

  std::string get_funcname() {
    return func_name;
  }

  void output_element() {
    std::cout << ln_col.first << " " << ln_col.second << "\n";
    std::cout << "Belong to Function: " << func_name << "\n";
  }
 

private:
  std::pair<int, int> ln_col;
  std::string func_name;

};

class def_use {
public:

  def_use() {
    ;
  }

  void add_Info(int def, int use, std::string funcname) {
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
        p.add_funcname(funcname);
        du.push_back(p);
      }
    }
    else {
      element p;
      p.add_funcname(funcname);
      p.add_lncol(def, use);
      du.push_back(p);
    }
  }

  void add_varname(std::string v) {
    var_name = v;
  }

  void add_type(std::string t) {
    type = t;
  }

  std::string get_type() {
    return type;
  }

  std::string get_vname() {
    return var_name;
  }

  void output_all() {
    std::cout << var_name << "  ";
    std::cout << type << "\n";
    for (int i = 0; i < du.size(); ++i) {
      du[i].output_element();
    }
  }

  std::vector<element> get_du() {
    return du;
  }

private:
  std::vector<element> du;
  //type of the variable
  std::string type;
  std::string var_name;
  
};

class defuse_node {
public:
  
  defuse_node() {
    ;
  }

  
  void add_var(int id, std::string var) {
    du_node[id] = def_use();
    du_node[id].add_varname(var);
  }

  void add_du(int id, int def, int use, std::string funcname) {
    du_node[id].add_Info(def, use, funcname);
  }

  void add_type(int id, std::string type) {
    du_node[id].add_type(type);
  }

  void output_node() {
    for (auto b = du_node.begin(); b != du_node.end(); ++b) {
      std::cout << (*b).first << "  ";
      (*b).second.output_all();
    }
  }

  def_use get_element(int id) {
    return du_node[id];
  }

  std::string get_type(int id) {
    return du_node[id].get_type();
  }

  std::string get_varname(int id) {
    return du_node[id].get_vname();
  }

  std::map<int, def_use> get_node() {
    return du_node;
  }

private:
  std::map<int, def_use> du_node;
};

#endif //DEF_USE_H