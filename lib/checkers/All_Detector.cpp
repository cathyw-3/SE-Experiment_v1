#include "checkers/All_Detector.h"
#include "checkers/def_use.h"
//include your files

//这是一个全局变量，存储路径树
std::map<int, std::vector<CFGBlock *>> path_tree;

//这一部分提供检测，cout可以注释掉（只是输出检测用），第一层循环是按照路径分支序号；
//第二层循环按照每条路径的CFGBlock遍历，这个CFGBlock是完整的基本块信息，ly等需要的
//forstmt等可以通过CFGBlock中的Terminator获得，case等可以通过Label获得；第三层循环是
//每一个CFGBlock中顺序执行语句的stmt，大家可以使用自己的检测遍历来分析。
void Detector::detector() {
    for (auto idx = (path_tree.begin()); idx != path_tree.end(); ++idx) {
      //path index
      int path_idx = (*idx).first;
      std::cout << path_idx << "\n";
      for (auto cfg_bk = ++((*idx).second.begin()); cfg_bk != (*idx).second.end(); ++cfg_bk) {
          //cfg_block of the path
          CFGBlock *cur_bk = (*cfg_bk);
          std::cout << cur_bk->getBlockID() << "\n";
          for (auto stmt = cur_bk->begin(); stmt != cur_bk->end(); ++stmt) {
              if (Optional<CFGStmt> CS = (*stmt).getAs<CFGStmt>()) {
              Stmt *S = const_cast<Stmt *>(CS->getStmt());
              assert(S != nullptr && "Expecting non-null Stmt");
              std::cout << S->getStmtClassName() << "\n";
            }
              /*
              for every statement.
              add your detect here.
              */
          }
      }
    }
}