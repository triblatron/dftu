#include "dftu.hpp"

#include <antlr4-runtime.h>
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseListener.h"
#include "ParserRuleContext.h"

namespace dftu
{
    bool dimensionless(const Dimension & dim)
    {
        // True if all powers of the base dimensions are 0.
        bool result = true;

        for (int i = BASEDIM_ONE; result && i < BASEDIM_MAX; ++i)
        {
            if (dim.power[i] != 0)
            {
                result = false;
            }
        }
        return result;
    }

    bool base(const Dimension & dim)
    {
        // True if there is only one dimension with non-zero power and its power is one
        int sumOfPowers = 0;

        for (int i = BASEDIM_ONE; i < BASEDIM_MAX; ++i)
        {
            if (dim.power[i] != 1 && dim.power[i] != 0 )
            {
                return false;
            }
            sumOfPowers+=dim.power[i];
        }
        return sumOfPowers==1;
    }

    bool base(const Quantity & q)
    {
        int sumOfPowers = 0;

        for (int i = BASEUNIT_ONE; i < BASEUNIT_MAX; ++i)
        {
            if (q.unitSI->power[i] != 1 && q.unitSI->power[i] != 0)
            {
                return false;
            }
            sumOfPowers += q.unitSI->power[i];
        }

        return sumOfPowers==1;
    }

    bool dimensionless(const Unit & unit)
    {
        bool result = true;

        for (int i = BASEUNIT_ONE; result && i < BASEUNIT_MAX; ++i)
        {
            if (unit.power[i] != 0)
            {
                result = false;
            }
        }

        return result;
    }

    bool dimensionless(const Quantity & q)
    {
        return dimensionless(*q.unitSI);
    }

    //~ //! The name of the unit e.g. millemetre.
    //~ const char * name;
    //~ //! The ASCII symbol of the unit e.g. 'mm'.
    //~ const char * symbol;
    //~ //! The product of powers of base units.
    //~ //! This corresponds to powers of base dimensions.
    //~ int power[BASEUNIT_MAX];
    //~ //! A conversion factor to SI units.
    //~ //! 1.0 if this is an SI unit.
    //~ double factorSI;
    //~ //! The base 10 power of the unit.
    //~ //! This turns e.g. m into mm.
    //~ Scale scale;

    const UnitSystem SI=
    {
        1,
        {
            {
                "meter",
                "m",
                {
                    0,1,0,0,0,0,0
                },
                1.0,
                SCALE_ONE
            }
        }
    };

    class TreeShapeListener : public dftu::ExprBaseListener {
    public:
        TreeShapeListener(Reading * reading)
        :
        _reading(reading)
        {
            // Do nothing.
        }

        void enterExpr(dftu::ExprParser::ExprContext *ctx) override {
            // Do something when entering the key rule.
            _reading->value = atof(ctx->Floatingliteral()->getSymbol()->getText().c_str());

        }
    private:
        Reading * _reading;
    };

    ParseResult parse( const char * value, const UnitSystem * system, Reading * outputReading )
    {
        antlr4::ANTLRInputStream input(value);
        dftu::ExprLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);

        tokens.fill();
        for (auto token : tokens.getTokens()) {
            std::cout << token->toString() << std::endl;
        }

        dftu::ExprParser parser(&tokens);
        antlr4::tree::ParseTree* tree = parser.expr();
        antlr4::tree::ParseTreeWalker * walker = new antlr4::tree::ParseTreeWalker();
        TreeShapeListener listener(outputReading);
        walker->walk(&listener, tree);

        std::cout << tree->toStringTree(&parser) << std::endl << std::endl;
    }
}
