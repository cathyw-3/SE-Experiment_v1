#include "checkers/TemplateChecker.h"

void TraverseDecl(Decl *anydecl);
void TraverseStmt(Stmt * anystmt);

void TraverseDecl(Decl *anydecl) {
  if (anydecl != nullptr) {
    VarDecl *vardecl;
    unsigned kind = anydecl->getKind();
    switch (kind)
    {
    case 57: //vardecl
      vardecl = (VarDecl *)anydecl;
      std::cout << vardecl->getQualifiedNameAsString() << " "
        << vardecl->getType().getAsString() << std::endl;
      if (vardecl->ensureEvaluatedStmt() != nullptr)
        TraverseStmt(vardecl->ensureEvaluatedStmt()->Value);
      break;
    
    default:
      break;
    }
  }
}


void TraverseStmt(Stmt * anystmt) {
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
    unsigned stmtclass = anystmt->getStmtClass();
    switch (stmtclass) {
      case 3: //breakstmt
        brstmt = (BreakStmt *)anystmt;
        std::cout << brstmt->getStmtClassName() << std::endl;
        break;
      case 8: //compoundstmt
        cmpstmt = (CompoundStmt *)anystmt;
        std::cout << cmpstmt->getStmtClassName() << std::endl;
        for (auto tmp = cmpstmt->body_begin(); tmp != cmpstmt->body_end(); ++tmp) {
          TraverseStmt(*tmp);
        }
        break;
      case 12: //declstmt
        dlstmt = (DeclStmt *)anystmt;
        std::cout << dlstmt->getStmtClassName() << ": " << std::endl;
        for (auto j = dlstmt->decl_begin(); j != dlstmt->decl_end(); ++j)
          TraverseDecl(*j);
        break;
      case 14: //forstmt
        forstmt = (ForStmt *)anystmt;
        std::cout << forstmt->getStmtClassName() << ": " << std::endl;
        for (auto j = forstmt->child_begin(); j != forstmt->child_end(); ++j) {
          TraverseStmt(*j);
        }
        break;
      case 16: //ifstmt
        ifstmt = (IfStmt *)anystmt;
        std::cout << ifstmt->getStmtClassName() << ": " << std::endl;
        for (auto i = ifstmt->child_begin(); i != ifstmt->child_end(); ++i)
          TraverseStmt(*i);
        break;
      case 74: //returnstmt
        retstmt = (ReturnStmt *)anystmt;
        std::cout << retstmt->getStmtClassName() << ": " << std::endl;
        for (auto j = retstmt->child_begin(); j != retstmt->child_end(); ++j) {
          TraverseStmt(*j);
        }
        break;
      case 79: //casestmt
        casestmt = (CaseStmt *)anystmt;
        std::cout << casestmt->getStmtClassName() << ": " << std::endl;
        for (auto i = casestmt->child_begin(); i != casestmt->child_end(); ++i) {
          TraverseStmt(*i);
        }
        break;
      case 80: //defaultstmt
        defau = (DefaultStmt *)anystmt;
        std::cout << defau->getStmtClassName() << ": " << std::endl;
        for (auto i = defau->child_begin(); i != defau->child_end(); ++i)
          TraverseStmt(*i);
        break;
      case 81: //switchstmt
        swstmt = (SwitchStmt *)anystmt;
        std::cout << swstmt->getStmtClassName() << ": " << std::endl;
        for (auto i = swstmt->child_begin(); i != swstmt->child_end(); ++i) {
          TraverseStmt(*i);
        }
        break;
      case 92: //BinaryOperator
        bin = (BinaryOperator *)anystmt;
        std::cout << bin->getStmtClassName() << ": ";
        std::cout << bin->getType().getAsString() << "  " << bin->getOpcodeStr().str() << std::endl;
        for (auto i = bin->child_begin(); i != bin->child_end(); ++i) {
          TraverseStmt(*i);
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
        callexpr = (CallExpr *)anystmt;
        std::cout << callexpr->getStmtClassName() << ": " << std::endl;
        for (auto i = callexpr->child_begin(); i != callexpr->child_end(); ++i) {
          TraverseStmt(*i);
        }
        break;
      case 122: //CStyleCastExpr
        cscastexpr = (CStyleCastExpr *)anystmt;
        std::cout << cscastexpr->getStmtClassName() << ": ";
        std::cout << cscastexpr->getType().getAsString() << std:: endl;
        if (*(cscastexpr->child_begin()) != nullptr) {
          for (auto i = cscastexpr->child_begin(); i != cscastexpr->child_end(); ++i) {
            TraverseStmt(*i);
          }
        }
        break;
      case 129: //ImplicitCastExpr
        imcastexpr = (ImplicitCastExpr *)anystmt;
        std::cout << imcastexpr->getStmtClassName() << ": ";
        std::cout << imcastexpr->getType().getAsString() << std::endl;
        if (*(imcastexpr->child_begin()) != nullptr) {
          for (auto i = imcastexpr->child_begin(); i != imcastexpr->child_end(); ++i) {
            TraverseStmt(*i);
          }
        }
        break;
      case 136: //DeclRefExpr
        dlrefexpr = (DeclRefExpr *)anystmt;
        std::cout << dlrefexpr->getStmtClassName() << ": ";
        std::cout << dlrefexpr->getType().getAsString() << "  ";
        std::cout << dlrefexpr->getDecl()->getDeclKindName() << "  ";
        std::cout << dlrefexpr->getDecl()->getNameAsString() << std::endl;
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
        for (auto i = constmt->child_begin(); i != constmt->child_end(); ++i) {
          TraverseStmt(*i);
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
        break;
      case 158: //MemberExpr
        member = (MemberExpr *)anystmt;
        std::cout << member->getStmtClassName() << ": ";
        std::cout << member->getType().getAsString() << "  " << member->getMemberNameInfo().getAsString() << std::endl;
        for (auto i = member->child_begin(); i != member->child_end(); ++i)
          TraverseStmt(*i);
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
        unary = (UnaryOperator *)anystmt;
        std::cout << unary->getStmtClassName() << ": ";
        std::cout << unary->getType().getAsString() << "  " << unary->getOpcodeStr(unary->getOpcode()).str() << std::endl;
        for (auto i = unary->child_begin(); i != unary->child_end(); ++i) {
          TraverseStmt(*i);
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
      TraverseDecl(vd);
  }
  
  while (astr_iter != getASTRsEnd()) {
    auto fds = astr_iter->second.GetFunctionDecls();

    for (auto fd : fds) {
      printf("FunctionDecl: ");
      //std::cout << common::getFullName(fd) << std::endl;
      auto fd_cfg = common::buildCFG(fd);
      // Traverse CFG
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
      Stmt *cmpstmt = (fd->getBody());
      
      TraverseStmt(cmpstmt);

      printf("\n");
    }
    ++astr_iter;
  }
}
