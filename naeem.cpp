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
#include <iomanip>

using namespace std;

int i, j, k;
int st_no, ins_no, ev_number, f_index, s_index, temp_event;

int max_n_station = 0,
    min_n_station = 0,
    max_n_instrument= 0,
    min_n_instrument= 0;

int max_st  = 0,
    min_st  = 0,
    max_ins = 0,
    min_ins = 0;

int nvalid_ev  = 0,
    nvalid_ins = 0,
    nvalid_st  = 0;

bool is_station,
     is_instrument,
     is_event;


string st_name[100];
string ins_name[10];
string max_stations_record[100];
string min_stations_record[100];
string max_instrument_record[10];
string min_instrument_record[10];

string temp_station;
string temp_instrument;


int main() {
    
    string   inputfilename;
    ifstream inputfile;
    ofstream outputfile,errorfile;

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
    errorfile.open("naeem.err");
    
    // Write the summary report in the output file
    outputfile << "Seismic Events Summary Report" << "\n"<<"\n";
    
    
    inputfile >> i;
    st_no = i;
    
    inputfile >> i;
    ins_no = i;
    
    // number of stations
    cout << "\n";
    cout << "Number of stations: " << st_no << "\n";
    cout << "Number of instruments: " << ins_no << "\n";
    
    errorfile << "\n";
    errorfile << "Number of stations: " << st_no << "\n";
    errorfile << "Number of instruments: " << ins_no << "\n";
    
    int st_ins[st_no][ins_no];
    int sum_stations[st_no];
    int sum_instrument[ins_no];
    
    
    for(i=0; i<st_no; i++){
        
        for(j=0; j<ins_no; j++){
            
            st_ins[i][j] = 0;
            
        }
    }
    
    
    for(i=0; i<st_no; i++){
        
       sum_stations[i] = 0;
        
    }
    
    
    for(i=0; i<st_no; i++){
        
        sum_instrument[i] = 0;
        
    }
    
    
 
    for (j=0; j<st_no ; j++) {
        
        inputfile >> st_name[j];
        
    }
    
    
    for (j=0; j<ins_no ; j++) {
        
        inputfile >> ins_name[j];
        
    }
    
    
    // Write the summary report in the output file
    outputfile <<setw(10)<<left<< "Station" << " " ;
    
    for (i=0; i<st_no; i++) {
        
         outputfile  << setw(15) << right << ins_name[i] << " " ;
        
   }
  
    outputfile  << "\n";
   
    
    int data_counter = 1;
    
    while (inputfile >> temp_station >> temp_instrument >> temp_event){
        
        is_station    = false;
        is_instrument = false;
        is_event      = false;
        
        for (i=0; i < st_no; i++) {
            
            if (temp_station==st_name[i]) {
                f_index=i;
                is_station = true;
                break;
            }
        }
        
        for (i=0; i < ins_no; i++) {
            if (temp_instrument==ins_name[i]) {
             
                s_index=i;
                is_instrument=true;
                break;
            }
            
        }
        
        if (temp_event >= 0){
            is_event = true;
        }
        
        if (is_event && is_instrument && is_station){
             st_ins[f_index][s_index]=st_ins[f_index][s_index] + temp_event;
        } else if (is_station==false){
            cout << "Entry #"<<data_counter<<":"<<temp_station<<" "<<temp_instrument<<" "<<temp_event<<" "
            << "-- Warning: Station does not exist"<<"\n";
            
            errorfile << "Entry #"<<data_counter<<":"<<temp_station<<" "<<temp_instrument<<" "<<temp_event<<" "
            << "-- Warning: Station does not exist"<<"\n";
            
            nvalid_st=nvalid_st+1;
            
        } else if (is_instrument==false){
            cout << "Entry #"<<data_counter<<":"<<temp_station<<" "<<temp_instrument<<" "<<temp_event<<" "
            << "-- Warning: Instrument does not exist"<<"\n";
            
            errorfile << "Entry #"<<data_counter<<":"<<temp_station<<" "<<temp_instrument<<" "<<temp_event<<" "
            << "-- Warning: Instrument does not exist"<<"\n";
            
            
            nvalid_ins=nvalid_ins+1;
            
        } else if (is_event==false){
            cout << "Entry #"<<data_counter<<":"<<temp_station<<" "<<temp_instrument<<" "<<temp_event<<" "
            << "-- Warning: Negative events"<<"\n";
            
            errorfile << "Entry #"<<data_counter<<":"<<temp_station<<" "<<temp_instrument<<" "<<temp_event<<" "
            << "-- Warning: Negative events"<<"\n";
            
            nvalid_ev=nvalid_ev+1;
                
        }
                
        
        data_counter=data_counter+1;
    }
    
    
    cout << "Total of " << (data_counter-1)-(nvalid_st+nvalid_ins+nvalid_ev) << " entries processed correctly" <<"\n";
    cout << "Total of " << (nvalid_st+nvalid_ins+nvalid_ev) << " ignored" <<"\n";
    cout << "Generating report... " << "\n";
    
    
    errorfile << "Total of " << (data_counter-1)-(nvalid_st+nvalid_ins+nvalid_ev) << " entries processed correctly" <<"\n";
    errorfile << "Total of " << (nvalid_st+nvalid_ins+nvalid_ev) << " ignored" <<"\n";
    errorfile << "Generating report... " << "\n";
    
    // calculation of total number of event per station
    
    for (i=0; i<st_no; i++) {
       
       for (j=0; j < ins_no; j++){
           
           sum_stations[i]+=   st_ins[i][j];
       }
       
    }
    
    min_n_station = sum_stations[1];
    max_n_station = sum_stations[1];
    
    for (j=0; j<ins_no; j++) {
        
        for (i=0; i < st_no; i++){
           
            sum_instrument[j]+= st_ins[i][j];
        }
        
    }
    
    
    min_n_instrument = sum_instrument [1];
    max_n_instrument = sum_instrument [1];
    
    for (k=0; k<st_no; k++) {
    
        
        outputfile <<setw(10)<<left<<  st_name[k] <<" ";
        
        for(j=0; j<ins_no; j++){
            
        outputfile <<setw(15)<<right<< st_ins[k][j] << " ";
            
        }
         outputfile << "\n";
        
        
    }
    
     outputfile << "\n";
     outputfile << "Total number of events per station"<< "\n";
     outputfile << "\n";
  
    
     outputfile <<setw(10)<<left<<"Station"<<" "<<setw(15)<<right<<"Total"<<"\n";
    
    for (k=0; k<st_no; k++) {
        
        
        outputfile <<setw(10)<<left<<  st_name[k] << " "<<setw(15) <<right<< sum_stations[k] << "\n";
        
        
    }
    
    
    outputfile << "\n";
    outputfile << "Total number of events per insrument"<< "\n";
    outputfile << "\n";
    
    
    
     outputfile <<setw(15)<<left<<"Instrument"<<" "<<setw(10)<<right<<"Total"<<"\n";
    for (k=0; k<ins_no; k++) {
        
       
        outputfile <<setw(15)<<left<< ins_name[k] <<" "<<setw(10)<<right << sum_instrument[k]<< "\n";
        
        
    }
    
    // Calculation the most record for stations
    
    for (i=0;  i < st_no; i++) {
        if (sum_stations[i] > max_n_station){
            max_n_station = sum_stations[i];
            
        }
        
    }
    
    // Calculation the least record for stations
    
    for (i=0; i < st_no; i++) {
        if (sum_stations[i] < min_n_station){
            min_n_station = sum_stations[i];
        }
        
    }
    
     // Calculation the most record for instruments
    for (i=0; i < ins_no; i++) {
        if (sum_instrument[i] > max_n_instrument){
            max_n_instrument = sum_instrument[i];
        }
        
    }
    
    // Calculation the least record for instruments
    for (i=0; i < ins_no ; i++) {
        if (sum_instrument[i] < min_n_instrument){
            min_n_instrument = sum_instrument[i];
        }
        
    }
    
   
    
    for (i=0; i < st_no ; i++) {
        if (sum_stations[i] == max_n_station){
            max_stations_record[max_st] = st_name[i];
            max_st=max_st+1;
        }
        
    }
    
  
    
    for (i=0; i < st_no ; i++) {
        if (sum_stations[i] == min_n_station){
            min_stations_record[min_st] = st_name[i];
            min_st=min_st+1;
        }
        
    }

   
    
    for (i=0; i < ins_no ; i++) {
        if (sum_instrument[i] == max_n_instrument){
            max_instrument_record[max_ins] = ins_name[i];
            max_ins=max_ins+1;
        }
        
    }
    
  
    
    for (i=0; i < ins_no ; i++) {
        if (sum_instrument[i] == min_n_instrument){
            min_instrument_record[min_ins] = ins_name[i];
            min_ins=min_ins+1;
        }
        
    }

    
    outputfile << "Stations with the  most records is: " ;
    
    for (i=0; i < max_st ; i++) {
        if (max_st==1 || i == max_st-1) {
            outputfile << max_stations_record[i];
        } else  {
            outputfile << max_stations_record[i] << ", ";
         
        }
    }
    
    outputfile << " with " << max_n_station << " events" <<"\n" ;
    
    
    
    
    outputfile << "Stations with the least records is: " ;
    
    for (i=0; i < min_st ; i++) {
        if (min_st==1 || i == min_st-1) {
            outputfile << min_stations_record[i];
        } else  {
            outputfile << min_stations_record[i] << ", ";
            
        }
    }
    
    outputfile << " with " << min_n_station << " events" <<"\n"<<"\n" ;
    
    
    outputfile << "Instruments with the  most records is: " ;
    
    for (i=0; i < max_ins ; i++) {
        if (max_ins==1 || i == max_ins-1) {
            outputfile << max_instrument_record[i];
        } else  {
            outputfile << max_instrument_record[i] << ", ";
            
        }
    }
    
    outputfile << " with " << max_n_instrument << " events" <<"\n" ;

    
    outputfile << "Instruments with the least records is: " ;
    
    for (i=0; i < min_ins ; i++) {
        if (min_ins==1 || i == min_ins-1) {
            outputfile << min_instrument_record[i];
        } else  {
            outputfile << min_instrument_record[i] << ", ";
            
        }
    }
    
    outputfile << " with " << min_n_instrument << " events" <<"\n"<<"\n" ;
    
    cout << "Completed!" <<"\n"<<"\n";
    
    errorfile << "Completed!" <<"\n"<<"\n";
    
    
    // Closing files
    inputfile.close();
    outputfile.close();
    errorfile.close();
    
    return 0;
    
}

