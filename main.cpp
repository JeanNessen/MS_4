/////////////////////////////////////////////////////////////////////////////////
/// 1)      MainWindow.h MainWindow.cpp
/// 2 a)    Zu finden in der loadbinaries.h
/// 2 b)    Initialisierung des neuronalen Netzes Anhand
///         der Topologie (784,64,10) in Zeile 18 & 19.
///         und erster Versuch des Trainings. Klappt aber nicht...
///
///
///         WICHTIG:    EINIGE ERGEBNISSE, DIE IN DER KONSOLE
///                     ERSCHEINEN SOLLEN, ERSCHEINEN ERST NACH DEM
///                     SCHLIESSEN DES USER INTERFACES!!!!
/////////////////////////////////////////////////////////////////////////////////
#include "mainwindow.h"
#include <QApplication>
#include "loadbinaries.h"


int main(int argc, char *argv[])
{
    /* INCLUDED */
    const vector <size_t> top = {784, 64, 10};
    Net *neuralNet = new Net(top);

    vector <double> result;

    /* Amount of data - 60k pictures */
    int num_data = 60000;
    int img_size = 28*28;

    QApplication a(argc, argv);
    MainWindow w;

    /* load binary data */
    uns_char** pp_imgs = w.load->load_images("images.bin", num_data, img_size);
    w.load->load_labels("images.labels");

    vector<double> inp;

    /* filling the input vector inp with the pixel data from the 0-th image, a "5". */
    for(int i = 0; i < 28*28; i++)
    {
        inp.push_back(w.load->get_image(0)[i]);
    }

    /* prints first 2 pictures and labels from the dataset
     * You can use w.load->print_label(59999) to see
     * that all 60k images are loaded in. Just comment
     * the for loop and uncomment the line above.
     **/
    //w.load->print_image(59999);
    for(int i = 0; i < 2; i++) {
        w.load->print_label(i);
        w.load->print_image(i);
    }

    neuralNet->analize(inp);
    neuralNet->print_weights("weights.txt");
    neuralNet->print_all_results();
    neuralNet->get_results(result);
    neuralNet->back_prop(result,5);
    neuralNet->print_weights("weights_2.txt");
    /*---------------------------------------*/
    neuralNet->set_weights("weights_2.txt");
    neuralNet->analize(inp);
    neuralNet->print_weights("weights_3.txt");
    neuralNet->print_all_results();
    neuralNet->get_results(result);
    neuralNet->back_prop(result,5);
    neuralNet->print_weights("weights_4.txt");

    //Beim ersten aufrufen des Programmes soll das Array mit nullen gefüllt sein.
    for(int i = 0; i < w.pixelWidth; i++){
        for (int j = 0;j < w.pixelHeigth; j++){
            w.pixelValues[i][j] = 0.0;
        }
    }
    w.show();

    return a.exec();
}
