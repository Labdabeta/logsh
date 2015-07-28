#include <stdlib.h>
#include <ctype.h>
#include "proposition.h"

typedef struct PropositionTAG {
    char val;
    struct PropositionTAG *left;
    struct PropositionTAG *right;
}*PropositionHANDLE;

Proposition proposition_new(void)
{
    PropositionHANDLE ret = malloc(sizeof(struct PropositionTAG));
    ret->val = 0;
    ret->left = ret->right = 0;
    return ret;
}

Proposition proposition_make(char ch)
{
    PropositionHANDLE ret = malloc(sizeof(struct PropositionTAG));
    ret->val = ch;
    ret->left = ret->right = 0;
    return ret;
}

void proposition_delete(Proposition me)
{
    PropositionHANDLE this = me;
    if (!this)return;
    if (this->left) proposition_delete(this->left);
    if (this->right) proposition_delete(this->right);
    free(this);
}

Proposition proposition_set_value(Proposition me, char val)
{
    PropositionHANDLE this = me;
    if (!this)return 0;
    this->val = val;
    return this;
}

Proposition proposition_set_left(Proposition me, Proposition left)
{
    PropositionHANDLE this = me;
    if (!this)return 0;
    this->left = left;
    return this;
}

Proposition proposition_set_right(Proposition me, Proposition right)
{
    PropositionHANDLE this = me;
    if (!this)return 0;
    this->right = right;
    return this;
}


char proposition_get_value(const Proposition me)
{
    const PropositionHANDLE this = me;
    if (!this)return 0;
    return this->val;
}

Proposition proposition_get_left(const Proposition me)
{
    const PropositionHANDLE this = me;
    if (!this)return 0;
    return this->left;
}

Proposition proposition_get_right(const Proposition me)
{
    const PropositionHANDLE this = me;
    if (!this)return 0;
    return this->right;
}

int precedence(char a, char b) //compare with zero for a ? b
{
    int aprec,bprec;
    switch (a) {
        case '=':aprec = 1;break;
        case '>':case '-':aprec = 2;break;
        case '|':aprec = 3;break;
        case '&':aprec = 4;break;
        case '!':aprec = 5;break;
        default:aprec = 10;
    }
    switch (b) {
        case '=':bprec = 1;break;
        case '>':case '-':bprec = 2;break;
        case '|':bprec = 3;break;
        case '&':bprec = 4;break;
        case '!':bprec = 5;break;
        default:bprec = 10;
    }
    return aprec-bprec;
}
     
int proposition_format(const Proposition me, char *buffer, size_t size)
{
    char *end;
    const PropositionHANDLE this = me;
    if (!this || !buffer || !size)return 0;
    end = buffer + size;

#define PRINT(X) do {\
    if (buffer < end) {\
        *buffer++ = (X);\
    } else {\
        *buffer = '\0';\
        return size;\
    } } while (0)

    //Print left expression
    if (this->left && precedence(this->left->val,this->val) < 0) {
        PRINT('(');
        buffer += proposition_format(this->left, buffer, end-buffer);
        PRINT(')');
    } else {
        buffer += proposition_format(this->left, buffer, end-buffer);
    }

    //Print value
    PRINT(this->val);

    //Print right expression
    if (this->right && precedence(this->right->val,this->val) < 0) {
        PRINT('(');
        buffer += proposition_format(this->right, buffer, end-buffer);
        PRINT(')');
    } else {
        buffer += proposition_format(this->right, buffer, end-buffer);
    }
#undef PRINT
    
    *buffer = '\0';
    return buffer + size - end;
}

Proposition proposition_parse(const char *str)
{
    Proposition left=NULL,right=NULL,ret;
    char val = 0;
    while (*str && (!left || !right || !val)) {
        if (isalpha(*str)) {
            if (!left) {
                left = proposition_make(*str);
            } else if (!val) {
                proposition_delete(left);
                return NULL;
            } else {
                right = proposition_make(*str);
            }
        } else if (*str == '(') {
            if (!left) {
                left = proposition_parse(str+1);
            } else if (!val) {
                proposition_delete(left);
                return NULL;
            } else {
                right = proposition_parse(str+1);
            }
        } else {
            if (!left) {
                return NULL;
            } else if (!val) {
                val = *str;
            } else {
                return NULL;
            }
        }
        str++;
    }
    ret = proposition_make(val);
    proposition_set_left(ret,left);
    proposition_set_right(ret,right);
    return ret;
}




