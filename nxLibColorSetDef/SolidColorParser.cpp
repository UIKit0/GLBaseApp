/** \file
 *  This C source file was generated by $ANTLR version 3.3 Nov 30, 2010 12:45:30
 *
 *     -  From the grammar source file : SolidColor.g
 *     -                            On : 2011-09-23 20:02:22
 *     -                for the parser : SolidColorParserParser *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
*/
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/* -----------------------------------------
 * Include the ANTLR3 generated header file.
 */
#include    "SolidColorParser.h"
/* ----------------------------------------- */





/* MACROS that hide the C interface implementations from the
 * generated code, which makes it a little more understandable to the human eye.
 * I am very much against using C pre-processor macros for function calls and bits
 * of code as you cannot see what is happening when single stepping in debuggers
 * and so on. The exception (in my book at least) is for generated code, where you are
 * not maintaining it, but may wish to read and understand it. If you single step it, you know that input()
 * hides some indirect calls, but is always referring to the input stream. This is
 * probably more readable than ctx->input->istream->input(snarfle0->blarg) and allows me to rejig
 * the runtime interfaces without changing the generated code too often, without
 * confusing the reader of the generated output, who may not wish to know the gory
 * details of the interface inheritance.
 */

#define     CTX ctx

/* Aids in accessing scopes for grammar programmers
 */
#undef  SCOPE_TYPE
#undef  SCOPE_STACK
#undef  SCOPE_TOP
#define SCOPE_TYPE(scope)   pSolidColorParser_##scope##_SCOPE
#define SCOPE_STACK(scope)  pSolidColorParser_##scope##Stack
#define SCOPE_TOP(scope)    ctx->pSolidColorParser_##scope##Top
#define SCOPE_SIZE(scope)       ctx->pSolidColorParser_##scope##Stack_limit
#define SCOPE_INSTANCE(scope, i)    (ctx->SCOPE_STACK(scope)->get(ctx->SCOPE_STACK(scope),i))

/* Macros for accessing things in the parser
 */

#undef      PARSER
#undef      RECOGNIZER
#undef      HAVEPARSEDRULE
#undef      MEMOIZE
#undef      INPUT
#undef      STRSTREAM
#undef      HASEXCEPTION
#undef      EXCEPTION
#undef      MATCHT
#undef      MATCHANYT
#undef      FOLLOWSTACK
#undef      FOLLOWPUSH
#undef      FOLLOWPOP
#undef      PRECOVER
#undef      PREPORTERROR
#undef      LA
#undef      LT
#undef      CONSTRUCTEX
#undef      CONSUME
#undef      MARK
#undef      REWIND
#undef      REWINDLAST
#undef      PERRORRECOVERY
#undef      HASFAILED
#undef      FAILEDFLAG
#undef      RECOVERFROMMISMATCHEDSET
#undef      RECOVERFROMMISMATCHEDELEMENT
#undef      INDEX
#undef      ADAPTOR
#undef      SEEK
#undef      RULEMEMO
#undef      DBG

#define     PARSER              ctx->pParser
#define     RECOGNIZER              PARSER->rec
#define     PSRSTATE                RECOGNIZER->state
#define     HAVEPARSEDRULE(r)           RECOGNIZER->alreadyParsedRule(RECOGNIZER, r)
#define     MEMOIZE(ri,si)          RECOGNIZER->memoize(RECOGNIZER, ri, si)
#define     INPUT               PARSER->tstream
#define     STRSTREAM               INPUT
#define     ISTREAM             INPUT->istream
#define     INDEX()             ISTREAM->index(INPUT->istream)
#define     HASEXCEPTION()          (PSRSTATE->error == ANTLR3_TRUE)
#define     EXCEPTION               PSRSTATE->exception
#define     MATCHT(t, fs)           RECOGNIZER->match(RECOGNIZER, t, fs)
#define     MATCHANYT()             RECOGNIZER->matchAny(RECOGNIZER)
#define     FOLLOWSTACK             PSRSTATE->following
#ifdef  SKIP_FOLLOW_SETS
#define     FOLLOWPUSH(x)
#define     FOLLOWPOP()
#else
#define     FOLLOWPUSH(x)           FOLLOWSTACK->push(FOLLOWSTACK, ((void *)(&(x))), NULL)
#define     FOLLOWPOP()             FOLLOWSTACK->pop(FOLLOWSTACK)
#endif
#define     PRECOVER()              RECOGNIZER->recover(RECOGNIZER)
#define     PREPORTERROR()          RECOGNIZER->reportError(RECOGNIZER)
#define     LA(n)               INPUT->istream->_LA(ISTREAM, n)
#define     LT(n)               INPUT->_LT(INPUT, n)
#define     CONSTRUCTEX()           RECOGNIZER->exConstruct(RECOGNIZER)
#define     CONSUME()               ISTREAM->consume(ISTREAM)
#define     MARK()              ISTREAM->mark(ISTREAM)
#define     REWIND(m)               ISTREAM->rewind(ISTREAM, m)
#define     REWINDLAST()            ISTREAM->rewindLast(ISTREAM)
#define     SEEK(n)             ISTREAM->seek(ISTREAM, n)
#define     PERRORRECOVERY          PSRSTATE->errorRecovery
#define     FAILEDFLAG              PSRSTATE->failed
#define     HASFAILED()             (FAILEDFLAG == ANTLR3_TRUE)
#define     BACKTRACKING            PSRSTATE->backtracking
#define     RECOVERFROMMISMATCHEDSET(s)     RECOGNIZER->recoverFromMismatchedSet(RECOGNIZER, s)
#define     RECOVERFROMMISMATCHEDELEMENT(e) RECOGNIZER->recoverFromMismatchedElement(RECOGNIZER, s)
#define     ADAPTOR                         ctx->adaptor
#define     RULEMEMO                        PSRSTATE->ruleMemo
#define     DBG                             RECOGNIZER->debugger

#define     TOKTEXT(tok, txt)               tok, (pANTLR3_UINT8)txt

/* The 4 tokens defined below may well clash with your own #defines or token types. If so
 * then for the present you must use different names for your defines as these are hard coded
 * in the code generator. It would be better not to use such names internally, and maybe
 * we can change this in a forthcoming release. I deliberately do not #undef these
 * here as this will at least give you a redefined error somewhere if they clash.
 */
#define     UP      ANTLR3_TOKEN_UP
#define     DOWN    ANTLR3_TOKEN_DOWN
#define     EOR     ANTLR3_TOKEN_EOR
#define     INVALID ANTLR3_TOKEN_INVALID


/* =============================================================================
 * Functions to create and destroy scopes. First come the rule scopes, followed
 * by the global declared scopes.
 */


/* globalAttributeScopeFuncDecl(scope)
 */
/* -----------------------------------------------------------------------------
 * Function declaration for creating a SolidColorParser_ColorSet scope set
 */
static pSolidColorParser_ColorSet_SCOPE   pSolidColorParser_ColorSetPush(pSolidColorParser ctx);
static void ANTLR3_CDECL ColorSetFree(pSolidColorParser_ColorSet_SCOPE scope);
/* ----------------------------------------------------------------------------- */

/* globalAttributeScopeFuncs(scope)
 */
/* attributeFuncs(scope)
 */

static void ANTLR3_CDECL ColorSetFree(pSolidColorParser_ColorSet_SCOPE scope)
{
    ANTLR3_FREE(scope);
}

/** \brief Allocate initial memory for a SolidColorParser ColorSet scope variable stack entry and
 *         add it to the top of the stack.
 *
 * \remark
 * By default the structure is freed with ANTLR_FREE(), but you can use the
 * the \@init action to install a pointer to a custom free() routine by
 * adding the code:
 * \code
 *   ctx->pSolidColorParser_ColorSetTop->free = myroutine;
 * \endcode
 *
 * With lots of comments of course! The routine should be declared in
 * \@members { } as:
 * \code
 *   void ANTLR3_CDECL myfunc( pSolidColorParser_ColorSet_SCOPE ptr).
 * \endcode
 *
 * It should perform any custom freeing stuff that you need (call ANTLR_FREE3, not free()
 * NB: It should not free the pointer it is given, which is the scope stack entry itself
 * and will be freed by the function that calls your custom free routine.
 *
 */
static pSolidColorParser_ColorSet_SCOPE
pSolidColorParser_ColorSetPush(pSolidColorParser ctx)
{
    /* Pointer used to create a new set of attributes
     */
    pSolidColorParser_ColorSet_SCOPE      newAttributes;

    /* Allocate the memory for a new structure if we need one.
     */
    if (ctx->pSolidColorParser_ColorSetStack->size(ctx->pSolidColorParser_ColorSetStack) > ctx->pSolidColorParser_ColorSetStack_limit) {
        // The current limit value was less than the number of scopes available on the stack so
        // we can just reuse one. Our limit tracks the stack count, so the index of the entry we want
        // is one less than that, or conveniently, the current value of limit.
        //
        newAttributes = (pSolidColorParser_ColorSet_SCOPE)ctx->pSolidColorParser_ColorSetStack->get(ctx->pSolidColorParser_ColorSetStack, ctx->pSolidColorParser_ColorSetStack_limit);
    } else {
        // Need a new allocation
        //
        newAttributes = (pSolidColorParser_ColorSet_SCOPE) ANTLR3_MALLOC(sizeof(SolidColorParser_ColorSet_SCOPE));
        if  (newAttributes != NULL) {
            /* Standard ANTLR3 library implementation
             */
            ctx->pSolidColorParser_ColorSetStack->push(ctx->pSolidColorParser_ColorSetStack, newAttributes, (void (*)(void *))ColorSetFree);
        }
    }

    // Blank out any previous free pointer, the user might or might install a new one.
    //
    newAttributes->free = NULL;

    // Indicate the position in the available stack that the current level is at
    //
    ctx->pSolidColorParser_ColorSetStack_limit++;

    /* Return value is the pointer to the new entry, which may be used locally
     * without de-referencing via the context.
     */
    return  newAttributes;
}



/* ============================================================================= */

/* =============================================================================
 * Start of recognizer
 */



/** \brief Table of all token names in symbolic order, mainly used for
 *         error reporting.
 */
pANTLR3_UINT8   SolidColorParserTokenNames[15 + 4]
= {
    (pANTLR3_UINT8) "<invalid>",       /* String to print to indicate an invalid token */
    (pANTLR3_UINT8) "<EOR>",
    (pANTLR3_UINT8) "<DOWN>",
    (pANTLR3_UINT8) "<UP>",
    (pANTLR3_UINT8) "ID",
    (pANTLR3_UINT8) "HEX_DIGIT",
    (pANTLR3_UINT8) "HEXINT",
    (pANTLR3_UINT8) "EXPONENT",
    (pANTLR3_UINT8) "FLOAT",
    (pANTLR3_UINT8) "COMMENT",
    (pANTLR3_UINT8) "WS",
    (pANTLR3_UINT8) "ESC_SEQ",
    (pANTLR3_UINT8) "STRING",
    (pANTLR3_UINT8) "UNICODE_ESC",
    (pANTLR3_UINT8) "OCTAL_ESC",
    (pANTLR3_UINT8) "'rgba('",
    (pANTLR3_UINT8) "','",
    (pANTLR3_UINT8) "')'",
    (pANTLR3_UINT8) "'hsba('"
};


/* globalAttributeScopeFuncMacro(scope)
 */
/** Function  for popping the top value from a pSolidColorParser_ColorSetStack
 */
void
pSolidColorParser_ColorSetPop(pSolidColorParser ctx)
{
    // First see if the user defined a function they want to be called when a
    // scope is popped/freed.
    //
    // If the user supplied the scope entries with a free function,then call it first
    //
    if  (SCOPE_TOP(ColorSet)->free != NULL) {
        SCOPE_TOP(ColorSet)->free(SCOPE_TOP(ColorSet));
    }

    // Now we decrement the scope's upper limit bound. We do not actually pop the scope as
    // we want to reuse scope entries if we do continuous push and pops. Most scopes don't
    // next too far so we don't want to keep freeing and allocating them
    //
    ctx->pSolidColorParser_ColorSetStack_limit--;
    SCOPE_TOP(ColorSet) = (pSolidColorParser_ColorSet_SCOPE)(ctx->pSolidColorParser_ColorSetStack->get(ctx->pSolidColorParser_ColorSetStack, ctx->pSolidColorParser_ColorSetStack_limit - 1));
}

// Forward declare the locally static matching functions we have generated.
//
static nx::color::SolidColor*   solidColor    (pSolidColorParser ctx);
static void rgba    (pSolidColorParser ctx);
static void hsba    (pSolidColorParser ctx);
static void SolidColorParserFree(pSolidColorParser ctx);
static void     SolidColorParserReset (pSolidColorParser ctx);

/* For use in tree output where we are accumulating rule labels via label += ruleRef
 * we need a function that knows how to free a return scope when the list is destroyed.
 * We cannot just use ANTLR3_FREE because in debug tracking mode, this is a macro.
 */
static  void ANTLR3_CDECL freeScope(void * scope)
{
    ANTLR3_FREE(scope);
}

/** \brief Name of the grammar file that generated this code
 */
static const char fileName[] = "SolidColor.g";

/** \brief Return the name of the grammar file that generated this code.
 */
static const char * getGrammarFileName()
{
    return fileName;
}
/** \brief Create a new SolidColorParser parser and return a context for it.
 *
 * \param[in] instream Pointer to an input stream interface.
 *
 * \return Pointer to new parser context upon success.
 */
ANTLR3_API pSolidColorParser
SolidColorParserNew   (pANTLR3_COMMON_TOKEN_STREAM instream)
{
    // See if we can create a new parser with the standard constructor
    //
    return SolidColorParserNewSSD(instream, NULL);
}

/** \brief Create a new SolidColorParser parser and return a context for it.
 *
 * \param[in] instream Pointer to an input stream interface.
 *
 * \return Pointer to new parser context upon success.
 */
ANTLR3_API pSolidColorParser
SolidColorParserNewSSD   (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state)
{
    pSolidColorParser ctx;      /* Context structure we will build and return   */

    ctx = (pSolidColorParser) ANTLR3_CALLOC(1, sizeof(SolidColorParser));

    if  (ctx == NULL) {
        // Failed to allocate memory for parser context
        //
        return  NULL;
    }

    /* -------------------------------------------------------------------
     * Memory for basic structure is allocated, now to fill in
     * the base ANTLR3 structures. We initialize the function pointers
     * for the standard ANTLR3 parser function set, but upon return
     * from here, the programmer may set the pointers to provide custom
     * implementations of each function.
     *
     * We don't use the macros defined in SolidColorParser.h here, in order that you can get a sense
     * of what goes where.
     */

    /* Create a base parser/recognizer, using the supplied token stream
     */
    ctx->pParser        = antlr3ParserNewStream(ANTLR3_SIZE_HINT, instream->tstream, state);
    /* Install the implementation of our SolidColorParser interface
     */
    ctx->solidColor = solidColor;
    ctx->rgba   = rgba;
    ctx->hsba   = hsba;
    ctx->free           = SolidColorParserFree;
    ctx->reset          = SolidColorParserReset;
    ctx->getGrammarFileName = getGrammarFileName;

    /* Install the scope pushing methods.
     */
    /* globalAttributeScope(scope)
     */
    ctx->pSolidColorParser_ColorSetPush     = pSolidColorParser_ColorSetPush;
    ctx->pSolidColorParser_ColorSetStack    = antlr3StackNew(0);
    ctx->pSolidColorParser_ColorSetStack_limit    = 0;
    ctx->pSolidColorParser_ColorSetTop      = NULL;






    /* Install the token table
     */
    PSRSTATE->tokenNames   = SolidColorParserTokenNames;


    /* Return the newly built parser to the caller
     */
    return  ctx;
}

static void
SolidColorParserReset (pSolidColorParser ctx)
{
    RECOGNIZER->reset(RECOGNIZER);
}

/** Free the parser resources
 */
static void
SolidColorParserFree(pSolidColorParser ctx)
{
    /* Free any scope memory
     */
    /* globalAttributeScope(scope)
     */
    ctx->pSolidColorParser_ColorSetStack->free(ctx->pSolidColorParser_ColorSetStack);



    // Free this parser
    //
    ctx->pParser->free(ctx->pParser);

    ANTLR3_FREE(ctx);

    /* Everything is released, so we can return
     */
    return;
}

/** Return token names used by this parser
 *
 * The returned pointer is used as an index into the token names table (using the token
 * number as the index).
 *
 * \return Pointer to first char * in the table.
 */
static pANTLR3_UINT8    *getTokenNames()
{
    return SolidColorParserTokenNames;
}


/* Declare the bitsets
 */

/** Bitset defining follow set for error recovery in rule state: FOLLOW_rgba_in_solidColor613  */
static  ANTLR3_BITWORD FOLLOW_rgba_in_solidColor613_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000002) };
static  ANTLR3_BITSET_LIST FOLLOW_rgba_in_solidColor613 = { FOLLOW_rgba_in_solidColor613_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_hsba_in_solidColor617  */
static  ANTLR3_BITWORD FOLLOW_hsba_in_solidColor617_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000002) };
static  ANTLR3_BITSET_LIST FOLLOW_hsba_in_solidColor617 = { FOLLOW_hsba_in_solidColor617_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_15_in_rgba635  */
static  ANTLR3_BITWORD FOLLOW_15_in_rgba635_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_15_in_rgba635 = { FOLLOW_15_in_rgba635_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_rgba639  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_rgba639_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_rgba639  = { FOLLOW_FLOAT_in_rgba639_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_rgba641  */
static  ANTLR3_BITWORD FOLLOW_16_in_rgba641_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_rgba641 = { FOLLOW_16_in_rgba641_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_rgba645  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_rgba645_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_rgba645  = { FOLLOW_FLOAT_in_rgba645_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_rgba647  */
static  ANTLR3_BITWORD FOLLOW_16_in_rgba647_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_rgba647 = { FOLLOW_16_in_rgba647_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_rgba651  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_rgba651_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_rgba651  = { FOLLOW_FLOAT_in_rgba651_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_rgba653  */
static  ANTLR3_BITWORD FOLLOW_16_in_rgba653_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_rgba653 = { FOLLOW_16_in_rgba653_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_rgba657  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_rgba657_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000020000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_rgba657  = { FOLLOW_FLOAT_in_rgba657_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_17_in_rgba659  */
static  ANTLR3_BITWORD FOLLOW_17_in_rgba659_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000002) };
static  ANTLR3_BITSET_LIST FOLLOW_17_in_rgba659 = { FOLLOW_17_in_rgba659_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_15_in_rgba670  */
static  ANTLR3_BITWORD FOLLOW_15_in_rgba670_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000040) };
static  ANTLR3_BITSET_LIST FOLLOW_15_in_rgba670 = { FOLLOW_15_in_rgba670_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_HEXINT_in_rgba674  */
static  ANTLR3_BITWORD FOLLOW_HEXINT_in_rgba674_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_HEXINT_in_rgba674 = { FOLLOW_HEXINT_in_rgba674_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_rgba676  */
static  ANTLR3_BITWORD FOLLOW_16_in_rgba676_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_rgba676 = { FOLLOW_16_in_rgba676_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_rgba680  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_rgba680_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000020000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_rgba680  = { FOLLOW_FLOAT_in_rgba680_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_17_in_rgba682  */
static  ANTLR3_BITWORD FOLLOW_17_in_rgba682_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000002) };
static  ANTLR3_BITSET_LIST FOLLOW_17_in_rgba682 = { FOLLOW_17_in_rgba682_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_18_in_hsba697  */
static  ANTLR3_BITWORD FOLLOW_18_in_hsba697_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_18_in_hsba697 = { FOLLOW_18_in_hsba697_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_hsba701  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_hsba701_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_hsba701  = { FOLLOW_FLOAT_in_hsba701_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_hsba703  */
static  ANTLR3_BITWORD FOLLOW_16_in_hsba703_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_hsba703 = { FOLLOW_16_in_hsba703_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_hsba707  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_hsba707_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_hsba707  = { FOLLOW_FLOAT_in_hsba707_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_hsba709  */
static  ANTLR3_BITWORD FOLLOW_16_in_hsba709_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_hsba709 = { FOLLOW_16_in_hsba709_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_hsba713  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_hsba713_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000010000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_hsba713  = { FOLLOW_FLOAT_in_hsba713_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_16_in_hsba715  */
static  ANTLR3_BITWORD FOLLOW_16_in_hsba715_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000100) };
static  ANTLR3_BITSET_LIST FOLLOW_16_in_hsba715 = { FOLLOW_16_in_hsba715_bits, 1    };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_FLOAT_in_hsba719  */
static  ANTLR3_BITWORD FOLLOW_FLOAT_in_hsba719_bits[]   = { ANTLR3_UINT64_LIT(0x0000000000020000) };
static  ANTLR3_BITSET_LIST FOLLOW_FLOAT_in_hsba719  = { FOLLOW_FLOAT_in_hsba719_bits, 1 };
/** Bitset defining follow set for error recovery in rule state: FOLLOW_17_in_hsba721  */
static  ANTLR3_BITWORD FOLLOW_17_in_hsba721_bits[]  = { ANTLR3_UINT64_LIT(0x0000000000000002) };
static  ANTLR3_BITSET_LIST FOLLOW_17_in_hsba721 = { FOLLOW_17_in_hsba721_bits, 1    };




/* ==============================================
 * Parsing rules
 */
/**
 * $ANTLR start solidColor
 * SolidColor.g:101:1: solidColor returns [nx::color::SolidColor* ret] : ( rgba | hsba ) ;
 */
static nx::color::SolidColor*
solidColor(pSolidColorParser ctx)
{
    nx::color::SolidColor* ret;

    /* Initialize rule variables
     */
    ctx->pSolidColorParser_ColorSetTop = pSolidColorParser_ColorSetPush(ctx);


    (SCOPE_TOP(ColorSet))->solidColor = new nx::color::SolidColor();

    {
        // SolidColor.g:106:2: ( ( rgba | hsba ) )
        // SolidColor.g:107:2: ( rgba | hsba )
        {

            // SolidColor.g:107:2: ( rgba | hsba )
            {
                int alt1 = 2;
                switch ( LA(1) ) {
                case 15: {
                    alt1 = 1;
                }
                break;
                case 18: {
                    alt1 = 2;
                }
                break;

                default:
                    CONSTRUCTEX();
                    EXCEPTION->type         = ANTLR3_NO_VIABLE_ALT_EXCEPTION;
                    EXCEPTION->message      = (void *)"";
                    EXCEPTION->decisionNum  = 1;
                    EXCEPTION->state        = 0;


                    goto rulesolidColorEx;
                }

                switch (alt1) {
                case 1:
                    // SolidColor.g:107:4: rgba
                {
                    FOLLOWPUSH(FOLLOW_rgba_in_solidColor613);
                    rgba(ctx);

                    FOLLOWPOP();
                    if  (HASEXCEPTION()) {
                        goto rulesolidColorEx;
                    }


                }
                break;
                case 2:
                    // SolidColor.g:107:11: hsba
                {
                    FOLLOWPUSH(FOLLOW_hsba_in_solidColor617);
                    hsba(ctx);

                    FOLLOWPOP();
                    if  (HASEXCEPTION()) {
                        goto rulesolidColorEx;
                    }


                }
                break;

                }
            }
            {

                ret =    (SCOPE_TOP(ColorSet))->solidColor;

            }

        }

    }


    // This is where rules clean up and exit
    //
    goto rulesolidColorEx; /* Prevent compiler warnings */
rulesolidColorEx:
    ;

    if (HASEXCEPTION()) {
        PREPORTERROR();
        PRECOVER();
    }

    pSolidColorParser_ColorSetPop(ctx);

    return ret;
}
/* $ANTLR end solidColor */

/**
 * $ANTLR start rgba
 * SolidColor.g:113:1: rgba : ( ( 'rgba(' r= FLOAT ',' g= FLOAT ',' b= FLOAT ',' a= FLOAT ')' ) | ( 'rgba(' rgb= HEXINT ',' a= FLOAT ')' ) );
 */
static void
rgba(pSolidColorParser ctx)
{
    pANTLR3_COMMON_TOKEN    r;
    pANTLR3_COMMON_TOKEN    g;
    pANTLR3_COMMON_TOKEN    b;
    pANTLR3_COMMON_TOKEN    a;
    pANTLR3_COMMON_TOKEN    rgb;

    /* Initialize rule variables
     */


    r       = NULL;
    g       = NULL;
    b       = NULL;
    a       = NULL;
    rgb       = NULL;

    {
        {
            //  SolidColor.g:113:6: ( ( 'rgba(' r= FLOAT ',' g= FLOAT ',' b= FLOAT ',' a= FLOAT ')' ) | ( 'rgba(' rgb= HEXINT ',' a= FLOAT ')' ) )

            ANTLR3_UINT32 alt2;

            alt2 = 2;

            switch ( LA(1) ) {
            case 15: {
                switch ( LA(2) ) {
                case FLOAT: {
                    alt2 = 1;
                }
                break;
                case HEXINT: {
                    alt2 = 2;
                }
                break;

                default:
                    CONSTRUCTEX();
                    EXCEPTION->type         = ANTLR3_NO_VIABLE_ALT_EXCEPTION;
                    EXCEPTION->message      = (void *)"";
                    EXCEPTION->decisionNum  = 2;
                    EXCEPTION->state        = 1;


                    goto rulergbaEx;
                }

            }
            break;

            default:
                CONSTRUCTEX();
                EXCEPTION->type         = ANTLR3_NO_VIABLE_ALT_EXCEPTION;
                EXCEPTION->message      = (void *)"";
                EXCEPTION->decisionNum  = 2;
                EXCEPTION->state        = 0;


                goto rulergbaEx;
            }

            switch (alt2) {
            case 1:
                // SolidColor.g:114:2: ( 'rgba(' r= FLOAT ',' g= FLOAT ',' b= FLOAT ',' a= FLOAT ')' )
            {
                // SolidColor.g:114:2: ( 'rgba(' r= FLOAT ',' g= FLOAT ',' b= FLOAT ',' a= FLOAT ')' )
                // SolidColor.g:114:3: 'rgba(' r= FLOAT ',' g= FLOAT ',' b= FLOAT ',' a= FLOAT ')'
                {
                    MATCHT(15, &FOLLOW_15_in_rgba635);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    r = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_rgba639);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    MATCHT(16, &FOLLOW_16_in_rgba641);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    g = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_rgba645);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    MATCHT(16, &FOLLOW_16_in_rgba647);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    b = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_rgba651);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    MATCHT(16, &FOLLOW_16_in_rgba653);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    a = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_rgba657);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    MATCHT(17, &FOLLOW_17_in_rgba659);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }


                }

                {

                    (SCOPE_TOP(ColorSet))->solidColor->SetColor(
                        pu8tof((r->getText(r))->chars),
                        pu8tof((g->getText(g))->chars),
                        pu8tof((b->getText(b))->chars),
                        pu8tof((a->getText(a))->chars));

                }

            }
            break;
            case 2:
                // SolidColor.g:122:2: ( 'rgba(' rgb= HEXINT ',' a= FLOAT ')' )
            {
                // SolidColor.g:122:2: ( 'rgba(' rgb= HEXINT ',' a= FLOAT ')' )
                // SolidColor.g:122:3: 'rgba(' rgb= HEXINT ',' a= FLOAT ')'
                {
                    MATCHT(15, &FOLLOW_15_in_rgba670);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    rgb = (pANTLR3_COMMON_TOKEN) MATCHT(HEXINT, &FOLLOW_HEXINT_in_rgba674);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    MATCHT(16, &FOLLOW_16_in_rgba676);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    a = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_rgba680);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }

                    MATCHT(17, &FOLLOW_17_in_rgba682);
                    if  (HASEXCEPTION()) {
                        goto rulergbaEx;
                    }


                }

                {

                    float red, green, blue;
                    parse3values((rgb->getText(rgb))->chars, &red, &green, &blue);
                    (SCOPE_TOP(ColorSet))->solidColor->SetColor(
                        red,
                        green,
                        blue,
                        pu8tof((a->getText(a))->chars));

                }

            }
            break;

            }
        }
    }


    // This is where rules clean up and exit
    //
    goto rulergbaEx; /* Prevent compiler warnings */
rulergbaEx:
    ;

    if (HASEXCEPTION()) {
        PREPORTERROR();
        PRECOVER();
    }


    return ;
}
/* $ANTLR end rgba */

/**
 * $ANTLR start hsba
 * SolidColor.g:133:1: hsba : 'hsba(' h= FLOAT ',' s= FLOAT ',' b= FLOAT ',' a= FLOAT ')' ;
 */
static void
hsba(pSolidColorParser ctx)
{
    pANTLR3_COMMON_TOKEN    h;
    pANTLR3_COMMON_TOKEN    s;
    pANTLR3_COMMON_TOKEN    b;
    pANTLR3_COMMON_TOKEN    a;

    /* Initialize rule variables
     */


    h       = NULL;
    s       = NULL;
    b       = NULL;
    a       = NULL;

    {
        // SolidColor.g:133:6: ( 'hsba(' h= FLOAT ',' s= FLOAT ',' b= FLOAT ',' a= FLOAT ')' )
        // SolidColor.g:134:2: 'hsba(' h= FLOAT ',' s= FLOAT ',' b= FLOAT ',' a= FLOAT ')'
        {
            MATCHT(18, &FOLLOW_18_in_hsba697);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            h = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_hsba701);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            MATCHT(16, &FOLLOW_16_in_hsba703);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            s = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_hsba707);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            MATCHT(16, &FOLLOW_16_in_hsba709);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            b = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_hsba713);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            MATCHT(16, &FOLLOW_16_in_hsba715);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            a = (pANTLR3_COMMON_TOKEN) MATCHT(FLOAT, &FOLLOW_FLOAT_in_hsba719);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            MATCHT(17, &FOLLOW_17_in_hsba721);
            if  (HASEXCEPTION()) {
                goto rulehsbaEx;
            }

            {

                float red, green, blue;
                HsvToRgb(
                    pu8tof((h->getText(h))->chars),
                    pu8tof((s->getText(s))->chars),
                    pu8tof((b->getText(b))->chars),
                    red,
                    green,
                    blue);
                (SCOPE_TOP(ColorSet))->solidColor->SetColor(
                    red,
                    green,
                    blue,
                    pu8tof((a->getText(a))->chars));

            }

        }

    }


    // This is where rules clean up and exit
    //
    goto rulehsbaEx; /* Prevent compiler warnings */
rulehsbaEx:
    ;

    if (HASEXCEPTION()) {
        PREPORTERROR();
        PRECOVER();
    }


    return ;
}
/* $ANTLR end hsba */
/* End of parsing rules
 * ==============================================
 */

/* ==============================================
 * Syntactic predicates
 */
/* End of syntactic predicates
 * ==============================================
 */






/* End of code
 * =============================================================================
 */