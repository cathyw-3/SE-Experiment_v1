#include "checkers/TemplateChecker.h"
#include "stack"
#include "algorithm"

struct Info {
  int def_line;
};

void TraverseDecl(Decl *anydecl, int count, SourceManager *scm);
void TraverseStmt(Stmt * anystmt, int count, SourceManager *scm);
defuse_node all_node;
bool definition = false;
bool integ = false;
bool callee = false;
std::map<int, std::map<std::string, int>> def_tmp;
std::map<std::string, int> global_def;
std::map<std::string, bool> decl_or_def;
int block_id = -1;
std::vector<int> reverse_path;
std::stack<CFGBlock *> stack_path;
std::string varname;



void TraverseDecl(Decl *anydecl, int count, SourceManager *scm) {
  if (anydecl != nullptr) {
    for (int i = 0; i < count; i++)
      printf(" ");
    VarDecl *vardecl;
    unsigned line = 0;
    unsigned kind = anydecl->getKind();
    switch (kind)
    {
    case 57: //vardecl
      vardecl = (VarDecl *)anydecl;
      line = vardecl->getASTContext().getSourceManager().getSpellingLineNumber(vardecl->getLocation());
      std::cout << vardecl->getID() << "\n";
      //std::cout << line << std::endl;
      std::cout << vardecl->getQualifiedNameAsString() << " "
        << vardecl->getType().getAsString() << std::endl;
      all_node.add_var(vardecl->getQualifiedNameAsString());
      //add
      if (block_id == -1) {
        global_def[vardecl->getQualifiedNameAsString()] = line;
      }
      else
        def_tmp[block_id][vardecl->getQualifiedNameAsString()] = line;
      decl_or_def[vardecl->getQualifiedNameAsString()] = false;
      //std::cout << count << std::endl;
      if (vardecl->ensureEvaluatedStmt() != nullptr) {
        ++count;
        if (vardecl->ensureEvaluatedStmt()->Value != nullptr) {
          if (strcmp(vardecl->ensureEvaluatedStmt()->Value->getStmtClassName(), "IntegerLiteral") == 0) {
            integ = true;
            varname = vardecl->getQualifiedNameAsString();
          }
        }
        else
        {
          integ = false;
        }
        TraverseStmt(vardecl->ensureEvaluatedStmt()->Value, count, scm);
      }
      break;
    
    default:
      break;
    }
  }
}


void TraverseStmt(Stmt * anystmt, int count, SourceManager *scm) {
  if (anystmt != nullptr) {
    CompoundStmt *cmpstmt;
    DeclStmt *dlstmt;
    ForStmt *forstmt;
    ReturnStmt *retstmt;
    CallExpr *callexpr;
    IntegerLiteral *intltr;
    CStyleCastExpr *cscastexpr;
    ImplicitCastExpr *imcastexpr;
    DeclRefExpr *dlrefexpr;
    StringLiteral *strltr;
    GNUNullExpr *gnu;
    BinaryOperator *bin;
    UnaryOperator *unary;
    ParenExpr *paren;
    SwitchStmt *swstmt;
    CaseStmt * casestmt;
    ConstantExpr *constmt;
    BreakStmt *brstmt;
    DefaultStmt *defau;
    IfStmt *ifstmt;
    CXXNullPtrLiteralExpr *nullptrltr;
    CXXConstructExpr *construct;
    MemberExpr *member;
    FloatingLiteral *floatltr;
    unsigned line;
    int pos;
    for (int k = 0; k < count; ++k)
      printf(" ");
    unsigned stmtclass = anystmt->getStmtClass();
    switch (stmtclass) {
      case 3: //breakstmt
        brstmt = (BreakStmt *)anystmt;
        std::cout << brstmt->getStmtClassName() << std::endl;
        break;
      case 8: //compoundstmt
        cmpstmt = (CompoundStmt *)anystmt;
        std::cout << cmpstmt->getStmtClassName() << std::endl;
        ++count;
        for (auto tmp = cmpstmt->body_begin(); tmp != cmpstmt->body_end(); ++tmp) {
          std::cout << (*tmp)->getBeginLoc().getPtrEncoding();
          TraverseStmt(*tmp, count, scm);
        }
        break;
      case 12: //declstmt
        ++count;
        dlstmt = (DeclStmt *)anystmt;
        std::cout << dlstmt->getStmtClassName() << ": " << std::endl;
        for (auto j = dlstmt->decl_begin(); j != dlstmt->decl_end(); ++j) {
          
          TraverseDecl(*j, count, scm);
        }
        break;
      case 14: //forstmt
        ++count;
        forstmt = (ForStmt *)anystmt;
        std::cout << forstmt->getStmtClassName() << ": " << std::endl;
        for (auto j = forstmt->child_begin(); j != forstmt->child_end(); ++j) {
          TraverseStmt(*j, count, scm);
        }
        break;
      case 16: //ifstmt
        ++count;
        ifstmt = (IfStmt *)anystmt;
        std::cout << ifstmt->getStmtClassName() << ": " << std::endl;
        for (auto i = ifstmt->child_begin(); i != ifstmt->child_end(); ++i)
          TraverseStmt(*i, count, scm);
        break;
      case 74: //returnstmt
        ++count;
        retstmt = (ReturnStmt *)anystmt;
        std::cout << retstmt->getStmtClassName() << ": " << std::endl;
        for (auto j = retstmt->child_begin(); j != retstmt->child_end(); ++j) {
          TraverseStmt(*j, count, scm);
        }
        break;
      case 79: //casestmt
        ++count;
        casestmt = (CaseStmt *)anystmt;
        std::cout << casestmt->getStmtClassName() << ": " << std::endl;
        for (auto i = casestmt->child_begin(); i != casestmt->child_end(); ++i) {
          TraverseStmt(*i, count, scm);
        }
        break;
      case 80: //defaultstmt
        ++count;
        defau = (DefaultStmt *)anystmt;
        std::cout << defau->getStmtClassName() << ": " << std::endl;
        for (auto i = defau->child_begin(); i != defau->child_end(); ++i)
          TraverseStmt(*i, count, scm);
        break;
      case 81: //switchstmt
        ++count;
        swstmt = (SwitchStmt *)anystmt;
        std::cout << swstmt->getStmtClassName() << ": " << std::endl;
        for (auto i = swstmt->child_begin(); i != swstmt->child_end(); ++i) {
          TraverseStmt(*i, count, scm);
        }
        break;
      case 92: //BinaryOperator
        ++count;
        bin = (BinaryOperator *)anystmt;
        std::cout << bin->getStmtClassName() << ": ";
        std::cout << bin->getType().getAsString() << "  " << bin->getOpcodeStr().str() << std::endl;
        for (auto i = bin->child_begin(); i != bin->child_end(); ++i) {
          if (strcmp((*i)->getStmtClassName(), "DeclRefExpr") == 0)
            definition = true;
          else 
            definition = false;
          TraverseStmt(*i, count, scm);
        }
        break;
      case 97: //CXXConstructExpr
        construct = (CXXConstructExpr *)anystmt;
        std::cout << construct->getStmtClassName() << ": ";
        std::cout << construct->getType().getAsString() << "  ";
        std::cout << construct->getConstructor()->getNumParams() << " ";
        for (unsigned i = 0; i < construct->getConstructor()->getNumParams(); ++i) {
          std::cout << construct->getConstructor()->getParamDecl(i)->getType().getAsString() << "," 
            << construct->getConstructor()->getParamDecl(i)->getNameAsString() << "  ";
        }
        std::cout << std::endl;
        break;
      case 107: //CXXNullptrLiteralExpr
        nullptrltr = (CXXNullPtrLiteralExpr *)anystmt;
        std::cout << nullptrltr->getStmtClassName() << ": ";
        std::cout << nullptrltr->getType().getAsString() << std::endl;
        break;
      case 116: //callExpr
        callee = true;
        ++count;
        callexpr = (CallExpr *)anystmt;
        std::cout << callexpr->getStmtClassName() << ": " << std::endl;
        for (auto i = callexpr->child_begin(); i != callexpr->child_end(); ++i) {
          TraverseStmt(*i, count, scm);
        }
        callee = false;
        break;
      case 122: //CStyleCastExpr
        ++count;
        cscastexpr = (CStyleCastExpr *)anystmt;
        std::cout << cscastexpr->getStmtClassName() << ": ";
        std::cout << cscastexpr->getType().getAsString() << std:: endl;
        if (*(cscastexpr->child_begin()) != nullptr) {
          for (auto i = cscastexpr->child_begin(); i != cscastexpr->child_end(); ++i) {
            TraverseStmt(*i, count, scm);
          }
        }
        break;
      case 129: //ImplicitCastExpr
        imcastexpr = (ImplicitCastExpr *)anystmt;
        std::cout << imcastexpr->getStmtClassName() << ": ";
        std::cout << imcastexpr->getType().getAsString() << std::endl;
        if (*(imcastexpr->child_begin()) != nullptr) {
          ++count;
          for (auto i = imcastexpr->child_begin(); i != imcastexpr->child_end(); ++i) {
            TraverseStmt(*i, count, scm);
          }
        }
        break;
      case 136: //DeclRefExpr
        dlrefexpr = (DeclRefExpr *)anystmt;
        std::cout << dlrefexpr->getStmtClassName() << ": ";
        std::cout << dlrefexpr->getType().getAsString() << "  ";
        std::cout << dlrefexpr->getDecl()->getDeclKindName() << "  ";
        std::cout << dlrefexpr->getDecl()->getNameAsString() << std::endl;
        std::cout << dlrefexpr->getDecl()->getID() << "\n";
        line = scm->getSpellingLineNumber(dlrefexpr->getLocation());
        //std::cout << line << std::endl;
        if (strcmp(dlrefexpr->getDecl()->getDeclKindName(), "Function") != 0) {
          if (definition == true) {
            //update or add def
            //def_tmp[block_id] = "var+info"
            def_tmp[block_id][dlrefexpr->getDecl()->getNameAsString()] = line;
            decl_or_def[dlrefexpr->getDecl()->getNameAsString()] = true;
            definition = false;
          }
          else {
            //use
            //def-reverse to last definition
            //all_node.add_du(var, def_tmp)
            for (int i = 0; i < reverse_path.size(); ++i) {
              if (reverse_path[i] == block_id) {
                pos = i;
                break;
              }
            }
            if (def_tmp[block_id].find(dlrefexpr->getDecl()->getNameAsString()) != def_tmp[block_id].end()) {
              all_node.add_du(dlrefexpr->getDecl()->getNameAsString(), def_tmp[block_id][dlrefexpr->getDecl()->getNameAsString()], line);
            }
            else {
              --pos;
              //std::cout << pos << std::endl;
              while (pos >= 0) {
                if (def_tmp[reverse_path[pos]].find(dlrefexpr->getDecl()->getNameAsString()) != def_tmp[reverse_path[pos]].end()) {
                  all_node.add_du(dlrefexpr->getDecl()->getNameAsString(), def_tmp[reverse_path[pos]][dlrefexpr->getDecl()->getNameAsString()], line);
                  break;
                }
                --pos;
              }
              //std::cout << pos << std::endl;
            }
            if (pos == -1) {
              all_node.add_du(dlrefexpr->getDecl()->getNameAsString(), global_def[dlrefexpr->getDecl()->getNameAsString()], line);
            }
          }
        }
        break;
      case 144: //floatingLiteral
        floatltr = (FloatingLiteral *)anystmt;
        std::cout << floatltr->getStmtClassName() << ": ";
        std::cout << floatltr->getType().getAsString() << "  " << floatltr->getValue().convertToDouble() << std::endl;
        break;
      case 145: //ConstantExpr
        constmt = (ConstantExpr *)anystmt;
        std::cout << constmt->getStmtClassName() << ": ";
        std::cout << constmt->getType().getAsString() << "  ";
        if (constmt->getAPValueResult().isInt() == true)
          std::cout << constmt->getAPValueResult().getInt().getSExtValue() << std::endl;
        ++count;
        for (auto i = constmt->child_begin(); i != constmt->child_end(); ++i) {
          TraverseStmt(*i, count, scm);
        }
        break;
      case 148: //GNUNullExpr
        gnu = (GNUNullExpr *)anystmt;
        std::cout << gnu->getStmtClassName() << ": ";
        std::cout << gnu->getType().getAsString() << std::endl;
        break;
      case 153: //IntegerLiteral
        intltr = (IntegerLiteral *)anystmt;
        std::cout << intltr->getStmtClassName() << ": ";
        std::cout << intltr->getType().getAsString() << "  ";
        std::cout << intltr->getValue().getSExtValue() << std::endl;
        if (integ == true) {
          //update or add def
          //std::cout << block_id << varname << std::endl;
          def_tmp[block_id][varname] = scm->getSpellingLineNumber(intltr->getLocation());
          decl_or_def[varname] = true;
          integ = false;
        }
        break;
      case 158: //MemberExpr
        ++count;
        member = (MemberExpr *)anystmt;
        std::cout << member->getStmtClassName() << ": ";
        std::cout << member->getType().getAsString() << "  " << member->getMemberNameInfo().getAsString() << std::endl;
        for (auto i = member->child_begin(); i != member->child_end(); ++i)
          TraverseStmt(*i, count, scm);
        break;
      case 181: //ParenExpr
        paren = (ParenExpr *)anystmt;
        std::cout << paren->getStmtClassName() << ": ";
        std::cout << paren->getType().getAsString() << "  ";
        switch (paren->getValueKind()) {
          case 0: std::cout << "rvalue" << std::endl; break;
          case 1: std::cout << "lvalue" << std::endl; break;
          case 2: std::cout << "xvalue" << std:: endl; break;
          default: break;
        }
        break;
      case 189: //StringLiteral
        strltr = (StringLiteral *)anystmt;
        std::cout << strltr->getStmtClassName() << ": ";
        std::cout << strltr->getType().getAsString() << "  ";
        std::cout << strltr->getString().str() << std::endl;
        break;
      case 195: //UnaryOperator
        ++count;
        unary = (UnaryOperator *)anystmt;
        std::cout << unary->getStmtClassName() << ": ";
        std::cout << unary->getType().getAsString() << "  " << unary->getOpcodeStr(unary->getOpcode()).str() << std::endl;
        for (auto i = unary->child_begin(); i != unary->child_end(); ++i) {
          TraverseStmt(*i, count, scm);
        }
        break;
      default: 
        std::cout << anystmt->getStmtClassName() << anystmt->getStmtClass() << std::endl;
        break;
    }
  }
}

void TemplateChecker::check() {
  // for example
  auto astr_iter = getASTRsBegin();

  
  auto vds = astr_iter->second.GetVarDecls();
  for (auto vd : vds) {
      printf("Global variable: ");
      std::cout << vd->getQualifiedNameAsString() << "  "
        << vd->getType().getAsString() << "  " << std::endl;
      TraverseDecl(vd, 0, &(vd->getASTContext().getSourceManager()));
  }
  
  while (astr_iter != getASTRsEnd()) {
    auto fds = astr_iter->second.GetFunctionDecls();

    for (auto fd : fds) {
      printf("FunctionDecl: ");
      //std::cout << common::getFullName(fd) << std::endl;
      auto fd_cfg = common::buildCFG(fd);
      
      std::cout << fd->getQualifiedNameAsString() << " "
        << fd->getType().getAsString() << std::endl;

      
      //parameter
      if (fd->getNumParams() > 0) {
        printf("  Parameters: \n");
        for (unsigned i = 0; i < fd->getNumParams(); i++) {
          std::cout << "  " << fd->getParamDecl(i)->getQualifiedNameAsString() << " ";
          std::cout << "  " << fd->getParamDecl(i)->getType().getAsString() << std::endl;
        }
      }
      
      //Compoundstmt
      //Stmt *cmpstmt = (fd->getBody());
      
      //TraverseStmt(cmpstmt);

      //printf("\n");

      // Traverse CFG
      LangOptions LangOpts;
      LangOpts.CPlusPlus = true;
      fd_cfg->dump(LangOpts, true);
      
      auto block = &(fd_cfg->getEntry());
      auto exit = &fd_cfg->getExit();
      //first
      CFGBlock *t;
      while(block->getBlockID() != exit->getBlockID()) {
        if (std::find(reverse_path.begin(), reverse_path.end(), block->getBlockID()) != reverse_path.end()) {
          //std::cout << "in.\n";
          for (auto i = block->succ_begin(); i != block->succ_end(); ++i) {
            t = i->getReachableBlock();
          }
          block = t;
          //std::cout << block->getBlockID() << "\n";
        }
        if (block->getBlockID() != exit->getBlockID()) {
          stack_path.push(block);
          block_id = block->getBlockID();
          reverse_path.push_back(block_id);
          for (auto I = block->begin(); I != block->end(); ++I) {
            if (Optional<CFGStmt> CS = (*I).getAs<CFGStmt>()) {
              Stmt *S = const_cast<Stmt *>(CS->getStmt());
              assert(S != nullptr && "Expecting non-null Stmt");
              //std::cout <<"1.\n"<<std::endl;
              TraverseStmt(S, 0, &fd->getASTContext().getSourceManager());
            }
          }
          block = block->succ_begin()->getReachableBlock();
        }
      }
      
      //std::cout << "out the first.\n";
      //next
      CFGBlock *current;
      CFGBlock *tmp;
      CFGBlock *next;
      while ((stack_path.empty() == false)) {
        //std::cout << stack_path.top()->succ_size() << "\n";
        if (stack_path.top()->succ_size() > 1) {
          tmp = stack_path.top();
          //find next successor of block tmp
          for (auto i = tmp->succ_begin(); i != tmp->succ_end(); ++i) {
            if (i->getReachableBlock()->getBlockID() == current->getBlockID()) {
              next = (++i)->getReachableBlock();
              break;
            }
          }
          //if (next->getBlockID() == exit->getBlockID())
            //break;
        }
        //the last child
        if ((stack_path.top()->succ_size() <= 1) || (next == tmp->succ_end()->getReachableBlock()) || (next->getBlockID() == exit->getBlockID())) {
          current = stack_path.top();
          stack_path.pop();
          reverse_path.pop_back();
        }
        else {
          while(next->getBlockID() != exit->getBlockID()) {
            //std::cout << reverse_path.size() << "\n";
            if (std::find(reverse_path.begin(), reverse_path.end(), next->getBlockID()) != reverse_path.end()) {
              for (auto i = next->succ_begin(); i != next->succ_end(); ++i) {
                t = i->getReachableBlock();
              }
              next = t;
              //std::cout << next->getBlockID() << "\n";
            }
            stack_path.push(next);
            block_id = next->getBlockID();
            reverse_path.push_back(block_id);
            for (auto I = next->begin(); I != next->end(); ++I) {
              if (Optional<CFGStmt> CS = (*I).getAs<CFGStmt>()) {
                Stmt *S = const_cast<Stmt *>(CS->getStmt());
                assert(S != nullptr && "Expecting non-null Stmt");
                //std::cout <<"1.\n"<<std::endl;
                TraverseStmt(S, 0, &fd->getASTContext().getSourceManager());
              }  
            }
            next = next->succ_begin()->getReachableBlock();
          }
        }
      }
      
      //std::cout << "out the whole while.\n";
    }
    
    ++astr_iter;
  }

  
  all_node.output_node();

  //analyze
  for (auto b = decl_or_def.begin(); b != decl_or_def.end(); ++b) {
    if((*b).second == false) {
      std::cout << "error: ";
      std::cout << "variable" << "'" << (*b).first << "'" << "uninitialized!\n";
      std::vector<element> d = all_node.get_node()[(*b).first].get_du();
      for (auto b_in = d.begin(); b_in != d.end(); ++b_in) {
        (*b_in).output_element();
      }
    }
  }
}
