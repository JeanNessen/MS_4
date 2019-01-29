//////////////////////////////////////////////////////////////////
/// author: David
///
/// Die LoadBinaries Klasse dient zum Import und zur Interpretation
/// der .bin und .labels Dateien.
/// - - -  - - -  - - -  - - -  - - -  - - -  - - -  - - -  - - -
/// Benutze die load_labels und load_images mit einer Instanz
/// dieser Klasse und lege vorher die .bin .labels Dateien in den
/// Build Ordner des Projektes. Ansonsten auch mal in den Projekt-
/// ordner. Das hängt davon ab, wo dein Qt nach der Datei sucht.
//////////////////////////////////////////////////////////////////

#ifndef LOADBINARIES_H
#define LOADBINARIES_H
#include "net.h"


/**
 * \class LoadBinaries
 *
 * first 4 bytes of the .bin data are
 * HEX: 00 00 08 03
 * BIN: 00000000 00000000 00001000 00000011
 * which means that we have datatype
 * unsigned char with dimension 3.
 *
 * next 4 bytes are
 * HEX: 00 00 EA 60
 * which is 60000
 * probably the amount of images
 *
 * next 4 bytes
 * HEX: 00 00 00 1C
 * which is 28
 *
 * next 4 bytes
 * HEX: 00 00 00 1C
 * which is 28
 * measures 28x28
 */

using namespace std;

/**
 * @brief uns_char
 *
 */
typedef unsigned char uns_char;

class LoadBinaries
{
public:
    /* --- CONSTRUCTOR --- */
    LoadBinaries(){
        _magic_num = 0;
        _pict_size = 28 * 28;
    }

    /* --- IMPORT AND PRINT FUNCTIONS --- */
    void load_labels(string);
    uns_char** load_images(string, int&, int&);
    void loadLabels(string);
    void print_label(int i);
    void print_image(int i);

    /* --- SETTER --- */
    void set_magic_num(int arg) {_magic_num = arg;}
    void set_rows(int arg) {_rows = arg;}
    void set_cols(int arg) {_cols = arg;}
    void set_data_size(int arg){_data_size = arg;}

    /* --- GETTER --- */
    int get_magic_num() {return _magic_num;}
    int get_rows() {return _rows;}
    int get_cols() {return _cols;}
    int get_data_size(){return _data_size;}
    int get_label(int i){return labels[i];}

    /* returns the i-th image from data set */
    vector<int> get_image(int i) {
        vector<int> temp;
        temp.clear();
        for(int j = i; j <= (i+1); j++) {
            for(int k = _pict_size * i; k < _pict_size * (i+1); k++) {
                temp.push_back(images[k]);
            }
        }
        return temp;
    }

    /* --- DESTRUCTOR --- */
    ~LoadBinaries(){ }

    /* --- SUPPORT FUNCTIONS --- */

    /**
     * @brief flip
     * @param i
     * @return
     *
     * If you use an intel processor then the bytes
     * has to be flipped because Intel uses little endian
     * and the data is stored in big endian format.
     */
    int flip (int i) {
        uns_char ch_1, ch_2, ch_3, ch_4;
        ch_1 = i & 255;
        ch_2 = (i >> 8) & 255;
        ch_3 = (i >> 16) & 255;
        ch_4 = (i >> 24) & 255;
        return ((int) ch_1 << 24) + ((int)ch_2 << 16) + ((int)ch_3 << 8) + ch_4;
    }

    /* --- VECTORS & ARRAYS --- */
    vector<int> labels;
    vector<int> images;

    uns_char* p_labels;
private:
    // amount of images provided by the .bin file
    int _pict_size;
    int _data_size;
    int _magic_num;
    int _rows;
    int _cols;
};

inline void LoadBinaries::load_labels(string filename) {
    labels.clear();

    ifstream data (filename, ios::binary);

    if (data.is_open())
    {
        int magic_number = 0;
        int num_labels = 0;
        data.read((char*) &magic_number, sizeof (magic_number));
        magic_number = flip(magic_number);
        data.read((char*) &num_labels, sizeof (num_labels));
        num_labels = flip(num_labels);

        for(int i = 0; i < num_labels; ++i) {
            uns_char temp = 0;
            data.read((char*) &temp, sizeof (temp));
            labels.push_back((int)temp);
        }
    } else {
        throw runtime_error("error while opening file `" + filename + "`!");
    }
}

inline uns_char** LoadBinaries::load_images(string filename, int& set_size, int& img_size) {

    ifstream bin_data(filename, ios::binary);

    if(bin_data.is_open()) {
        set_magic_num(0);
        bin_data.read(reinterpret_cast<char*>(&_magic_num), sizeof (_magic_num));
        set_magic_num(flip(_magic_num));

        if(_magic_num != 2051) throw runtime_error("invalid file");

        bin_data.read(  reinterpret_cast<char*>(&set_size), sizeof (set_size)),
                set_size = flip(set_size);
        bin_data.read(  reinterpret_cast<char*>(&_rows), sizeof (_rows)),
                _rows = flip(_rows);
        bin_data.read(  reinterpret_cast<char*>(&_cols), sizeof (_cols));
                _cols = flip(_cols);

        img_size = _rows * _cols;

        uns_char** pp_data_set = new uns_char*[set_size];

        images.clear();
        for(int i = 0; i < set_size; i++) {
            pp_data_set[i] = new uns_char[img_size];
            bin_data.read(reinterpret_cast<char*>(pp_data_set[i]), img_size);
        }

        for(int i = 0; i < 60000; i++) {
            for(int j = 0; j < 28*28; j++) {
                images.push_back(pp_data_set[i][j]);
            }
        }

        return pp_data_set;
    } else {
        throw runtime_error("error while opening file `" + filename + "`!");
    }
}

inline void LoadBinaries::print_label(int i) {
    printf("%u", get_label(i));
    printf("\n");
}

inline void LoadBinaries::print_image(int i) {
    int c = 0;
    for(int j = 0; j < 28*28; j++) {
        c++;
        printf ("%u " " ", (int)get_image(i)[j]);
        if ( c == 28) {
            printf("\n");
            c = 0;
        };
    }
    printf("\n");
}


#endif // LOADBINARIES_H

//        cout << "magic num: " << _magic_num << "\n"
//             << "which is 0x803 in HEX" << "\n"
//             << "and 00000000 00000000 00001000 00000011 binary format." << "\n"
//             << "Thus the data is stored as unsigned chars with" << "\n"
//             << "with 3 dimensions. width x height x PixelValue";
