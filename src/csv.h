#ifndef CSV_H
#define CSV_H

#include "game.h"

using namespace std;

struct tankData
{
    string player;
    int place;
    int kills;
    int shots;
    int hits;
    int AP;
    int radar;
    int maxHealth;
    int remainingHealth;
    int maxAmmo;
};


class csv
{
public:
    csv();
    void addColumn(string columnInput);
    void addRow(tankData input);

    void outputCSV();

private:
    vector<string> columnName;
    vector<tankData> rowValues;
};

#endif
