#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Enunt

Se considera un campionat de fotbal. Campionatul de fotbal contine un LinkedList(lista simplu inlantuita) de echipe de fotbal.
O echipa de fotbal contine un ArrayList de jucatori.
Un jucator este caracterizat de nume si salar.
Echipa de fotbal si campionatul contin adional cate un nume. Acesta va fi considerat a fi unic.
Sa se implementeze urmatoarele metode:

adauga un jucator in interiorul echipei de fotbal
addPlayer(FootballTeam *team, FootballPlayer *player)


printFootballTeam(FootballTeam *team) // se vor printa informatiile despre echipa(numele echipei + informatiile despre jucatori)

root desemneaza nodul radacina al LinkedList-ului. newTeam este echipa ce va urma sa fie adaugata in lista
addTeam(FootballTeam *root, FootballTeam *newTeam) //


acelasi enunt ca ma sus, doar ca vom elimina o echipa
removeTeam(FootballTeam *root, FootballTeam *teamToRemove)


footballChampionship contine nodul radacina al liste inlantuite de echipe. Se va cauta echipa dupa nume, iar in momentul in care a fost gasita, se va
va adauga jucatorul in arraylist-ul acesteia
addFootballPlayer(FootballChampionship *footballChampionship, char *teamName, FootballPlayer *footballPlayer)


va itera pe lista de echipa si va chema metoda printFootballTeam pentru afisare
printFootballChampionship(FootballChampionship *footballChampionship)

*/

typedef struct FootballPlayer {
    char *name;
    double salary;

} FootballPlayer;

typedef struct FootballTeam {

    FootballPlayer **footballPlayers;
    char *name;
    int size;
    int maxSize;

    struct FootballTeam *next;

} FootballTeam;

typedef struct FootballChampionship {

    char *name;
    // this is the root of the linkedlist of football team
    FootballTeam *footballTeam;

} FootballChampionship;

// create new football team
FootballTeam *createArrayList() {

    FootballTeam *team = (FootballTeam *) malloc(sizeof(FootballTeam));
    if (NULL == team) {
        return NULL;
    }
    team->size = 0;
    team->maxSize = 10;
    team->name = NULL;
    team->footballPlayers = (FootballPlayer **) malloc(team->maxSize * sizeof(FootballPlayer*));
    if (NULL == team->footballPlayers) {
        free(team);
        return NULL;
    }
    team->footballPlayers[0] = NULL;
    team->next = NULL;

    return team;

}

FootballTeam *resizeArray(FootballTeam *list) {
    list->maxSize = list->maxSize * 2;
    // store in temp variable and check for NULL
    list->footballPlayers = (FootballPlayer **) realloc(list->footballPlayers, list->maxSize * sizeof(FootballPlayer*));
    if (NULL == list->footballPlayers) {
        free(list);
        return NULL;
    }

    return list;
}

FootballTeam *addPlayer(FootballTeam *team, FootballPlayer *player) {

    if (team->size == team->maxSize) {
        team = resizeArray(team);
        if (NULL == team) {
            return NULL;
        }
    }

    team->footballPlayers[team->size] = player;
    ++team->size;

    return team;

}

void printArrayList(FootballTeam *team) {

    printf("Team:%s\n", team->name);
    for (int i = 0; i < team->size; ++i) {
        printf("Player:\nName=%s\nsalary=%lf\n\n", team->footballPlayers[i]->name,
               team->footballPlayers[i]->salary);
    }

}

FootballTeam *addTeam(FootballTeam *root, FootballTeam *newTeam) {

    FootballTeam *iter = root;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = newTeam;

    return root;
}

FootballTeam *removeTeam(FootballTeam *root, FootballTeam *teamToRemove) {

    if (NULL == root || NULL == teamToRemove) {
        return NULL;
    }

    if (strcmp(root->name, teamToRemove->name) == 0) {
        FootballTeam *tmp = root->next;
        free(root);
        root = tmp;
        return root;
    }

    // multiple ways to solve
    FootballTeam *iter = root;
    FootballTeam *prev;
    while (iter != NULL && strcmp(iter->name, teamToRemove->name) != 0) {
        prev = iter;
        iter = iter->next;
    }

    if (NULL == iter) {
        return NULL;
    }

    prev->next = iter->next;
    free(iter);
    iter = NULL;

    return root;

}

FootballTeam *addFootballPlayer(FootballChampionship *footballChampionship, char *teamName, FootballPlayer *footballPlayer) {

    FootballTeam *root = footballChampionship->footballTeam;
    while (root->next != NULL && strcmp(root->name, teamName) != 0) {
        root = root->next;
    }

    if (strcmp(root->name, teamName) == 0) {
        FootballTeam *tmp = addPlayer(root, footballPlayer);
        if (tmp != NULL) {
            root = tmp;
        }
    }

    return footballChampionship->footballTeam;

}

void printFootballChampionship(FootballChampionship *footballChampionship) {
    printf("FootballChampionship:%s\n", footballChampionship->name);

    FootballTeam *iter = footballChampionship->footballTeam;
    while (iter != NULL) {
        printArrayList(iter);
        iter = iter->next;
    }
}

FootballPlayer *populateWithData(char *name, double salary) {
    FootballPlayer *footballPlayer = (FootballPlayer *) malloc(sizeof(FootballPlayer));
    footballPlayer->name = name;
    footballPlayer->salary = salary;

    return footballPlayer;
}

/**
class A{

private:

    int x;

public:
    int getX(){
        return x;
    }

    int setX(int x){
        this->x = x;
    }

    void function(int x);

    void function(int x, int y);

};
*/


int main() {
    printf("Hello, World!\n");

    FootballTeam *root = createArrayList();
    root->name = "Team 1";
    FootballPlayer *footballPlayer1 = populateWithData("Player1", 100);
    FootballPlayer *footballPlayer2 = populateWithData("Player2", 200);
    root = addPlayer(root, footballPlayer1);
    root = addPlayer(root, footballPlayer2);


    FootballTeam *team2 = createArrayList();
    team2->name = "Team 2";
    FootballPlayer *footballPlayer3 = populateWithData("Player3", 300);
    FootballPlayer *footballPlayer4 = populateWithData("Player4", 400);
    team2 = addPlayer(team2, footballPlayer3);
    team2 = addPlayer(team2, footballPlayer4);


    FootballTeam *team3 = createArrayList();
    team3->name = "Team 3";
    FootballPlayer *footballPlayer5 = populateWithData("Player5", 500);
    FootballPlayer *footballPlayer6 = populateWithData("Player6", 600);
    team3 = addPlayer(team3, footballPlayer5);
    team3 = addPlayer(team3, footballPlayer6);


    root = addTeam(root, team2);
    root = addTeam(root, team3);


    FootballChampionship *championship = (FootballChampionship *) malloc(sizeof(FootballChampionship));
    championship->name = "Fictional championship";
    championship->footballTeam = root;

    printFootballChampionship(championship);

    FootballTeam *tmp = removeTeam(root, team2);
    if (tmp != NULL) {
        root = tmp;
    }

    printf("\n\n\n\n_________________________\nAfter remove:\n\n");
    printFootballChampionship(championship);

    FootballPlayer *footballPlayer7 = populateWithData("NewPlayer", 5000);
    championship->footballTeam = addFootballPlayer(championship, "Team 3", footballPlayer7);


    printf("\n\n\n\n_________________________\nAfter inserting player:\n\n");
    printFootballChampionship(championship);

    return 0;
}
