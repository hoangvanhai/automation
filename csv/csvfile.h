#ifndef CSVFile_hpp
#define CSVFile_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "debug.h"

using namespace std;

class CSVFile {

public:
typedef vector<vector<string> > CsvVector;
friend ostream& print(ostream&, const CSVFile&);

public:
    CSVFile();
    CSVFile(const string&);

    void set_filepath(std::string file);
    int open();

    inline vector<string>::size_type get_size();
    uint32_t get_count();
    inline void headers();
    vector<string> get_header();

    CsvVector get_column(const int&);
    CsvVector get_column(const vector<int>&);
    CsvVector get_column(const string&);
    CsvVector get_column(const vector<string>&);

    vector<string> get_row(const int&);
    CsvVector get_row(const int&, const int&); // get some rows in a range

    void write_row(const map<string,string>&);

    inline CsvVector rows() {
        return contents;
    }

    void display(const vector<string> &row);
    void display(const CsvVector &rows);
    void displayall();


private:
    string          m_filename;
    vector<string>  m_header;
    CsvVector       contents;
    ifstream        stream_read;
    ofstream        stream_write;

    inline string remove_extension(const string&);
    vector<string> column_info(const string&);
    string merge_row_vector(const vector<string>&);
    int index_from_string(const string&);
    map<int,string> index_from_string(const map<string,string>& row_map);
};

#endif /* CSVFile_hpp */
