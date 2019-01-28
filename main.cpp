#include "mainwindow.h"
#include <QApplication>
#include "loadbinaries.h"
int main(int argc, char *argv[])
{

    /* INCLUDED */
    const vector <size_t> top = {784, 64, 10};
    Net *neuralNet = new Net(top);
    vector <double> result;
    /* load binary data */
    LoadBinaries *load = new LoadBinaries();

    int num_data = 60000;
    int img_size = 28*28;

    uns_char** pp_imgs = load->load_images("images.bin", num_data, img_size);
    load->load_labels("images.labels");
    vector <double> inp;

    load->print_label(0);
    load->print_image(0);

    load->print_label(1);
    load->print_image(2);

//    neuralNet->analize(inp);
//    neuralNet->print_weights("weights.txt");
//    neuralNet->print_all_results();
//    neuralNet->get_results(result);
//    neuralNet->back_prop(result,5);
//    neuralNet->print_weights("weights_2.txt");
//    neuralNet->set_weights("weights_2.txt");
//    neuralNet->analize(inp);
//    neuralNet->print_all_results();

    QApplication a(argc, argv);
    MainWindow w;
    for(int i = 0; i < w.pixelWidth; i++){
        for (int j = 0;j < w.pixelHeigth; j++){
            w.pixelValues[i][j] = 0.0;
        }
    }
    w.show();

    return a.exec();
}
