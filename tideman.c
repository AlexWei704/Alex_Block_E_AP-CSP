#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define MAX 9

int preferences[MAX][MAX];
bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
} pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair temp[0];
int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool iscycle(int i, int j);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}
// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}
// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {

        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int one_w = pairs[j].winner;
            int one_l = pairs[j].loser;

            int mov1 = preferences[one_w][one_l] - preferences[one_l][one_w]; // margin of victory 1

            int two_w = pairs[j + 1].winner;
            int two_l = pairs[j + 1].loser;

            int mov2 = preferences[two_w][two_l] - preferences[two_l][two_w]; // margin of victory 2

            if (mov1 < mov2)
            {
                temp[0] = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp[0];
            }
        }
    }
    return;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        locked[w][l] = true;
        if (iscycle(w, l) == true)
        {
            locked[w][l] = false;
        }
    }
    return;
}
bool iscycle(int i, int j)
{
    if (i == j)
    {
        return true;
    }
    for (int k = 0; k < candidate_count; k++)
    {
        if (locked[j][k] == true)
        {
            if (iscycle(i, k))
            {
                return true;
            }
        }
    }

    return false;
}
// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < MAX; i++)
    {
        bool f_winner = true;
        for (int j = 0; j < MAX; j++)
        {
            if (locked[j][i] == true)
            {
                f_winner = false;
                break;
            }
        }
        if (f_winner == true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
