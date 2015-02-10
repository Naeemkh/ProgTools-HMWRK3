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
int st_no,ins_no,k,i,f,j,ev_number;
char str1;
string line,st_name,ins_name;

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
    
    k=1;

    while ( inputfile >> i ) {
        
        if      ( k==1 ) { st_no = i; k=k+1;}
        else if ( k==2 ) {ins_no = i; k=k+1;}
        else { break; }
        
    }
    
    inputfile.close();
    
    inputfile.open(inputfilename.c_str());
    
    //string st_name[st_no];

    cout << "Number of stations" << st_no << "  Number of Instruments" << ins_no << "\n";
    
    
    f=1;
    j=1;
    

  /*  while ( inputfile >> str1 ) {
        
        if (f==1 || f==2) { f=f+1;}
        
        else if (f < (3+st_no) ) {
        
            
        
        }
   
    
    while (getline(inputfile, line)) {
        
        istringstream iss(line);
        string word;
        
        int g=1;
        while(iss >> word){
            if (g==1){st_name = word;}
            if (g==2){ins_name = word;}
            //if (g==3){ev_number = word;}
            g=g+1;
        }
        
        cout<< "station name :" << st_name << "  Instrument name:" << ins_name << "\n" ;
        
            if (word == "ShortPeriod"){
                cout << "ShortPeriod stations:" << f+1 << "\n";
            }
        }
    
    
        
  */
    

    
    //cout << st_ins[0][3] << "\n";
    // st_ins[0][j]=str1; j=j+1;f=f+1;
    
    
    // Closing files
    inputfile.close();
    outputfile.close();
    
    return 0;
    
}

