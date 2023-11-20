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

#include <stdio.h>    
#include <stdlib.h>
#include <iostream>
#include <string>

#include "nodes.h"
using namespace std;

int yylex(); 

void yyerror(const char *s) {
    // Define the yyerror function
    fprintf(stderr, "Error: %s\n", s);
}

Node* makeNoOp() {
    return new Number(0, vector<unique_ptr<Node>>());
}

Node* makeSignal() {
    return new Signal(0, vector<unique_ptr<Node>>());
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


#line 231 "parser.tab.c"

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
  YYSYMBOL_SIGNAL = 19,                    /* SIGNAL  */
  YYSYMBOL_CALL = 20,                      /* CALL  */
  YYSYMBOL_WHEN = 21,                      /* WHEN  */
  YYSYMBOL_THEN = 22,                      /* THEN  */
  YYSYMBOL_OTHERWISE = 23,                 /* OTHERWISE  */
  YYSYMBOL_DRIVE = 24,                     /* DRIVE  */
  YYSYMBOL_ON = 25,                        /* ON  */
  YYSYMBOL_PLAY_UNTIL = 26,                /* PLAY_UNTIL  */
  YYSYMBOL_BREAK_LINE = 27,                /* BREAK_LINE  */
  YYSYMBOL_ACTION = 28,                    /* ACTION  */
  YYSYMBOL_L_BRACKET = 29,                 /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 30,                 /* R_BRACKET  */
  YYSYMBOL_RESULT = 31,                    /* RESULT  */
  YYSYMBOL_IDENTIFIER = 32,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 33,                    /* NUMBER  */
  YYSYMBOL_STRING = 34,                    /* STRING  */
  YYSYMBOL_POSITION = 35,                  /* POSITION  */
  YYSYMBOL_DOWN = 36,                      /* DOWN  */
  YYSYMBOL_TYPE = 37,                      /* TYPE  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_statements = 40,                /* statements  */
  YYSYMBOL_statement = 41,                 /* statement  */
  YYSYMBOL_block = 42,                     /* block  */
  YYSYMBOL_result = 43,                    /* result  */
  YYSYMBOL_func_declaration = 44,          /* func_declaration  */
  YYSYMBOL_declaration_arguments = 45,     /* declaration_arguments  */
  YYSYMBOL_drive_loop = 46,                /* drive_loop  */
  YYSYMBOL_play_until = 47,                /* play_until  */
  YYSYMBOL_when_conditional = 48,          /* when_conditional  */
  YYSYMBOL_variable_declaration = 49,      /* variable_declaration  */
  YYSYMBOL_assignment = 50,                /* assignment  */
  YYSYMBOL_call_arguments = 51,            /* call_arguments  */
  YYSYMBOL_call = 52,                      /* call  */
  YYSYMBOL_boolean_expression = 53,        /* boolean_expression  */
  YYSYMBOL_boolean_term = 54,              /* boolean_term  */
  YYSYMBOL_relative_expression = 55,       /* relative_expression  */
  YYSYMBOL_expression = 56,                /* expression  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_factor = 58                     /* factor  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   191,   191,   196,   197,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   211,   212,   215,   217,   219,   223,
     225,   229,   233,   235,   236,   239,   240,   243,   244,   245,
     248,   249,   252,   254,   255,   258,   259,   262,   263,   264,
     265,   268,   269,   270,   273,   274,   275,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289
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
  "COLON", "SIGNAL", "CALL", "WHEN", "THEN", "OTHERWISE", "DRIVE", "ON",
  "PLAY_UNTIL", "BREAK_LINE", "ACTION", "L_BRACKET", "R_BRACKET", "RESULT",
  "IDENTIFIER", "NUMBER", "STRING", "POSITION", "DOWN", "TYPE", "$accept",
  "program", "statements", "statement", "block", "result",
  "func_declaration", "declaration_arguments", "drive_loop", "play_until",
  "when_conditional", "variable_declaration", "assignment",
  "call_arguments", "call", "boolean_expression", "boolean_term",
  "relative_expression", "expression", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-62)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     147,    52,   102,    -8,   102,   -62,     2,   102,     4,    40,
      73,   147,   -62,    47,    48,    49,    50,    51,    54,    55,
      56,   102,   102,   102,   102,   102,   102,    78,    79,   -62,
     -62,   -62,    23,    72,    38,    13,    34,   -62,    58,   -11,
      59,    77,    27,   102,    71,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,     6,   -62,   -62,   -62,    20,
     -62,    81,    61,   102,    67,   102,   102,   102,   102,   102,
     102,   102,   102,    74,   119,   -62,    92,   -62,     5,    77,
      77,   102,   -62,   -62,   -62,   -62,     7,    72,    80,    38,
      13,    13,    13,    34,    34,   -62,   -62,    95,   -62,   133,
      -1,   -62,   102,    77,   -62,    67,   102,   -62,    67,    70,
       8,    77,   -62,    11,   -62,   -62,    67,    76,   102,   -62,
      82,    33,   -62,    67,   -62
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     5,     0,     0,     0,     0,
       0,     2,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    53,    47,
      54,    55,     0,    34,    36,    40,    43,    46,     0,     0,
       0,    16,     0,     0,    25,     1,     4,     6,     7,     8,
       9,    10,    11,    12,    13,     0,    49,    50,    51,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,    28,     0,    30,
      27,     0,    32,    48,    56,    57,     0,    33,    23,    35,
      37,    38,    39,    41,    42,    44,    45,     0,    14,     0,
       0,    29,     0,    26,    58,     0,     0,    15,     0,     0,
       0,    31,    24,     0,    17,    19,     0,     0,     0,    18,
       0,     0,    20,     0,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,   -62,    35,   -10,   -61,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,    53,   -62,    -2,    57,    45,   -14,     0,
     -15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    10,    11,    12,    75,    13,    14,   110,    15,    16,
      17,    18,    19,    78,    20,    79,    33,    34,    35,    36,
      37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    46,    39,    88,    63,    41,   108,    56,    57,    58,
      42,    60,   101,    82,   104,   116,    69,    70,    74,    55,
      43,    63,   102,    59,   102,   117,    63,    83,   118,    38,
      22,    23,    24,    25,    77,    63,   109,    26,    63,    40,
     123,    80,    71,    72,   112,    64,    27,   114,    63,    66,
      67,    68,    90,    91,    92,   119,    95,    96,    21,    28,
      29,    30,   124,    31,    22,    23,    24,    25,    85,    93,
      94,    26,    44,    45,    47,    48,    49,    50,    51,   103,
      27,    52,    53,    54,    61,    62,    65,    81,    84,    46,
      73,    76,    63,    28,    29,    30,    74,    31,   100,    97,
     111,   106,   115,   105,   113,    22,    23,    24,    25,    99,
      89,     0,    26,   120,   122,    86,   121,     0,     0,     0,
      87,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,     0,    31,     1,
       2,     0,     0,     3,     0,     4,     5,     6,     0,    98,
       7,     8,     0,     1,     2,     0,     9,     3,     0,     4,
       5,     6,     0,   107,     7,     8,     0,     1,     2,     0,
       9,     3,     0,     4,     5,     6,     0,     0,     7,     8,
       0,     0,     0,     0,     9
};

static const yytype_int8 yycheck[] =
{
       2,    11,     4,    64,    15,     7,     7,    22,    23,    24,
       6,    26,     7,     7,     7,     7,     3,     4,    29,    21,
      16,    15,    17,    25,    17,    17,    15,     7,    17,    37,
       3,     4,     5,     6,     7,    15,    37,    10,    15,    37,
       7,    43,     8,     9,   105,    22,    19,   108,    15,    11,
      12,    13,    66,    67,    68,   116,    71,    72,     6,    32,
      33,    34,   123,    36,     3,     4,     5,     6,     7,    69,
      70,    10,    32,     0,    27,    27,    27,    27,    27,    81,
      19,    27,    27,    27,     6,     6,    14,    16,     7,    99,
      32,    32,    15,    32,    33,    34,    29,    36,     6,    25,
     102,     6,    32,    23,   106,     3,     4,     5,     6,    74,
      65,    -1,    10,    37,    32,    62,   118,    -1,    -1,    -1,
      63,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    -1,    36,    20,
      21,    -1,    -1,    24,    -1,    26,    27,    28,    -1,    30,
      31,    32,    -1,    20,    21,    -1,    37,    24,    -1,    26,
      27,    28,    -1,    30,    31,    32,    -1,    20,    21,    -1,
      37,    24,    -1,    26,    27,    28,    -1,    -1,    31,    32,
      -1,    -1,    -1,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    21,    24,    26,    27,    28,    31,    32,    37,
      39,    40,    41,    43,    44,    46,    47,    48,    49,    50,
      52,     6,     3,     4,     5,     6,    10,    19,    32,    33,
      34,    36,    53,    54,    55,    56,    57,    58,    37,    53,
      37,    53,     6,    16,    32,     0,    41,    27,    27,    27,
      27,    27,    27,    27,    27,    53,    58,    58,    58,    53,
      58,     6,     6,    15,    22,    14,    11,    12,    13,     3,
       4,     8,     9,    32,    29,    42,    32,     7,    51,    53,
      53,    16,     7,     7,     7,     7,    51,    54,    42,    55,
      56,    56,    56,    57,    57,    58,    58,    25,    30,    40,
       6,     7,    17,    53,     7,    23,     6,    30,     7,    37,
      45,    53,    42,    53,    42,    32,     7,    17,    17,    42,
      37,    53,    32,     7,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    42,    42,    43,    44,    44,    45,
      45,    46,    47,    48,    48,    49,    49,    50,    50,    50,
      51,    51,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    56,    56,    56,    57,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     2,     6,     7,     2,
       4,    10,     3,     4,     6,     2,     4,     3,     3,     4,
       1,     3,     4,     3,     1,     3,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     1,     3,     2,
       2,     2,     2,     1,     1,     1,     3,     3,     4
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
#line 191 "parser.y"
                    { 
    SymbolTable* symbolTable = new SymbolTable();
    (yyvsp[0].nodePtr)->evaluate(*symbolTable); 
}
#line 1369 "parser.tab.c"
    break;

  case 3: /* statements: statement  */
#line 196 "parser.y"
                      { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1375 "parser.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 197 "parser.y"
                            { (yyvsp[-1].nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1381 "parser.tab.c"
    break;

  case 5: /* statement: BREAK_LINE  */
#line 200 "parser.y"
                      { (yyval.nodePtr) = makeNoOp(); }
#line 1387 "parser.tab.c"
    break;

  case 14: /* block: L_BRACKET R_BRACKET  */
#line 211 "parser.y"
                           { (yyval.nodePtr) = makeNoOp(); }
#line 1393 "parser.tab.c"
    break;

  case 15: /* block: L_BRACKET statements R_BRACKET  */
#line 212 "parser.y"
                                     { (yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1399 "parser.tab.c"
    break;

  case 16: /* result: RESULT boolean_expression  */
#line 215 "parser.y"
                                  { (yyval.nodePtr) = makeResult((yyvsp[0].nodePtr)); }
#line 1405 "parser.tab.c"
    break;

  case 17: /* func_declaration: ACTION TYPE IDENTIFIER L_PARENTHESIS R_PARENTHESIS block  */
#line 218 "parser.y"
    { (yyval.nodePtr) = makeFunctionDeclarationWithoutArgs((yyvsp[-4].stringValue), (yyvsp[-3].stringValue), (yyvsp[0].nodePtr)); }
#line 1411 "parser.tab.c"
    break;

  case 18: /* func_declaration: ACTION TYPE IDENTIFIER L_PARENTHESIS declaration_arguments R_PARENTHESIS block  */
#line 220 "parser.y"
    { (yyval.nodePtr) = makeFunctionDeclarationWithArgs((yyvsp[-5].stringValue), (yyvsp[-4].stringValue), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1417 "parser.tab.c"
    break;

  case 19: /* declaration_arguments: TYPE IDENTIFIER  */
#line 224 "parser.y"
    { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>(makePureVarDeclaration((yyvsp[-1].stringValue), (yyvsp[0].stringValue)))); }
#line 1423 "parser.tab.c"
    break;

  case 20: /* declaration_arguments: declaration_arguments COMMA TYPE IDENTIFIER  */
#line 226 "parser.y"
    { (yyvsp[-3].nodePtr)->children.emplace_back(makePureVarDeclaration((yyvsp[-1].stringValue), (yyvsp[0].stringValue))); }
#line 1429 "parser.tab.c"
    break;

  case 21: /* drive_loop: DRIVE TYPE IDENTIFIER ON L_PARENTHESIS boolean_expression COMMA boolean_expression R_PARENTHESIS block  */
#line 230 "parser.y"
    { (yyval.nodePtr) =  makeDrive((yyvsp[-8].stringValue), (yyvsp[-7].stringValue), (yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1435 "parser.tab.c"
    break;

  case 22: /* play_until: PLAY_UNTIL boolean_expression block  */
#line 233 "parser.y"
                                                { (yyval.nodePtr) = makePlayUntil((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr)); }
#line 1441 "parser.tab.c"
    break;

  case 23: /* when_conditional: WHEN boolean_expression THEN block  */
#line 235 "parser.y"
                                                     { (yyval.nodePtr) = makeWhenConditionalWithOneBlock((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1447 "parser.tab.c"
    break;

  case 24: /* when_conditional: WHEN boolean_expression THEN block OTHERWISE block  */
#line 236 "parser.y"
                                                         { (yyval.nodePtr) = makeWhenConditionalWithTwoBlocks((yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1453 "parser.tab.c"
    break;

  case 25: /* variable_declaration: TYPE IDENTIFIER  */
#line 239 "parser.y"
                                      { (yyval.nodePtr) = makePureVarDeclaration((yyvsp[-1].stringValue), (yyvsp[0].stringValue)); }
#line 1459 "parser.tab.c"
    break;

  case 26: /* variable_declaration: TYPE IDENTIFIER IS boolean_expression  */
#line 240 "parser.y"
                                            { (yyval.nodePtr) = makeVarDeclarationWithAssignment((yyvsp[-3].stringValue), (yyvsp[-2].stringValue), (yyvsp[0].nodePtr)); }
#line 1465 "parser.tab.c"
    break;

  case 27: /* assignment: IDENTIFIER IS boolean_expression  */
#line 243 "parser.y"
                                             { (yyval.nodePtr) = makeAssignment((yyvsp[-2].stringValue), (yyvsp[0].nodePtr)); }
#line 1471 "parser.tab.c"
    break;

  case 28: /* assignment: IDENTIFIER L_PARENTHESIS R_PARENTHESIS  */
#line 244 "parser.y"
                                             { (yyval.nodePtr) = makeFunctionCallWithoutArgs((yyvsp[-2].stringValue)); }
#line 1477 "parser.tab.c"
    break;

  case 29: /* assignment: IDENTIFIER L_PARENTHESIS call_arguments R_PARENTHESIS  */
#line 245 "parser.y"
                                                            { (yyval.nodePtr) = makeFunctionCallWithArgs((yyvsp[-3].stringValue), (yyvsp[-1].nodePtr)); }
#line 1483 "parser.tab.c"
    break;

  case 30: /* call_arguments: boolean_expression  */
#line 248 "parser.y"
                                   { (yyval.nodePtr) = makeBlock(); (yyval.nodePtr)->children.emplace_back(unique_ptr<Node>((yyvsp[0].nodePtr))); }
#line 1489 "parser.tab.c"
    break;

  case 31: /* call_arguments: call_arguments COMMA boolean_expression  */
#line 249 "parser.y"
                                              { (yyvsp[-2].nodePtr)->children.emplace_back((yyvsp[0].nodePtr)); }
#line 1495 "parser.tab.c"
    break;

  case 32: /* call: CALL L_PARENTHESIS boolean_expression R_PARENTHESIS  */
#line 252 "parser.y"
                                                          { (yyval.nodePtr) = makeCall((yyvsp[-1].nodePtr)); }
#line 1501 "parser.tab.c"
    break;

  case 33: /* boolean_expression: boolean_expression OR boolean_term  */
#line 254 "parser.y"
                                                       { (yyval.nodePtr)= makeBinOp((int) BinOperation::OR, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1507 "parser.tab.c"
    break;

  case 34: /* boolean_expression: boolean_term  */
#line 255 "parser.y"
                   { (yyval.nodePtr)= (yyvsp[0].nodePtr); }
#line 1513 "parser.tab.c"
    break;

  case 35: /* boolean_term: boolean_term AND relative_expression  */
#line 258 "parser.y"
                                                   { (yyval.nodePtr)= makeBinOp((int) BinOperation::AND, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1519 "parser.tab.c"
    break;

  case 36: /* boolean_term: relative_expression  */
#line 259 "parser.y"
                          { (yyval.nodePtr)= (yyvsp[0].nodePtr); }
#line 1525 "parser.tab.c"
    break;

  case 37: /* relative_expression: relative_expression EQUALS expression  */
#line 262 "parser.y"
                                                           { (yyval.nodePtr) = makeBinOp((int) BinOperation::EQUALS, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1531 "parser.tab.c"
    break;

  case 38: /* relative_expression: relative_expression GREATER_THAN expression  */
#line 263 "parser.y"
                                                  { (yyval.nodePtr) = makeBinOp((int) BinOperation::GREATER_THAN, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1537 "parser.tab.c"
    break;

  case 39: /* relative_expression: relative_expression LESSER_THAN expression  */
#line 264 "parser.y"
                                                 { (yyval.nodePtr) = makeBinOp((int) BinOperation::LESSER_THAN, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1543 "parser.tab.c"
    break;

  case 40: /* relative_expression: expression  */
#line 265 "parser.y"
                 { (yyval.nodePtr)= (yyvsp[0].nodePtr); }
#line 1549 "parser.tab.c"
    break;

  case 41: /* expression: expression PLUS term  */
#line 268 "parser.y"
                                 { (yyval.nodePtr) = makeBinOp((int) BinOperation::PLUS, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1555 "parser.tab.c"
    break;

  case 42: /* expression: expression MINUS term  */
#line 269 "parser.y"
                                  { (yyval.nodePtr) = makeBinOp((int) BinOperation::MINUS, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1561 "parser.tab.c"
    break;

  case 43: /* expression: term  */
#line 270 "parser.y"
                 { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1567 "parser.tab.c"
    break;

  case 44: /* term: term TIMES factor  */
#line 273 "parser.y"
                        { (yyval.nodePtr) = makeBinOp((int) BinOperation::TIMES, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1573 "parser.tab.c"
    break;

  case 45: /* term: term DIVIDE factor  */
#line 274 "parser.y"
                         { (yyval.nodePtr) = makeBinOp((int) BinOperation::DIVIDE, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr)); }
#line 1579 "parser.tab.c"
    break;

  case 46: /* term: factor  */
#line 275 "parser.y"
             { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 1585 "parser.tab.c"
    break;

  case 47: /* factor: NUMBER  */
#line 278 "parser.y"
               { (yyval.nodePtr)= makeNumber((yyvsp[0].number)); }
#line 1591 "parser.tab.c"
    break;

  case 48: /* factor: L_PARENTHESIS boolean_expression R_PARENTHESIS  */
#line 279 "parser.y"
                                                     {(yyval.nodePtr) = (yyvsp[-1].nodePtr); }
#line 1597 "parser.tab.c"
    break;

  case 49: /* factor: PLUS factor  */
#line 280 "parser.y"
                  { (yyval.nodePtr) = makeUnOp((int) UnOperation::PLUS, (yyvsp[0].nodePtr)); }
#line 1603 "parser.tab.c"
    break;

  case 50: /* factor: MINUS factor  */
#line 281 "parser.y"
                   { (yyval.nodePtr) = makeUnOp((int) UnOperation::MINUS, (yyvsp[0].nodePtr));  }
#line 1609 "parser.tab.c"
    break;

  case 51: /* factor: INCREMENT factor  */
#line 282 "parser.y"
                       {(yyval.nodePtr) = makeUnOp((int) UnOperation::INCREMENT, (yyvsp[0].nodePtr)); }
#line 1615 "parser.tab.c"
    break;

  case 52: /* factor: NOT factor  */
#line 283 "parser.y"
                 { (yyval.nodePtr) = makeUnOp((int) UnOperation::NOT, (yyvsp[0].nodePtr));  }
#line 1621 "parser.tab.c"
    break;

  case 53: /* factor: IDENTIFIER  */
#line 284 "parser.y"
                 { (yyval.nodePtr) = makeIdentifier((yyvsp[0].stringValue)); }
#line 1627 "parser.tab.c"
    break;

  case 54: /* factor: STRING  */
#line 285 "parser.y"
             { (yyval.nodePtr) = makeString((yyvsp[0].stringValue)); }
#line 1633 "parser.tab.c"
    break;

  case 55: /* factor: DOWN  */
#line 286 "parser.y"
           { (yyval.nodePtr) = makeString((yyvsp[0].stringValue)); }
#line 1639 "parser.tab.c"
    break;

  case 56: /* factor: SIGNAL L_PARENTHESIS R_PARENTHESIS  */
#line 287 "parser.y"
                                         { (yyval.nodePtr) = makeSignal(); }
#line 1645 "parser.tab.c"
    break;

  case 57: /* factor: IDENTIFIER L_PARENTHESIS R_PARENTHESIS  */
#line 288 "parser.y"
                                             { (yyval.nodePtr) = makeFunctionCallWithoutArgs((yyvsp[-2].stringValue)); }
#line 1651 "parser.tab.c"
    break;

  case 58: /* factor: IDENTIFIER L_PARENTHESIS call_arguments R_PARENTHESIS  */
#line 289 "parser.y"
                                                            { (yyval.nodePtr) = makeFunctionCallWithArgs((yyvsp[-3].stringValue), (yyvsp[-1].nodePtr)); }
#line 1657 "parser.tab.c"
    break;


#line 1661 "parser.tab.c"

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

#line 292 "parser.y"

