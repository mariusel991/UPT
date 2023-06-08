#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Use malloc and realloc 
// FootballTeam *addPlayer(FootballTeam *team, FootballPlayer *player)
// FootballChampionship *addTeam(FootballChampionship *footballChampionship, FootballTeam *footballTeam)

typedef struct FootballPlayer
{
    char *name;
    double salary;
} FootballPlayer;

typedef struct FootballTeam
{
    FootballPlayer **footbaballPlayers;
    char *name;
    int currentNumberOfPlayers;
    int currentAllocatedMemory;
} FootbaballTeam;

typedef struct FootballChampionship
{
    FootbaballTeam **footballTeams;
    char *name;
    int currentNumbersOfTeams;
    int currentAllocatedMemory;
} FootballChampionship;

FootballPlayer *searchFootballPlayerInFootballTeamByName(char *name, FootbaballTeam *footbalTeam)
{
    for (int i = 0; i < footbalTeam->currentNumberOfPlayers; ++i)
    {
        if (strcmp(footbalTeam->footbaballPlayers[i]->name, name) == 0)
        {
            return footbalTeam->footbaballPlayers[i];
        }
    }

    return NULL;
}

FootballPlayer *searchFootballPlayerInFootballChampionship(char *name, FootballChampionship *footballChampionship)
{
    for (int i = 0; i < footballChampionship->currentNumbersOfTeams; ++i)
    {
        FootbaballTeam *footballTeam = footballChampionship->footballTeams[i];

        FootballPlayer *footballPlayer = searchFootballPlayerInFootballTeamByName(name, footballTeam);
        if (footballPlayer != NULL)
        {
            return footballPlayer;
        }
    }

    return NULL;
}

int main()
{

    return 0;
}
