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
      * outputfile and error file.General idea of the function is
      * to generate the summary report of the seismic stations 
      * operations in California.
      * In order to compile the code run make -f naeem.mk 
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
    
    /********************* Variables declaration **********************************/
        
    int i, j;
    int st_no, ins_no, ev_number, f_index, s_index, temp_event;
    
    int max_n_station = 0,
        min_n_station = 0,
        max_n_instrument = 0,
        min_n_instrument = 0;
    
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
    
    /******************************************************************************/
    /*********************** function declaration *********************************/


    //Function for picking the maximum and minimum of stations and instrumetns
    // max_min(number of array, array, predefined max, 1 ) d=1 max, d=2 min
    int max_min (int a, int b[], int c, int d) {
    
        if ( d == 1 ) {
        
            for ( i = 0;  i < a; i++ ) {
            
                if ( b[i] > c ) {
                
                    c = b[i];
                
                }
            }
            
        } else if (d == 2 ) {
            
            for ( i = 0;  i < a; i++ ) {
            
                if ( b[i] < c ) {
                
                    c = b[i];
              
                }
            }
        }
        
       return c;
        
    }


            
    int main() {
        
        string   inputfilename;
        ifstream inputfile;
        ofstream outputfile, errorfile;
    
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
                
        // open output file and error file.
        outputfile.open("naeem.out");
        errorfile.open("naeem.err");
        
        outputfile << "Seismic Events Summary Report" << "\n" << "\n";
                
        inputfile >> i;
        st_no = i;
        
        inputfile >> i;
        ins_no = i;
        
        
        cout << "\n";
        cout << "Number of stations: " << st_no << "\n";
        cout << "Number of instruments: " << ins_no << "\n";
        
        errorfile << "\n";
        errorfile << "Number of stations: " << st_no << "\n";
        errorfile << "Number of instruments: " << ins_no << "\n";
        
        
        // Declare the arrays after reading the size of arrays.
        int st_ins[st_no][ins_no],
            sum_stations[st_no],
            sum_instrument[ins_no];
              
        // Preallocate the arrays with zero.
        for ( i = 0; i < st_no; i++ ) {
            
            sum_stations[i] = 0;
            
            for ( j = 0; j < ins_no; j++ ) {
                
                st_ins[i][j] = 0;
                sum_instrument[j] = 0;
                
            }
        }
        
        
        // store the station name
        for ( j = 0; j < st_no; j++ ) {
            
            inputfile >> st_name[j];
            
        }
        
        
        //store the instrument name
        for ( j = 0; j < ins_no; j++ ){
            
            inputfile >> ins_name[j];
            
        }
        
        
        // Write the summary report in the output file
        outputfile << setw(10) << left << "Station" << " ";
        
        for ( i = 0; i < st_no; i++ ) {
            
            outputfile  << setw(15) << right << ins_name[i] << " ";
            
        }
      
        outputfile  << "\n";
                
        int data_counter = 1;
        
        // read the rest of file to get the station and instrument data
        while ( inputfile >> temp_station >> temp_instrument >> temp_event ) {
            
            // suppose that stations and instruments and number of events are not valid.
            is_station    = false;
            is_instrument = false;
            is_event      = false;
            
            for ( i = 0; i < st_no; i++ ) {
                
                if ( temp_station == st_name[i] ) {
                    
                    f_index = i;
                    is_station = true;
                    break;
                }
            }
            
            for (i = 0; i < ins_no; i++) {
                
                if ( temp_instrument == ins_name[i] ) {
                 
                    s_index = i;
                    is_instrument = true;
                    break;
                }
            }
            
            if ( temp_event >= 0 ) {
                is_event = true;
            }
            
            // If all three fields are valid then add it to data.
            if ( is_event && is_instrument && is_station ) {
                
                st_ins[f_index][s_index] = st_ins[f_index][s_index] + temp_event;
                
            } else if ( is_station == false ) {
                
                cout << "Entry #" << data_counter << ":" << temp_station << " "
                     << temp_instrument << " " << temp_event << " "
                     << "-- Warning: Station does not exist" << "\n";
                
                
                errorfile << "Entry #" << data_counter << ":" << temp_station << " "
                          << temp_instrument << " " << temp_event << " "
                          << "-- Warning: Station does not exist" << "\n";
              
                nvalid_st = nvalid_st + 1;
                
            } else if ( is_instrument == false ) {
                
                cout << "Entry #" << data_counter << ":" << temp_station << " "
                     << temp_instrument << " " << temp_event << " "
                     << "-- Warning: Instrument does not exist" << "\n";
                
                
                errorfile << "Entry #" << data_counter << ":" << temp_station << " "
                          << temp_instrument << " " << temp_event << " "
                          << "-- Warning: Instrument does not exist" << "\n";
                
                nvalid_ins = nvalid_ins + 1;
                
            } else if ( is_event == false ){
                
                cout << "Entry #" << data_counter << ":" << temp_station << " "
                     << temp_instrument << " " << temp_event << " "
                     << "-- Warning: Negative events" << "\n";
                
                errorfile << "Entry #" << data_counter << ":" << temp_station << " "
                          << temp_instrument << " " << temp_event << " "
                          << "-- Warning: Negative events" << "\n";
                     
                nvalid_ev = nvalid_ev + 1;
                    
            }
                    
            data_counter = data_counter + 1;
        }
        
        
        cout << "Total of " 
             << ( data_counter - 1 ) - ( nvalid_st + nvalid_ins + nvalid_ev ) 
             << " entries processed correctly" << "\n"
             << "Total of " << ( nvalid_st + nvalid_ins + nvalid_ev ) << " ignored" << "\n"
             << "Generating report... " << "\n";
        
        errorfile << "Total of " 
                  << ( data_counter - 1 ) - ( nvalid_st + nvalid_ins + nvalid_ev )
                  << " entries processed correctly" << "\n"
                  << "Total of " << ( nvalid_st + nvalid_ins + nvalid_ev ) << " ignored" << "\n"
                  << "Generating report... " << "\n";
        
        
        // calculation of total number of event per station
        for ( i = 0; i < st_no; i++ ) {
           
           for ( j = 0; j < ins_no; j++ ) {
               
                sum_stations[i] += st_ins[i][j];
               
           }
           
        }
        
        
        // Assumption of the fisrt number as both max and min number of stations.
        min_n_station = sum_stations[0];
        max_n_station = sum_stations[0];
        
        for ( j = 0; j < ins_no; j++ ) {
            
            for ( i = 0; i < st_no; i++ ) {
               
                sum_instrument[j] += st_ins[i][j];
            }
            
        }
        
        // Assumption of the fisrt number as both max and min number of instruments.
        min_n_instrument = sum_instrument [0];
        max_n_instrument = sum_instrument [0];
        
        
        for ( i = 0; i < st_no; i++ ) {
        
            outputfile << setw(10) << left << st_name[i] << " ";
            
            for( j = 0; j < ins_no; j++ ) {
                
                outputfile << setw(15) << right << st_ins[i][j] << " ";
                
            }

            outputfile << "\n";
        }
        
        outputfile << "\n";
        outputfile << "Total number of events per station" << "\n" << "\n";
           
        outputfile << setw(10) << left << "Station" << " " << setw(15) << right << "Total" << "\n";
        
        for ( i = 0; i < st_no; i++ ) {
            
            outputfile << setw(10)<< left << st_name[i] << " " << setw(15) << right << sum_stations[i] << "\n";
            
        }
        
        
        outputfile << "\n";
        outputfile << "Total number of events per insrument" << "\n" << "\n";
               
        
        outputfile << setw(15) << left << "Instrument" << " " << setw(10) << right << "Total" << "\n";
        
        for ( i = 0; i < ins_no; i++) {
            
            outputfile << setw(15) << left << ins_name[i] << " " << setw(10) << right << sum_instrument[i] << "\n";
            
        }
        
        // Picking the most and least number of events per stations and instruments.
        max_n_station    = max_min(st_no,sum_stations,max_n_station,1);
        min_n_station    = max_min(st_no,sum_stations,min_n_station,2);
        max_n_instrument = max_min(ins_no,sum_instrument,max_n_instrument,1);
        min_n_instrument = max_min(ins_no,sum_instrument,min_n_instrument,2);
        
        
        // storing all stations that have max number of events.
        for ( i = 0; i < st_no ; i++ ) {
            
            if ( sum_stations[i] == max_n_station ){
                
                max_stations_record[max_st] = st_name[i];
                
                max_st = max_st + 1;
            }
        }
        
      
        // storing all stations that have min number of events.
        for ( i = 0; i < st_no ; i++ ) {
            
            if ( sum_stations[i] == min_n_station ) {
                
                min_stations_record[min_st] = st_name[i];
                
                min_st = min_st + 1;
            }
            
        }
    
       
        // storing all instruments that have max number of events.
        for ( i = 0; i < ins_no ; i++ ) {
            
            if ( sum_instrument[i] == max_n_instrument ) {
                
                max_instrument_record[max_ins] = ins_name[i];
                
                max_ins = max_ins + 1;
            }
            
        }
        
      
        // storing all instrumetns that have min number of events.
        for ( i = 0; i < ins_no ; i++) {
            
            if ( sum_instrument[i] == min_n_instrument ) {
                
                min_instrument_record[min_ins] = ins_name[i];
                
                min_ins = min_ins + 1;
                
            }
            
        }
    
        outputfile << "\n";
        outputfile << "Stations with the  most records is: ";
        
        for ( i = 0; i < max_st ; i++ ) {
            
            // Defining a format of print for one or more than one stations.
            if ( max_st == 1 || i == max_st - 1 ) {
                
                outputfile << max_stations_record[i];
                
            } else {
                
                outputfile << max_stations_record[i] << ", ";
             
            }
        }
        
        outputfile << " with " << max_n_station << " events" << "\n";
        
        
        outputfile << "Stations with the least records is: ";
        
        for ( i = 0; i < min_st; i++ ) {
            
            // Defining a format of print for one or more than one stations.
            if ( min_st == 1 || i == min_st - 1 ) {
                
                outputfile << min_stations_record[i];
                
            } else {
                
                outputfile << min_stations_record[i] << ", ";
                
            }
        }
        
        outputfile << " with " << min_n_station << " events" << "\n" << "\n";
        
        outputfile << "Instruments with the  most records is: ";
        
        for ( i = 0; i < max_ins; i++ ) {
            
            // Defining a format of print for one or more than one instruments.
            if ( max_ins == 1 || i == max_ins - 1 ) {
                
                outputfile << max_instrument_record[i];
                
            } else {
                
                outputfile << max_instrument_record[i] << ", ";
                
            }
        }
        
        outputfile << " with " << max_n_instrument << " events" << "\n";
    
        outputfile << "Instruments with the least records is: ";
        
        for ( i = 0; i < min_ins; i++ ) {
            
            // Defining a format of print for one or more than one instruments.
            if ( min_ins == 1 || i == min_ins - 1 ) {
                
                outputfile << min_instrument_record[i];
                
            } else {
                
                outputfile << min_instrument_record[i] << ", ";
                
            }
        }
        
        outputfile << " with " << min_n_instrument << " events" << "\n" << "\n";
        
        cout << "Completed!" << "\n" << "\n";
        
        errorfile << "Completed!" << "\n" << "\n";
        
        
        // Closing files
        inputfile.close();
        outputfile.close();
        errorfile.close();
        
        return 0;
        
    }

