//
//  main.cpp
//  slm243_assignment1
//
//  Created by Sabrina Ma on 9/21/16.
//  Copyright © 2016 Sabrina Ma. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <math.h>
#include <iomanip>
#include "LL.h"
#include "Stack.h"

using namespace std;

void uploadFile(string fName, string fData);
void polyOperation(Stack<LL<int>> obj, string arithOp);
LL<int> arithOperation(LL<int> lhsOperand, LL<int>rhsOperand);

int main(int argc, const char * argv[]) {

    string data, file_name;
    
    //File used for input specified on command line
    file_name = argv[1];
    
    //Reads file into vector of strings
    uploadFile(file_name,data);
    
    return 0;
}

void uploadFile(string fName, string fData)
{
    string row;
    string add = string(1, '+'), subtract = string(1, '-'), multiply = string(1, '*');
    string space = string(1, ' ');
    
    ifstream inFile;
    inFile.open(fName);
    
    if (!inFile)
    {
        cout << "Data file failed to open: " << fName << endl;
        cout << "Please verify the file name and try again. \n";
        cout <<"File data did not successfully load." << endl << endl << endl;
    }
    
    else
    {
        //Read file and count how many polynomials there are. This will be the stack capacity.
        int rowCount = 0;
        while (inFile && getline(inFile, row))
        {
            if ((row != add) && (row != subtract) && (row != multiply))
            {
                rowCount++;
            }
        }

        inFile.close();
        
        //Read file
        inFile.open(fName);
        Stack <LL<int> > stackObj(rowCount);
    
        //Read in every row
        while (inFile && getline(inFile, row))
        {
            //Rows that are polynomials
            if ((row != add) && (row != subtract) && (row != multiply))
            {
                //By counting spaces, can determine how many variables there are (count +1)
                int spaceCount = 0;
                for (int i = 0; i <= row.size()-1; i++)
                {
                    if (row.at(i) == ' ')
                    {
                        spaceCount++;
                    }
                }
                
                //Convert string to integers and add to array for indexing purposes
                stringstream stream(row);
                int array[spaceCount+1];
                int i = 0;
                while(1)
                {
                    int n;
                    stream >> n;
                    array[i] = n;
                    i++;
                    if(!stream)
                        break;
                }
                
                //Instantiate link list object and populate with coefficients and exponents
                LL<int> llObj;
                for (int i = 0; i <= spaceCount; i++)
                {
                    //cout << array[i] << endl;
                    //cout << array[i +1] << endl;
                    llObj.insert(array[i], array[i+1]);
                    i += 1;
                }
                
                cout << "Polynomial: " << llObj << endl;
                
                //cout << "Pushing onto stack\n";
                stackObj.push(llObj);
                
            }//END if statement
            
            else if ((row == add) || (row == subtract) || (row == multiply))
            {
                cout << "Operator: " << row << endl;
                LL<int> rhsOperand = stackObj.getTop();
                stackObj.pop();
                LL<int> lhsOperand = stackObj.getTop();
                stackObj.pop();
                
                //cout << "lhsOperand" << lhsOperand << endl;
                //cout << "rhsOperand" << rhsOperand << endl;
                
                if (row == add)
                {
                    LL<int> result = (lhsOperand + rhsOperand);
                    //cout << result << endl;
                    stackObj.push(result);
                }
                
                if (row == subtract)
                {
                    LL<int> result = (lhsOperand - rhsOperand);
                    //cout << result << endl;
                    stackObj.push(result);
                }

                if (row == multiply)
                {
                    LL<int> result = (lhsOperand * rhsOperand);
                    //cout << result << endl;
                    stackObj.push(result);
                }
            }
        } //END while loop
        cout << "Result: " << stackObj.getTop() << endl;
    }
    inFile.close();
}
