#include "csv.h"

csv::csv()
{

}

void csv::addColumn(string columnInput)
{
    columnName.push_back(columnInput);
}

void csv::addRow(tankData input)
{
    rowValues.push_back(input);
}


void csv::outputCSV()
{
    unsigned int i;
    ofstream output;
    ifstream test;

    test.open("output.csv");
    if(test.is_open())
    {
        test.close();
        output.open("output.csv",std::ios_base::app);
    }

    else
    {    
        output.open("output.csv");

    //output column headings
        for (i = 0; i < columnName.size(); i++)
        {
            if(i != 0)
                output << ",";

            output << columnName[i];
            
        }
        output << "\n";
    }
    

    //output row data
    for (i = 0; i < rowValues.size(); i++)
    {
        output << rowValues[i].player << ",";
        output << rowValues[i].place << ",";
        output << rowValues[i].kills << ",";
        output << rowValues[i].shots << ",";
        output << rowValues[i].hits << ",";
        output << rowValues[i].AP << ",";
        output << rowValues[i].radar << ",";
        output << rowValues[i].maxHealth << ",";
        output << rowValues[i].remainingHealth << ",";
        output << rowValues[i].maxAmmo << endl;
    }

    output.close();
}
