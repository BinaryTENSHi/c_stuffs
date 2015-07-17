#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define CROSSOVER_RATE   0.7
#define MUTATION_RATE    0.001
#define POP_SIZE         100

#define RANDOM_NUM       ((float)rand()/RAND_MAX)

#define GENE_COUNT 16

struct chromo {
    float fitness;
    char genes[GENE_COUNT];
};

enum operator {
    op_plus = 10,
    op_minus = 11,
    op_mul = 12,
    op_div = 13
};

struct chromo _chromos[POP_SIZE];

int _target;

void init_chromos(void);

void random_genes(char *arr);

void eval_chromo(struct chromo *chromo);

int calculate_chromo(struct chromo *chromo);

int clean_genes(char in[8], char out[8]);

void print_chromo(struct chromo *chromo);

void print_genes(char genes[8], int len);

void generation_roulette(int fitness, char out[16]);

void crossover(char left[16], char right[16]);

void mutate(char genes[16]);

int main(void) {
    printf("Genetic Calculator\n");
    _target = 42;
    printf("Please enter a target number: ");
    scanf("%i", &_target);

    getchar();
    if (_target == 0)
        return 1;

    printf("Entered: %i\n", _target);
    init_chromos();

    int generation = 1;
    while (true) {
        ++generation;
        float total_fitness = 0;

        for (int i = 0; i < POP_SIZE; ++i) {
            struct chromo *chromo = &_chromos[i];
            eval_chromo(chromo);

            total_fitness += chromo->fitness;

            if (chromo->fitness >= 999) {
                printf("Found solution in generation %i.\n", generation);
                print_chromo(chromo);
                getchar();
                return 0;
            }
        }

        struct chromo new_pop[POP_SIZE];
        int j = 0;
        while (j < POP_SIZE) {
            char parent_one[GENE_COUNT];
            char parent_two[GENE_COUNT];

            generation_roulette(total_fitness, parent_one);
            generation_roulette(total_fitness, parent_two);

            crossover(parent_one, parent_two);

            mutate(parent_one);
            mutate(parent_two);

            new_pop[j].fitness = 0;
            memcpy(new_pop[j++].genes, parent_one, sizeof(parent_one));

            new_pop[j].fitness = 0;
            memcpy(new_pop[j++].genes, parent_two, sizeof(parent_two));
        }

        memcpy(_chromos, new_pop, sizeof(_chromos));
    }
}

void mutate(char genes[GENE_COUNT]) {
    for (int i = 0; i < GENE_COUNT; ++i) {
        if (RANDOM_NUM < MUTATION_RATE) {
            int x = (int) (RANDOM_NUM * 4);
            char gene = genes[i];
            gene ^= 1 << x;
            genes[i] = gene;
        }
    }
}

void crossover(char left[16], char right[16]) {
    if (RANDOM_NUM < CROSSOVER_RATE) {
        int index = (int) (RANDOM_NUM * GENE_COUNT);
        for (int i = index; i < GENE_COUNT; ++i) {
            left[i] ^= right[i];
            right[i] ^= left[i];
            left[i] ^= right[i];
        }
    }
}

void generation_roulette(int total_fitness, char out[GENE_COUNT]) {
    float slice = (float) (RANDOM_NUM * total_fitness);
    float fitness = 0.0f;

    for (int i = 0; i < POP_SIZE; i++) {
        struct chromo *chromo = &_chromos[i];
        fitness += chromo->fitness;

        if (fitness >= slice) {
            for (int j = 0; j < GENE_COUNT; ++j) {
                out[j] = chromo->genes[j];
            }
            return;
        }
    }
}

void print_chromo(struct chromo *chromo) {
    printf("Chromosome ({%.2f}): ", chromo->fitness);
    char cleaned_genes[GENE_COUNT];
    int len = clean_genes(chromo->genes, cleaned_genes);
    for (int i = 0; i < len; ++i) {
        char bit = cleaned_genes[i];
        switch (bit) {
            case op_plus:
                bit = '+';
                break;
            case op_minus:
                bit = '-';
                break;
            case op_mul:
                bit = '*';
                break;
            case op_div:
                bit = '+';
                break;
            default:
                bit = (char) (48 + bit);
        }
        printf("%c ", bit);
    }
}

void eval_chromo(struct chromo *chromo) {
    int val = calculate_chromo(chromo);
    if (val == _target) {
        chromo->fitness = 999;
    } else {
        chromo->fitness = (float) (1.0 / (_target - val));
    }
}

int calculate_chromo(struct chromo *chromo) {
    int val = 0;
    char cleaned_genes[GENE_COUNT];
    int len = clean_genes(chromo->genes, cleaned_genes);

    for (int i = 0; i < len; ++i) {
        int gene = cleaned_genes[i];

        if (i == 0) {
            val = gene;
        } else {
            switch (gene) {
                case op_plus:
                    val += cleaned_genes[++i];
                    break;
                case op_minus:
                    val -= cleaned_genes[++i];
                    break;
                case op_mul:
                    val *= cleaned_genes[++i];
                    break;
                case op_div: {
                    char d = cleaned_genes[++i];
                    if (d == 0) {
                        val += d;
                    } else {
                        val /= d;
                    }
                    break;
                }
                default:
                    printf("uwot");
            }
        }
    }

    return val;
}

void print_genes(char genes[8], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%2i:", genes[i]);
    }
    printf("\n");
}

int clean_genes(char in[GENE_COUNT], char out[GENE_COUNT]) {
    bool req_operator = false;
    int last = 0;
    for (int i = 0; i < GENE_COUNT; ++i) {
        char gene = in[i];

        if (req_operator) {
            if (gene > 9 && gene < 14) {
                out[last++] = gene;
                req_operator = false;
            }
        }
        else {
            if (gene >= 0 && gene < 10) {
                out[last++] = gene;
                req_operator = true;
            }
        }
    }

    if (!req_operator) {
        out[last] = 0;
        --last;
    }

    return last;
}

void init_chromos(void) {
    srand((unsigned int) time(NULL));
    for (int i = 0; i < POP_SIZE; ++i) {
        _chromos[i].fitness = 0.0;
        random_genes(_chromos[i].genes);
    }
}

void random_genes(char *arr) {
    for (int i = 0; i < GENE_COUNT; ++i) {
        arr[i] = (char) (rand() % 14);
    }
}