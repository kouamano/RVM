/*************************************************/
/*          RVM - Region Vector Machine          */
/* Copyright (c) 2005 AMANO Kou                  */
/* National Institute of Agrobiological Scences  */
/* School of Libarary and Information Science    */
/* University of Tsukuba                         */
/*                           kamano@affrc.go.jp  */
/*************************************************/

/* define.h */

/* define statement */

#define PRINT_FORMAT 1	/* MATHEMATICA:1, LIST:2, PLANE:4 */

#define SHORT_LEN_STR 4
#define MAX_LEN_STR 1024
#define MAX_LEN_FILE_NAME 2048
#define RATIO_SIZE_EXPAND 30
#define MAX_CLUSTER 2147483647
#define MIN_CLUSTER 1
#define MAX_MEMBER 4096
#define DEFAULT_LOOP 0
#define DEFAULT_RATE 0.3
#define PLANE_OFS " "
#define LIST_OFS " "
#define MATH_OFS ","
#define LIST_BRKT_START "("
#define LIST_BRKT_END ")"
#define MATH_BRKT_START "{"
#define MATH_BRKT_END "}"
#define LIST_NULL "nil"
#define MATH_NULL "Null"

#if PRINT_FORMAT == 1
#define BRKT_START "{"
#define BRKT_END "}"
#define CAP_BRKT_START "\""
#define CAP_BRKT_END "\""
#define OFS ","
#define OLS "\n"
#define NULL_ELEMENT "Null"
#elif PRINT_FORMAT == 2
#define BRKT_START "("
#define BRKT_END ")"
#define CAP_BRKT_START "\""
#define CAP_BRKT_END "\""
#define OFS " "
#define OLS "\n"
#define NULL_ELEMENT "nil"
#elif PRINT_FORMAT == 4
#define BRKT_START " "
#define BRKT_END " "
#define CAP_BRKT_START "\""
#define CAP_BRKT_END "\""
#define OFS " "
#define OLS "\n"
#define NULL_ELEMENT "_"
#else
#define BRKT_START " "
#define BRKT_END " "
#define CAP_BRKT_START "\""
#define CAP_BRKT_END "\""
#define OFS " "
#define OLS "\n"
#define NULL_ELEMENT " "
#endif
