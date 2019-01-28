#include "mainwindow.h"
#include <QApplication>
#include "loadbinaries.h"

int main(int argc, char *argv[])
{

    /* INCLUDED */
    // 2 b)
    const vector <size_t> top = {784, 64, 10};
    Net *neuralNet = new Net(top);
    vector <double> result;
    /* load binary data */

    int num_data = 60000;
    int img_size = 28*28;

    QApplication a(argc, argv);
    MainWindow w;

    //LoadBinaries *load = new LoadBinaries();


    uns_char** pp_imgs = w.load->load_images("images.bin", num_data, img_size);
    w.load->load_labels("images.labels");
    vector <double> inp;

    w.load->print_label(0);
    w.load->print_image(0);

    w.load->print_label(1);
    w.load->print_image(1);

//    neuralNet->analize(inp);
//    neuralNet->print_weights("weights.txt");
//    neuralNet->print_all_results();
//    neuralNet->get_results(result);
//    neuralNet->back_prop(result,5);
//    neuralNet->print_weights("weights_2.txt");
//    neuralNet->set_weights("weights_2.txt");
//    neuralNet->analize(inp);
//    neuralNet->print_all_results();

    for(int i = 0; i < w.pixelWidth; i++){
        for (int j = 0;j < w.pixelHeigth; j++){
            w.pixelValues[i][j] = 0.0;
        }
    }
    w.show();

    return a.exec();
}
