/*
 * Prog Tools for Scits Engrs - CIVL 8903/7903 001
 * Prof. Ricardo Taborda
 * Homework 3
 * Written by : Naeem Khoshnevis (nkhshnvs@memphis.edu)
 * Feb 8, 2015 
 */

/*
 * This program is written at Center for Earthquake Research 
 * and Information (CERI) at University of Memphis. 
 * All rights reserved. 
 */

 /* This script take a input file name from user and return
  * outputfile and probabale error file.
  * General idea of the function is to generate the summary report of the 
  * seismic stations operations in California.
  * In order to compile the code run make. Then you can run ()
  * 
  * Example of input file:
  * 6 4
  * CE.13882 CE.13162 CI.CHN CE.13068 CE.23511 CE.DLA
  * Broadband StrongMotion ShortPeriod Borehole 
  * CE.13882 StrongMotion 3
  * CE.23511 Borehole 2
  * CI.CHN ShortPeriod 1
  * CE.13068 Broadband -2
  * CE.23511 ShortPeriod 1
  * CI.00000 HighGain 32
  * 
  */


#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

//string i;
int st_no,ins_no,k,i,f,j,ev_number,f_index,s_index;
char str1;
string line;
string st_name[100];
string ins_name[10];

string temp_station;
string temp_instrument;
int temp_event,temp_array,temp_array1;

int main() {
    
    string   inputfilename;
    ifstream inputfile;
    ofstream outputfile;

    // Prompt user for input file
    cout << "Enter input filename: ";
    cin  >> inputfilename;

    // Sanity check on the file stream
    inputfile.open(inputfilename.c_str());
    
    
    if ( !inputfile.is_open() ) {

        cout << "Cannot open input file: " 
             << inputfilename
             << endl;
        return 1;
    }

    outputfile.open("naeem.out");
    
    
    
    inputfile >> i;
    
    st_no = i;
    
    inputfile >> i;
    
    ins_no = i;
    
    int st_ins[st_no][ins_no];
    
    
    for(i=0; i<st_no; i++)
        
    {
        
        for(j=0; j<ins_no; j++)
            
        {
            st_ins[i][j]=0;
            
            
        }
        
    }
    
   
    
    for (j=0; j<st_no ; j++) {
        
        inputfile >> st_name[j];
        
    }
    
    
    for (j=0; j<ins_no ; j++) {
        
        inputfile >> ins_name[j];
        
    }

    
    for (i=0; i<st_no; i++) {
        
        cout << "station" << "-" << i << " = " << st_name[i] <<"\n";
        
   }
  
    for (i=0; i<ins_no; i++) {
        
        cout << "instrument" << "-" << i << " = " << ins_name[i] <<"\n";
        
    }
    
    
    while (inputfile >> temp_station >> temp_instrument >> temp_event){
    
//     cout << "temp station : " << temp_station << "  temp instrument: " << temp_instrument << " temp event: " << temp_event  << "\n";
        
        for (i=0; i < st_no; i++) {
            
            if (temp_station==st_name[i]) {
                f_index=i;
                break;
            }
        }
        
        for (i=0; i < ins_no; i++) {
            if (temp_instrument==ins_name[i]) {
             
                s_index=i;
                break;
            }
            
        }
        
        st_ins[f_index][s_index]=st_ins[f_index][s_index] + temp_event;
        
  
    }
    
    for(k=0; k<st_no; k++)
        
    {
        for(j=0; j<ins_no; j++)
            
        {
           // cout << "i = " << i << "j="<<j<< "  " << st_ins[i][j] << "\t";
              cout << st_ins[k][j] << "\t";
            
        }
        
        cout << endl;
        
    }
    

    
    // Closing files
    inputfile.close();
    outputfile.close();
    
    return 0;
    
}

