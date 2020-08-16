#include <iostream>
#include <antlr4-runtime.h>
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseListener.h"
#include "ParserRuleContext.h"

#include <fstream>

class TreeShapeListener : public dftu::ExprBaseListener {
public:
    void enterExpr(dftu::ExprParser::ExprContext *ctx) override {
        // Do something when entering the key rule.
        std::cout << "Float: " << atof(ctx->Floatingliteral()->getSymbol()->getText().c_str()) << std::endl;
    }
};

int main(int argc, char * argv[]) {
    if ( argc != 2 )
    {
        std::cerr << "Usage: " << argv[0] << " <input>\n";

        return -1;
    }
    antlr4::ANTLRInputStream input(argv[1]);
    dftu::ExprLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    dftu::ExprParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.expr();
    antlr4::tree::ParseTreeWalker * walker = new antlr4::tree::ParseTreeWalker();
    TreeShapeListener listener;
    walker->walk(&listener, tree);

    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    return 0;
}

