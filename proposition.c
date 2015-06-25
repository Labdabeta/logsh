#include <stdlib.h>
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
     
int proposition_print(const Proposition me, char *buffer, size_t size)
{
    int r,l;
    const PropositionHANDLE this = me;
    if (!this || !buffer || !size)return 0;
    *buffer = '(';
    l=proposition_print(this->left,buffer+1,size-1);
    if (size-l > 1)
        buffer[l+1]=this->val;
    else
        return l+1;
    r=proposition_print(this->right,buffer+(l+2),size-l-2);
    if (size-l-r > 2)
        buffer[l+r+2]=')';
    else
        return l+r+2;
    return l+r+3;
}