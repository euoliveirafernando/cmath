#ifndef _token_h_
#define _token_h_

enum token {
    #include "token"
};

typedef enum token token;

#define primary_expr(x) x == token_integer_literal || x == token_floating_point ||      \
                        x == token_character_constant || x == token_string_literal ||   \
                        x == token_euler || x == token_complex || x == token_pi
#define post_expr(x)    x == '(' || x == '[' || x == '.'
#define pow_expr(x)     x == '^' || x == token_rad || x == token_log
#define prod_expr(x)    x == '*' || x == '/' || x == '%'
#define sum_expr(x)     x == '+' || x == '-'
#define rel_expr(x)     x == '<' || x == '>' || x == token_less_equal || x == token_greater_equal
#define rel_eq_expr(x)  x == token_equal || x == token_not_equal
#define is_op(x)        x >= var && x <= store

#endif