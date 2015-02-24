/*
   automata.c: implements a one-dimensional cellular automaton.
   Author: Philip Cho (Hyunsu.Cho@trincoll.edu)
   Assumptions
   - The input is well-formatted.
   - Each input string is no more than 50 characters.
   - The rule set is an integer between 0 and 255.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50
#define TABLE_WIDTH 8

typedef char *RuleTable;

char *cellular_automata(const char *init_str, int rule_set, int num_gen);
RuleTable generate_rule_table(int rule_set);
char apply_rule_table(RuleTable rt, const char *str, int k, int str_length);
void delete_rule_table(RuleTable rt);
int binary_string_to_int(char c1, char c2, char c3);

int main(void)
{
    int num_cases, num_gen, rule_set;
    int i;

    char init_str[MAX_LENGTH + 1] = {0};
    char *final_str;

    scanf("%d", &num_cases);
    
    for (i = 0; i < num_cases; i++) {
        scanf("%s %d %d", init_str, &rule_set, &num_gen);
        final_str = cellular_automata(init_str, rule_set, num_gen);
        printf("%s\n", final_str);
        free(final_str);
    }

    return 0;
}

char *cellular_automata(const char *init_str, int rule_set, int num_gen)
/* generates a cellular automaton from a given rule set and applies it
   on a given input string over a specified number of generations.
   This function returns a pointer to a newly allocated string that contains
   the resulting string; the input string is not in any way modified. */
{
    char *str; // string of current generation
    char *new_str; // string of next generation
    int len; // length of str
    int i, k;
    RuleTable rt;
    
    len = strlen(init_str);
    str = (char *)calloc(len + 1, sizeof(char));
    new_str = (char *)calloc(len + 1, sizeof(char));
    rt = generate_rule_table(rule_set);

    strcpy(str, init_str);

    for (i = 0; i < num_gen; i++) {
        for (k = 0; k < len; k++)
            new_str[k] = apply_rule_table(rt, str, k, len);
        strcpy(str, new_str);
    }

    free(new_str);
    delete_rule_table(rt);

    return str;
}

RuleTable generate_rule_table(int rule_set)
/* generates the 8-entry rule table that corresponds to the rule set as given
   by a 1-byte integer. */
{
    RuleTable rule_table;
    int i;
    
    rule_table = (RuleTable)malloc(TABLE_WIDTH * sizeof(char));
    /* rule_table[i] stores the central character that results from pattern i,
       where i is in decimal depresentation. For example, rule_table[4] stores
       the central character that results from pattern "100". */
    i = 0;
    while (rule_set > 0) {
        rule_table[i] = '0' + rule_set % 2;
        rule_set /= 2;
        i++;
    }

    while (i < TABLE_WIDTH) {
        rule_table[i] = '0';
        i++;
    }

    return rule_table;
}

char apply_rule_table(RuleTable rt, const char *str, int k, int str_length)
/* interprets the given rule table to determine what the new string would have
   at its k-th position and returns that character. */
{
    int rule_idx;

    // do a wrap-around as necessary.
    if (k == 0)
        rule_idx = binary_string_to_int(str[str_length - 1], str[0], str[1]);
    else if (k == str_length - 1)
        rule_idx = binary_string_to_int(str[str_length - 2],
                                        str[str_length - 1], str[0]);
    else
        rule_idx = binary_string_to_int(str[k - 1], str[k], str[k + 1]);

    return rt[rule_idx];
}

void delete_rule_table(RuleTable rt)
/* deletes the rule table from memory. */
{
    free(rt);
}

int binary_string_to_int(char c1, char c2, char c3)
/* converts a 3-digit binary string c into an integer. c1 gives the first
   character in c, c2 gives the second, and c3 gives the third. */
{
    return (c1 - '0') * 4 + (c2 - '0') * 2 + (c3 - '0');
}
