/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

// File responsible for the syntax analyses phase of the compiler
// Builds the AST (Abstract Syntax Tree) that represents the NFLang program
// Define astRoot as the root of the AST tree when the syntax analyses is done
// Also define tokens used in the lexical analyses

#include <stdio.h>    
#include <stdlib.h>
#include <iostream>
#include <string>
#include "nodes.h"
using namespace std;

// Retrieve global pointer to astRoot (defined in main.cpp)
extern Node* astRoot;

// Define lexer functions
int yylex(); 
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

// Helper functions designed to create AST nodes
Node* makeNoOp() {
    return new Number(0, vector<unique_ptr<Node>>());
}

Node* makeSignal() {
    return new Signal(0, vector<unique_ptr<Node>>());
}

Node* makeDown(string *str) {
    return new Down(*str, vector<unique_ptr<Node>>());
}

Node* makeString(string *str) {
    return new String(*str, vector<unique_ptr<Node>>());
}

Node* makeNumber(int value) {
    return new Number(value, vector<unique_ptr<Node>>());
}

Node* makeIdentifier(string *identifier) {
    return new Identifier(*identifier, vector<unique_ptr<Node>>());
}

Node* makePlayValueIdentifier(string *identifier, string *position) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(makeIdentifier(position));
    return new Identifier(*identifier, move(children));
}

Node* makeUnOp(int operation, Node *child) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(child));
    return new UnOp(operation, move(children));
}

Node* makeBinOp(int operation, Node *left, Node *right) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(left));
    children.emplace_back(unique_ptr<Node>(right));
    return new BinOp(operation, move(children));
}

Node* makeEmptyPlay() {
    return new Play(0, vector<unique_ptr<Node>>());
}

Node* makePlayWithArguments(Node *arguments) {
    vector<unique_ptr<Node>> children;

    for (auto& argument : arguments->children) {
        children.emplace_back(std::move(argument));
    }

    return new Play(0, move(children));
}

Node* makePureVarDeclaration(string *type, string *identifier) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    return new VarDeclaration(*type, move(children));
}

Node* makeVarDeclarationWithAssignment(string *type, string *identifier, Node *expression) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    children.emplace_back(unique_ptr<Node>(expression));
    return new VarDeclaration(*type, move(children));
}

Node* makeAssignment(string *identifier, Node *expression) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    children.emplace_back(unique_ptr<Node>(expression));
    return new Assignment(0, move(children));
}

Node* makePlayPositionAssignment(string *identifier, string *position, Node *expression) {
    vector<unique_ptr<Node>> children;
    Node* identifierNode = makeIdentifier(identifier);
    Node* positionNode = makeIdentifier(position);
    children.emplace_back(unique_ptr<Node>(identifierNode));
    children.emplace_back(unique_ptr<Node>(positionNode));
    children.emplace_back(unique_ptr<Node>(expression));
    return new Assignment(0, move(children));
}

Node* makeCall(Node *child) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(child));
    return new Call(0, move(children));
}

Node* makeWhenConditionalWithOneBlock(Node *condition, Node *block) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(condition));
    children.emplace_back(unique_ptr<Node>(block));
    return new WhenConditional(0, move(children));
}

Node* makeWhenConditionalWithTwoBlocks(Node *condition, Node *whenBlock, Node *otherwiseBlock) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(condition));
    children.emplace_back(unique_ptr<Node>(whenBlock));
    children.emplace_back(unique_ptr<Node>(otherwiseBlock));
    return new WhenConditional(0, move(children));
}

Node* makePlayUntil(Node *condition, Node *block) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(condition));
    children.emplace_back(unique_ptr<Node>(block));
    return new PlayUntil(0, move(children));
}

Node* makeDrive(string *type, string *identifier, Node *leftValue, Node *rightValue, Node *block) {
    vector<unique_ptr<Node>> children;

    Node* variableDeclarationNode = makeVarDeclarationWithAssignment(type, identifier, leftValue);
    children.emplace_back(unique_ptr<Node>(variableDeclarationNode));
    children.emplace_back(unique_ptr<Node>(rightValue));
    children.emplace_back(unique_ptr<Node>(block));
    return new Drive(0, move(children));
}

Node* makeFunctionDeclarationWithoutArgs(string *type, string *identifier, Node *block) {
    vector<unique_ptr<Node>> children;

    Node* functionVarDec = makePureVarDeclaration(type, identifier);
    children.emplace_back(unique_ptr<Node>(functionVarDec));
    children.emplace_back(unique_ptr<Node>(block));
    return new FunctionDeclaration(0, move(children));
}

Node* makeFunctionDeclarationWithArgs(string *type, string *identifier, Node *arguments, Node *block) {
    vector<unique_ptr<Node>> children;

    Node* functionVarDec = makePureVarDeclaration(type, identifier);
    children.emplace_back(unique_ptr<Node>(functionVarDec));

    for (auto& argument : arguments->children) {
        children.emplace_back(std::move(argument));
    }

    children.emplace_back(unique_ptr<Node>(block));
    return new FunctionDeclaration(0, move(children));
}

Node* makeFunctionCallWithoutArgs(string *identifier) {
    return new FunctionCall(*identifier, vector<unique_ptr<Node>>());
}

Node* makeFunctionCallWithArgs(string *identifier, Node *arguments) {
    vector<unique_ptr<Node>> children;

    for (auto& argument : arguments->children) {
        children.emplace_back(std::move(argument));
    }

    return new FunctionCall(*identifier, move(children));
}

Node* makeResult(Node *expression) {
    vector<unique_ptr<Node>> children;
    children.emplace_back(unique_ptr<Node>(expression));

    return new Result(0, move(children));
}

Node* makeBlock() {
    return new Block(0, vector<unique_ptr<Node>>());
}


#line 272 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PLUS = 3,                       /* PLUS  */
  YYSYMBOL_MINUS = 4,                      /* MINUS  */
  YYSYMBOL_INCREMENT = 5,                  /* INCREMENT  */
  YYSYMBOL_L_PARENTHESIS = 6,              /* L_PARENTHESIS  */
  YYSYMBOL_R_PARENTHESIS = 7,              /* R_PARENTHESIS  */
  YYSYMBOL_TIMES = 8,                      /* TIMES  */
  YYSYMBOL_DIVIDE = 9,                     /* DIVIDE  */
  YYSYMBOL_NOT = 10,                       /* NOT  */
  YYSYMBOL_EQUALS = 11,                    /* EQUALS  */
  YYSYMBOL_GREATER_THAN = 12,              /* GREATER_THAN  */
  YYSYMBOL_LESSER_THAN = 13,               /* LESSER_THAN  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_IS = 16,                        /* IS  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_COLON = 18,                     /* COLON  */
  YYSYMBOL_DOT = 19,                       /* DOT  */
  YYSYMBOL_SIGNAL = 20,                    /* SIGNAL  */
  YYSYMBOL_CALL = 21,                      /* CALL  */
  YYSYMBOL_WHEN = 22,                      /* WHEN  */
  YYSYMBOL_THEN = 23,                      /* THEN  */
  YYSYMBOL_OTHERWISE = 24,                 /* OTHERWISE  */
  YYSYMBOL_DRIVE = 25,                     /* DRIVE  */
  YYSYMBOL_ON = 26,                        /* ON  */
  YYSYMBOL_PLAY_UNTIL = 27,                /* PLAY_UNTIL  */
  YYSYMBOL_BREAK_LINE = 28,                /* BREAK_LINE  */
  YYSYMBOL_ACTION = 29,                    /* ACTION  */
  YYSYMBOL_L_BRACKET = 30,                 /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 31,                 /* R_BRACKET  */
  YYSYMBOL_RESULT = 32,                    /* RESULT  */
  YYSYMBOL_IDENTIFIER = 33,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 34,                    /* NUMBER  */
  YYSYMBOL_STRING = 35,                    /* STRING  */
  YYSYMBOL_POSITION = 36,                  /* POSITION  */
  YYSYMBOL_DOWN = 37,                      /* DOWN  */
  YYSYMBOL_TYPE = 38,                      /* TYPE  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_program = 40,                   /* program  */
  YYSYMBOL_statements = 41,                /* statements  */
  YYSYMBOL_statement = 42,                 /* statement  */
  YYSYMBOL_block = 43,                     /* block  */
  YYSYMBOL_func_declaration = 44,          /* func_declaration  */
  YYSYMBOL_declaration_arguments = 45,     /* declaration_arguments  */
  YYSYMBOL_drive_loop = 46,                /* drive_loop  */
  YYSYMBOL_play_until = 47,                /* play_until  */
  YYSYMBOL_when_conditional = 48,          /* when_conditional  */
  YYSYMBOL_variable_declaration = 49,      /* variable_declaration  */
  YYSYMBOL_assignment = 50,                /* assignment  */
  YYSYMBOL_call_arguments = 51,            /* call_arguments  */
  YYSYMBOL_call = 52,                      /* call  */
  YYSYMBOL_func_statements = 53,           /* func_statements  */
  YYSYMBOL_func_statement = 54,            /* func_statement  */
  YYSYMBOL_func_block = 55,                /* func_block  */
  YYSYMBOL_result = 56,                    /* result  */
  YYSYMBOL_func_drive_loop = 57,           /* func_drive_loop  */
  YYSYMBOL_func_play_until = 58,           /* func_play_until  */
  YYSYMBOL_func_when_conditional = 59,     /* func_when_conditional  */
  YYSYMBOL_general_expression = 60,        /* general_expression  */
  YYSYMBOL_play_expression = 61,           /* play_expression  */
  YYSYMBOL_play_arguments = 62,            /* play_arguments  */
  YYSYMBOL_boolean_expression = 63,        /* boolean_expression  */
  YYSYMBOL_boolean_term = 64,              /* boolean_term  */
  YYSYMBOL_relative_expression = 65,       /* relative_expression  */
  YYSYMBOL_expression = 66,                /* expression  */
  YYSYMBOL_term = 67,                      /* term  */
  YYSYMBOL_factor = 68                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   242,   242,   250,   251,   255,   256,   257,   258,   259,
     260,   261,   262,   266,   267,   272,   274,   279,   281,   286,
     291,   294,   295,   299,   300,   304,   305,   306,   307,   311,
     312,   316,   322,   323,   327,   328,   329,   330,   331,   332,
     333,   334,   338,   339,   343,   346,   352,   356,   357,   365,
     366,   370,   371,   374,   375,   379,   380,   384,   385,   389,
     390,   391,   392,   396,   397,   398,   402,   403,   404,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PLUS", "MINUS",
  "INCREMENT", "L_PARENTHESIS", "R_PARENTHESIS", "TIMES", "DIVIDE", "NOT",
  "EQUALS", "GREATER_THAN", "LESSER_THAN", "AND", "OR", "IS", "COMMA",
  "COLON", "DOT", "SIGNAL", "CALL", "WHEN", "THEN", "OTHERWISE", "DRIVE",
  "ON", "PLAY_UNTIL", "BREAK_LINE", "ACTION", "L_BRACKET", "R_BRACKET",
  "RESULT", "IDENTIFIER", "NUMBER", "STRING", "POSITION", "DOWN", "TYPE",
  "$accept", "program", "statements", "statement", "block",
  "func_declaration", "declaration_arguments", "drive_loop", "play_until",
  "when_conditional", "variable_declaration", "assignment",
  "call_arguments", "call", "func_statements", "func_statement",
  "func_block", "result", "func_drive_loop", "func_play_until",
  "func_when_conditional", "general_expression", "play_expression",
  "play_arguments", "boolean_expression", "boolean_term",
  "relative_expression", "expression", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     122,    69,   119,    -8,   119,  -121,    53,    40,    49,   108,
     122,  -121,    83,    85,    90,    92,   105,   107,   109,    82,
     119,   119,   119,   119,   119,   104,    25,  -121,  -121,  -121,
      32,   124,    66,    23,    41,  -121,   103,     4,   112,     8,
      82,   106,   125,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,    -7,   133,  -121,   131,  -121,  -121,  -121,    56,
    -121,   141,    63,   123,   119,   132,   119,   119,   119,   119,
     119,   119,   119,   119,   140,   136,  -121,   162,  -121,    44,
    -121,  -121,   154,    82,  -121,   166,     6,  -121,  -121,  -121,
    -121,    45,  -121,   124,   156,    66,    23,    23,    23,    41,
      41,  -121,  -121,   176,  -121,   150,     1,  -121,    82,   119,
    -121,   119,   151,  -121,  -121,   132,   119,  -121,   160,   161,
      57,  -121,   131,   131,   175,  -121,    86,   164,  -121,  -121,
     160,   163,   119,   119,   119,   169,   119,  -121,  -121,    82,
     170,   180,   184,   178,  -121,   185,   186,   187,   189,  -121,
     171,   131,    65,    61,   188,    10,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,   132,   160,   192,
    -121,  -121,   195,   214,   160,   119,  -121,    89,   119,    74,
     160,  -121
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     5,     0,     0,     0,     0,
       2,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    69,    77,    78,
       0,    56,    58,    62,    65,    68,     0,     0,     0,     0,
       0,     0,    23,     1,     4,     6,     7,     8,     9,    10,
      11,    12,     0,     0,    50,    49,    71,    72,    73,     0,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,    26,     0,
      29,    25,     0,     0,    51,     0,     0,    31,    70,    79,
      80,     0,    76,    55,    21,    57,    59,    60,    61,    63,
      64,    66,    67,     0,    13,     0,     0,    27,     0,     0,
      24,     0,     0,    52,    81,     0,     0,    14,     0,     0,
       0,    30,    28,    53,     0,    22,     0,     0,    15,    17,
       0,     0,     0,     0,     0,     0,     0,    34,    42,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,    16,
       0,    54,     0,     0,     0,     0,    44,    39,    40,    41,
      43,    33,    35,    36,    37,    38,    18,     0,     0,     0,
      46,    19,    47,     0,     0,     0,    48,     0,     0,     0,
       0,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,   147,    -6,   -62,  -121,  -121,  -121,  -121,  -121,
    -111,  -110,   165,  -107,  -121,    80,  -120,  -121,  -121,  -121,
    -121,   -18,  -121,  -121,    -2,   167,   158,    59,    24,   -15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     9,    10,    11,    76,    12,   120,    13,    14,    15,
      16,    17,    79,    18,   143,   144,   128,   145,   146,   147,
     148,    80,    54,    86,    55,    31,    32,    33,    34,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    53,    37,    94,    44,    56,    57,    58,   118,    60,
     149,    20,    21,    22,    23,    78,   140,   141,    24,    64,
     142,    59,    81,   112,    84,    64,    70,    71,    25,    85,
      36,    62,   140,   141,    75,   170,   142,   113,    52,   119,
     127,    26,    27,    28,    63,    29,    39,    64,   172,    72,
      73,   107,   114,   125,   176,    65,    40,   101,   102,    41,
     181,   108,   108,    88,   130,   110,    20,    21,    22,    23,
      90,    64,   167,    24,   131,    19,    64,    67,    68,    69,
      64,   180,    42,    25,   168,    20,    21,    22,    23,    64,
     121,    38,    24,    52,    99,   100,    26,    27,    28,    44,
      29,    64,    25,   133,    64,   171,   178,   122,    43,   123,
      61,    45,    52,    46,   126,    26,    27,    28,    47,    29,
      48,   156,    20,    21,    22,    23,    96,    97,    98,    24,
     151,   152,   153,    49,   155,    50,    74,    51,    66,    25,
      87,    83,    82,     1,     2,    77,    64,     3,    89,     4,
       5,     6,    26,    27,    28,     7,    29,     1,     2,    92,
       8,     3,    75,     4,     5,     6,   103,   104,   106,     7,
     109,     1,     2,   177,     8,     3,   179,     4,     5,     6,
     115,   117,   116,     7,   111,     1,   134,   124,     8,   135,
     127,   136,   137,   132,   129,   138,   139,     7,   157,     1,
     134,   150,     8,   135,   166,   136,   137,   154,   158,   160,
     139,     7,   159,   162,   163,   164,     8,   165,   173,   174,
     175,   169,   105,   161,    95,     0,     0,    91,     0,     0,
       0,    93
};

static const yytype_int16 yycheck[] =
{
       2,    19,     4,    65,    10,    20,    21,    22,     7,    24,
     130,     3,     4,     5,     6,     7,   127,   127,    10,    15,
     127,    23,    40,    17,    31,    15,     3,     4,    20,    36,
      38,     6,   143,   143,    30,   155,   143,    31,    30,    38,
      30,    33,    34,    35,    19,    37,     6,    15,   168,     8,
       9,     7,     7,   115,   174,    23,    16,    72,    73,    19,
     180,    17,    17,     7,     7,    83,     3,     4,     5,     6,
       7,    15,     7,    10,    17,     6,    15,    11,    12,    13,
      15,     7,    33,    20,    23,     3,     4,     5,     6,    15,
     108,    38,    10,    30,    70,    71,    33,    34,    35,   105,
      37,    15,    20,    17,    15,   167,    17,   109,     0,   111,
       6,    28,    30,    28,   116,    33,    34,    35,    28,    37,
      28,   139,     3,     4,     5,     6,    67,    68,    69,    10,
     132,   133,   134,    28,   136,    28,    33,    28,    14,    20,
       7,    16,    36,    21,    22,    33,    15,    25,     7,    27,
      28,    29,    33,    34,    35,    33,    37,    21,    22,    36,
      38,    25,    30,    27,    28,    29,    26,    31,     6,    33,
      16,    21,    22,   175,    38,    25,   178,    27,    28,    29,
      24,    31,     6,    33,    18,    21,    22,    36,    38,    25,
      30,    27,    28,    18,    33,    31,    32,    33,    28,    21,
      22,    38,    38,    25,    33,    27,    28,    38,    28,    31,
      32,    33,    28,    28,    28,    28,    38,    28,    26,    24,
       6,    33,    75,   143,    66,    -1,    -1,    62,    -1,    -1,
      -1,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    21,    22,    25,    27,    28,    29,    33,    38,    40,
      41,    42,    44,    46,    47,    48,    49,    50,    52,     6,
       3,     4,     5,     6,    10,    20,    33,    34,    35,    37,
      63,    64,    65,    66,    67,    68,    38,    63,    38,     6,
      16,    19,    33,     0,    42,    28,    28,    28,    28,    28,
      28,    28,    30,    60,    61,    63,    68,    68,    68,    63,
      68,     6,     6,    19,    15,    23,    14,    11,    12,    13,
       3,     4,     8,     9,    33,    30,    43,    33,     7,    51,
      60,    60,    36,    16,    31,    36,    62,     7,     7,     7,
       7,    51,    36,    64,    43,    65,    66,    66,    66,    67,
      67,    68,    68,    26,    31,    41,     6,     7,    17,    16,
      60,    18,    17,    31,     7,    24,     6,    31,     7,    38,
      45,    60,    63,    63,    36,    43,    63,    30,    55,    33,
       7,    17,    18,    17,    22,    25,    27,    28,    31,    32,
      49,    50,    52,    53,    54,    56,    57,    58,    59,    55,
      38,    63,    63,    63,    38,    63,    60,    28,    28,    28,
      31,    54,    28,    28,    28,    28,    33,     7,    23,    33,
      55,    43,    55,    26,    24,     6,    55,    63,    17,    63,
       7,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    43,    43,    44,    44,    45,    45,    46,
      47,    48,    48,    49,    49,    50,    50,    50,    50,    51,
      51,    52,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    56,    57,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    65,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     6,     7,     2,     4,    10,
       3,     4,     6,     2,     4,     3,     3,     4,     5,     1,
       3,     4,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     2,    10,     3,     4,     6,     1,
       1,     2,     3,     3,     5,     3,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     1,
       3,     2,     2,     2,     2,     1,     3,     1,     1,     3,
       3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements  */
#line 242 "parser.y"
                    { 
    // Define de astRoot as the result of the program
    astRoot = (yyvsp[0].nodePtr);
}
#line 1460 "parser.tab.c"
    break;

  case 3: /* statements: statement  */
#line 250 "parser.y"
                      { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1466 "parser.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 251 "parser.y"
                            { (yyvsp[-1].nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1472 "parser.tab.c"
    break;

  case 5: /* statement: BREAK_LINE  */
#line 255 "parser.y"
                      { (yyval.nodePtr) = makeNoOp(); }
#line 1478 "parser.tab.c"
    break;

  case 13: /* block: L_BRACKET R_BRACKET  */
#line 266 "parser.y"
                           { (yyval.nodePtr) = makeNoOp(); }
#line 1484 "parser.tab.c"
    break;

  case 14: /* block: L_BRACKET statements R_BRACKET  */
#line 267 "parser.y"
                                     { (yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1490 "parser.tab.c"
    break;

  case 15: /* func_declaration: ACTION TYPE IDENTIFIER L_PARENTHESIS R_PARENTHESIS func_block  */
#line 273 "parser.y"
    { (yyval.nodePtr) = makeFunctionDeclarationWithoutArgs((yyvsp[-4].stringValue), (yyvsp[-3].stringValue), (yyvsp[0].nodePtr)); }
#line 1496 "parser.tab.c"
    break;

  case 16: /* func_declaration: ACTION TYPE IDENTIFIER L_PARENTHESIS declaration_arguments R_PARENTHESIS func_block  */
#line 275 "parser.y"
    { (yyval.nodePtr) = makeFunctionDeclarationWithArgs((yyvsp[-5].stringValue), (yyvsp[-4].stringValue), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1502 "parser.tab.c"
    break;

  case 17: /* declaration_arguments: TYPE IDENTIFIER  */
#line 280 "parser.y"
    { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>(makePureVarDeclaration((yyvsp[-1].stringValue), (yyvsp[0].stringValue)))); }
#line 1508 "parser.tab.c"
    break;

  case 18: /* declaration_arguments: declaration_arguments COMMA TYPE IDENTIFIER  */
#line 282 "parser.y"
    { (yyvsp[-3].nodePtr)->children.emplace_back(makePureVarDeclaration((yyvsp[-1].stringValue), (yyvsp[0].stringValue))); }
#line 1514 "parser.tab.c"
    break;

  case 19: /* drive_loop: DRIVE TYPE IDENTIFIER ON L_PARENTHESIS boolean_expression COMMA boolean_expression R_PARENTHESIS block  */
#line 287 "parser.y"
    { (yyval.nodePtr) =  makeDrive((yyvsp[-8].stringValue), (yyvsp[-7].stringValue), (yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1520 "parser.tab.c"
    break;

  case 20: /* play_until: PLAY_UNTIL boolean_expression block  */
#line 291 "parser.y"
                                                { (yyval.nodePtr) = makePlayUntil((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr)); }
#line 1526 "parser.tab.c"
    break;

  case 21: /* when_conditional: WHEN boolean_expression THEN block  */
#line 294 "parser.y"
                                                     { (yyval.nodePtr) = makeWhenConditionalWithOneBlock((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1532 "parser.tab.c"
    break;

  case 22: /* when_conditional: WHEN boolean_expression THEN block OTHERWISE block  */
#line 295 "parser.y"
                                                         { (yyval.nodePtr) = makeWhenConditionalWithTwoBlocks((yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1538 "parser.tab.c"
    break;

  case 23: /* variable_declaration: TYPE IDENTIFIER  */
#line 299 "parser.y"
                                      { (yyval.nodePtr) = makePureVarDeclaration((yyvsp[-1].stringValue), (yyvsp[0].stringValue)); }
#line 1544 "parser.tab.c"
    break;

  case 24: /* variable_declaration: TYPE IDENTIFIER IS general_expression  */
#line 300 "parser.y"
                                            { (yyval.nodePtr) = makeVarDeclarationWithAssignment((yyvsp[-3].stringValue), (yyvsp[-2].stringValue), (yyvsp[0].nodePtr)); }
#line 1550 "parser.tab.c"
    break;

  case 25: /* assignment: IDENTIFIER IS general_expression  */
#line 304 "parser.y"
                                             { (yyval.nodePtr) = makeAssignment((yyvsp[-2].stringValue), (yyvsp[0].nodePtr)); }
#line 1556 "parser.tab.c"
    break;

  case 26: /* assignment: IDENTIFIER L_PARENTHESIS R_PARENTHESIS  */
#line 305 "parser.y"
                                             { (yyval.nodePtr) = makeFunctionCallWithoutArgs((yyvsp[-2].stringValue)); }
#line 1562 "parser.tab.c"
    break;

  case 27: /* assignment: IDENTIFIER L_PARENTHESIS call_arguments R_PARENTHESIS  */
#line 306 "parser.y"
                                                            { (yyval.nodePtr) = makeFunctionCallWithArgs((yyvsp[-3].stringValue), (yyvsp[-1].nodePtr)); }
#line 1568 "parser.tab.c"
    break;

  case 28: /* assignment: IDENTIFIER DOT POSITION IS boolean_expression  */
#line 307 "parser.y"
                                                    { (yyval.nodePtr) = makePlayPositionAssignment((yyvsp[-4].stringValue), (yyvsp[-2].stringValue), (yyvsp[0].nodePtr)); }
#line 1574 "parser.tab.c"
    break;

  case 29: /* call_arguments: general_expression  */
#line 311 "parser.y"
                                   { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1580 "parser.tab.c"
    break;

  case 30: /* call_arguments: call_arguments COMMA general_expression  */
#line 312 "parser.y"
                                              { (yyvsp[-2].nodePtr)->children.emplace_back((yyvsp[0].nodePtr)); }
#line 1586 "parser.tab.c"
    break;

  case 31: /* call: CALL L_PARENTHESIS general_expression R_PARENTHESIS  */
#line 316 "parser.y"
                                                          { (yyval.nodePtr) = makeCall((yyvsp[-1].nodePtr)); }
#line 1592 "parser.tab.c"
    break;

  case 32: /* func_statements: func_statement  */
#line 322 "parser.y"
                                { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1598 "parser.tab.c"
    break;

  case 33: /* func_statements: func_statements func_statement  */
#line 323 "parser.y"
                                      { (yyvsp[-1].nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1604 "parser.tab.c"
    break;

  case 34: /* func_statement: BREAK_LINE  */
#line 327 "parser.y"
                           { (yyval.nodePtr) = makeNoOp(); }
#line 1610 "parser.tab.c"
    break;

  case 42: /* func_block: L_BRACKET R_BRACKET  */
#line 338 "parser.y"
                                { (yyval.nodePtr) = makeNoOp(); }
#line 1616 "parser.tab.c"
    break;

  case 43: /* func_block: L_BRACKET func_statements R_BRACKET  */
#line 339 "parser.y"
                                          { (yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1622 "parser.tab.c"
    break;

  case 44: /* result: RESULT general_expression  */
#line 343 "parser.y"
                                  { (yyval.nodePtr) = makeResult((yyvsp[0].nodePtr)); }
#line 1628 "parser.tab.c"
    break;

  case 45: /* func_drive_loop: DRIVE TYPE IDENTIFIER ON L_PARENTHESIS boolean_expression COMMA boolean_expression R_PARENTHESIS func_block  */
#line 347 "parser.y"
    { (yyval.nodePtr) =  makeDrive((yyvsp[-8].stringValue), (yyvsp[-7].stringValue), (yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1634 "parser.tab.c"
    break;

  case 46: /* func_play_until: PLAY_UNTIL boolean_expression func_block  */
#line 352 "parser.y"
                                                          { (yyval.nodePtr) = makePlayUntil((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr)); }
#line 1640 "parser.tab.c"
    break;

  case 47: /* func_when_conditional: WHEN boolean_expression THEN func_block  */
#line 356 "parser.y"
                                                               { (yyval.nodePtr) = makeWhenConditionalWithOneBlock((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1646 "parser.tab.c"
    break;

  case 48: /* func_when_conditional: WHEN boolean_expression THEN func_block OTHERWISE func_block  */
#line 357 "parser.y"
                                                                   { (yyval.nodePtr) = makeWhenConditionalWithTwoBlocks((yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1652 "parser.tab.c"
    break;

  case 49: /* general_expression: boolean_expression  */
#line 365 "parser.y"
                                       { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1658 "parser.tab.c"
    break;

  case 50: /* general_expression: play_expression  */
#line 366 "parser.y"
                      { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1664 "parser.tab.c"
    break;

  case 51: /* play_expression: L_BRACKET R_BRACKET  */
#line 370 "parser.y"
                                     { (yyval.nodePtr) = makeEmptyPlay(); }
#line 1670 "parser.tab.c"
    break;

  case 52: /* play_expression: L_BRACKET play_arguments R_BRACKET  */
#line 371 "parser.y"
                                         { (yyval.nodePtr) = makePlayWithArguments((yyvsp[-1].nodePtr)); }
#line 1676 "parser.tab.c"
    break;

  case 53: /* play_arguments: POSITION COLON boolean_expression  */
#line 374 "parser.y"
                                                  { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(makeAssignment((yyvsp[-2].stringValue), (yyvsp[0].nodePtr))); }
#line 1682 "parser.tab.c"
    break;

  case 54: /* play_arguments: play_arguments COMMA POSITION COLON boolean_expression  */
#line 375 "parser.y"
                                                             { (yyval.nodePtr)->children.emplace_back(makeAssignment((yyvsp[-2].stringValue), (yyvsp[0].nodePtr))); }
#line 1688 "parser.tab.c"
    break;

  case 55: /* boolean_expression: boolean_expression OR boolean_term  */
#line 379 "parser.y"
                                                       { (yyval.nodePtr)= makeBinOp((int) BinOperation::OR, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1694 "parser.tab.c"
    break;

  case 56: /* boolean_expression: boolean_term  */
#line 380 "parser.y"
                   { (yyval.nodePtr)= (yyvsp[0].nodePtr); }
#line 1700 "parser.tab.c"
    break;

  case 57: /* boolean_term: boolean_term AND relative_expression  */
#line 384 "parser.y"
                                                   { (yyval.nodePtr)= makeBinOp((int) BinOperation::AND, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1706 "parser.tab.c"
    break;

  case 58: /* boolean_term: relative_expression  */
#line 385 "parser.y"
                          { (yyval.nodePtr)= (yyvsp[0].nodePtr); }
#line 1712 "parser.tab.c"
    break;

  case 59: /* relative_expression: relative_expression EQUALS expression  */
#line 389 "parser.y"
                                                           { (yyval.nodePtr) = makeBinOp((int) BinOperation::EQUALS, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1718 "parser.tab.c"
    break;

  case 60: /* relative_expression: relative_expression GREATER_THAN expression  */
#line 390 "parser.y"
                                                  { (yyval.nodePtr) = makeBinOp((int) BinOperation::GREATER_THAN, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1724 "parser.tab.c"
    break;

  case 61: /* relative_expression: relative_expression LESSER_THAN expression  */
#line 391 "parser.y"
                                                 { (yyval.nodePtr) = makeBinOp((int) BinOperation::LESSER_THAN, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1730 "parser.tab.c"
    break;

  case 62: /* relative_expression: expression  */
#line 392 "parser.y"
                 { (yyval.nodePtr)= (yyvsp[0].nodePtr); }
#line 1736 "parser.tab.c"
    break;

  case 63: /* expression: expression PLUS term  */
#line 396 "parser.y"
                                 { (yyval.nodePtr) = makeBinOp((int) BinOperation::PLUS, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1742 "parser.tab.c"
    break;

  case 64: /* expression: expression MINUS term  */
#line 397 "parser.y"
                                  { (yyval.nodePtr) = makeBinOp((int) BinOperation::MINUS, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1748 "parser.tab.c"
    break;

  case 65: /* expression: term  */
#line 398 "parser.y"
                 { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1754 "parser.tab.c"
    break;

  case 66: /* term: term TIMES factor  */
#line 402 "parser.y"
                        { (yyval.nodePtr) = makeBinOp((int) BinOperation::TIMES, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1760 "parser.tab.c"
    break;

  case 67: /* term: term DIVIDE factor  */
#line 403 "parser.y"
                         { (yyval.nodePtr) = makeBinOp((int) BinOperation::DIVIDE, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1766 "parser.tab.c"
    break;

  case 68: /* term: factor  */
#line 404 "parser.y"
             { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1772 "parser.tab.c"
    break;

  case 69: /* factor: NUMBER  */
#line 409 "parser.y"
               { (yyval.nodePtr)= makeNumber((yyvsp[0].number)); }
#line 1778 "parser.tab.c"
    break;

  case 70: /* factor: L_PARENTHESIS boolean_expression R_PARENTHESIS  */
#line 410 "parser.y"
                                                     {(yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1784 "parser.tab.c"
    break;

  case 71: /* factor: PLUS factor  */
#line 411 "parser.y"
                  { (yyval.nodePtr) = makeUnOp((int) UnOperation::PLUS, (yyvsp[0].nodePtr)); }
#line 1790 "parser.tab.c"
    break;

  case 72: /* factor: MINUS factor  */
#line 412 "parser.y"
                   { (yyval.nodePtr) = makeUnOp((int) UnOperation::MINUS, (yyvsp[0].nodePtr));  }
#line 1796 "parser.tab.c"
    break;

  case 73: /* factor: INCREMENT factor  */
#line 413 "parser.y"
                       {(yyval.nodePtr) = makeUnOp((int) UnOperation::INCREMENT, (yyvsp[0].nodePtr)); }
#line 1802 "parser.tab.c"
    break;

  case 74: /* factor: NOT factor  */
#line 414 "parser.y"
                 { (yyval.nodePtr) = makeUnOp((int) UnOperation::NOT, (yyvsp[0].nodePtr));  }
#line 1808 "parser.tab.c"
    break;

  case 75: /* factor: IDENTIFIER  */
#line 415 "parser.y"
                 { (yyval.nodePtr) = makeIdentifier((yyvsp[0].stringValue)); }
#line 1814 "parser.tab.c"
    break;

  case 76: /* factor: IDENTIFIER DOT POSITION  */
#line 416 "parser.y"
                              { (yyval.nodePtr) = makePlayValueIdentifier((yyvsp[-2].stringValue), (yyvsp[0].stringValue)); }
#line 1820 "parser.tab.c"
    break;

  case 77: /* factor: STRING  */
#line 417 "parser.y"
             { (yyval.nodePtr) = makeString((yyvsp[0].stringValue)); }
#line 1826 "parser.tab.c"
    break;

  case 78: /* factor: DOWN  */
#line 418 "parser.y"
           { (yyval.nodePtr) = makeDown((yyvsp[0].stringValue)); }
#line 1832 "parser.tab.c"
    break;

  case 79: /* factor: SIGNAL L_PARENTHESIS R_PARENTHESIS  */
#line 419 "parser.y"
                                         { (yyval.nodePtr) = makeSignal(); }
#line 1838 "parser.tab.c"
    break;

  case 80: /* factor: IDENTIFIER L_PARENTHESIS R_PARENTHESIS  */
#line 420 "parser.y"
                                             { (yyval.nodePtr) = makeFunctionCallWithoutArgs((yyvsp[-2].stringValue)); }
#line 1844 "parser.tab.c"
    break;

  case 81: /* factor: IDENTIFIER L_PARENTHESIS call_arguments R_PARENTHESIS  */
#line 421 "parser.y"
                                                            { (yyval.nodePtr) = makeFunctionCallWithArgs((yyvsp[-3].stringValue), (yyvsp[-1].nodePtr)); }
#line 1850 "parser.tab.c"
    break;


#line 1854 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 424 "parser.y"

