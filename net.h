#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <QDebug>

#include "neuron.h"

class Net
{
public:
  Net(const std::vector <size_t> &topology)
  {
    size_t layers_number = topology.size();
    for (size_t layer_num = 0; layer_num != layers_number; layer_num++) {
      net_layers.push_back(Layer());
      size_t outputs_number;

      if (layer_num == topology.size() - 1) {
        outputs_number = 0;
      }
      else {
        outputs_number = topology[layer_num + 1];
      }

      for (size_t neuron_num = 0; neuron_num != topology[layer_num] + 1; neuron_num++) {
        net_layers.back().push_back(Neuron(outputs_number, neuron_num));
      }
      net_layers.back().back().set_output_value(1);
    }
  }

  void analize(const std::vector <double> &input_values);
  void count_error(const std::vector <double> &target_values, size_t test);
  void back_prop(const std::vector <double> &target_values, size_t test);
  void get_results(std::vector <double> &results_values) const;

  /* INCLUDED */
  void get_layer_results(std::vector <double> &result_values, size_t i) const;
  /* INCLUDED */
  void print_all_results() const;

  void set_weights(std::string filename);
  void print_weights(std::string filename);

  double current_speed;
  double total_net_error = 0;
  double net_error;

  char first_byte[1];   // Value 0x00
  char second_byte[1];  // Value 0x00
  char third_byte[1];   // Type of data
  char fourth_byte[1];  // Dimension

  ~Net()
  {}
private:
  std::vector <Layer> net_layers;
  double prev_net_error = 1000000000;
};

//
// Direct mode of neural network
// copy input values from map/MNIST
// for-loop "analize" for every neuron layers
//
inline void Net::analize(const std::vector <double> &input_values)
{
    qDebug() << "analize: " << endl;

  for (size_t i = 0; i != input_values.size(); i++) {
    net_layers[0][i].set_output_value(input_values[i]);
  }
  for (size_t layer_num = 1; layer_num != net_layers.size(); layer_num++) {
    Layer &prev_layer = net_layers[layer_num - 1];
    for (size_t n = 0; n != net_layers[layer_num].size() - 1; n++) {
      net_layers[layer_num][n].analize(prev_layer);
    }
  }
}


//
// back propagation
// calculate output gradients
// update input weights of neurons
//
inline void Net::back_prop(const std::vector <double> &target_values, size_t test)
{
  current_speed = net_layers[0][0].eta;
  Layer &output_layer = net_layers.back();
  if (test != 0 && test % 500 == 0) {
    bool speed = true;
    total_net_error /= 500;
    if (total_net_error - prev_net_error > 0.01) {
      speed = false;
    }
  for (size_t layer = 0; layer != net_layers.size() - 1; layer++) {
    for (size_t neuron = 0; neuron != net_layers[layer].size(); neuron++) {
      net_layers[layer][neuron].change_tempo(speed);
    }
  }
  prev_net_error = total_net_error;
  total_net_error = 0;
  }
  for (size_t n = 0; n != output_layer.size() - 1; n++) {
    output_layer[n].calc_output_gradients(target_values[n]);
  }
  for (size_t layer_num = net_layers.size() - 2; layer_num != 0; layer_num--) {
    Layer &hidden_layer = net_layers[layer_num];
    Layer &next_layer = net_layers[layer_num + 1];
    for (size_t n = 0; n != hidden_layer.size(); n++) {
      hidden_layer[n].calc_hidden_gradients(next_layer);
    }
  }
  for (size_t layer_num = net_layers.size() - 1; layer_num != 0; layer_num--) {
    Layer &layer = net_layers[layer_num];
    Layer &prev_layer = net_layers[layer_num - 1];
    for (size_t n = 0; n != layer.size() - 1; n++) {
      layer[n].update_input_weights(prev_layer);
    }
  }
}

//
// copy output values from net layers to result vector
//
inline void Net::get_results(std::vector <double> &results_values) const
{
  results_values.clear();
  for (size_t n = 0; n != net_layers.back().size() - 1; n++) {
    results_values.push_back(net_layers.back()[n].get_output_value());
  }
}


//
// load Neuron Weights from file
//
inline void Net::set_weights(std::string filename)
{
  std::ifstream weight_file(filename.c_str());
  if (!weight_file.eof()) {
    std::string odd_word;
    int odd_num;
    for (size_t layer_num = 0; layer_num != net_layers.size() - 1; layer_num++) {
      weight_file >> odd_word >> odd_num;
      for (size_t neuron_num = 0; neuron_num != net_layers[layer_num].size(); neuron_num++) {
        weight_file >> odd_word >> odd_num;
        Neuron &neuron = net_layers[layer_num][neuron_num];
        for (size_t i = 0; i != neuron.output_weights.size(); i++) {
          weight_file >> neuron.output_weights[i].weight;
        }
      }
    }
  }
  weight_file.close();
}

//
// save Neuron Weights into file
//
inline void Net::print_weights(std::string filename)
{
  std::ofstream weight_file(filename.c_str());
  weight_file.clear();
  for (size_t layer_num = 0; layer_num != net_layers.size() - 1; layer_num++) {
    weight_file << "Layer " << layer_num + 1 << "\r\n" << "\r\n";
    for (size_t neuron_num = 0; neuron_num != net_layers[layer_num].size(); neuron_num++) {
      std::vector <double> neuron_weights;
      net_layers[layer_num][neuron_num].get_neuron_weights(neuron_weights);
      if (neuron_num == net_layers[layer_num].size() - 1) {
        weight_file << "\r\n" << "Bias " << neuron_num + 1 << "\r\n" << "\r\n";
      }
      else {
        weight_file << "\r\n" << "Neuron " << neuron_num + 1 << "\r\n" << "\r\n";
      }
      for (size_t i = 0; i != neuron_weights.size(); i++) {
        weight_file << neuron_weights[i] << ' ';
      }
      weight_file << "\r\n";
    }
    weight_file << "\r\n" << "\r\n" << "\r\n";
  }
  weight_file.close();
}

/* INCLUDED */
//
//
//
inline void Net::get_layer_results(std::vector <double> &result_values, size_t i) const {
    result_values.clear();
    for(size_t n = 0; n != net_layers[i].size(); n++) {
        result_values.push_back(net_layers[i][n].get_output_value());
    }
}

/* INCLUDED */
//
// print each layer results
//
inline void Net::print_all_results() const {
    size_t j = 0;
    vector <double> result;

    for( size_t i = 0; i < net_layers.size(); i++ ) {
        get_layer_results(result, i);
        if( i == 0) {
            std::cout << "########################" << "\r\n";
            std::cout << " Input Layer results  " << "\r\n";
            std::cout << "########################" << "\r\n";
        }

        if( i == net_layers.size() - 1 ) {
            std::cout << "########################" << "\r\n";
            std::cout << " Output Layer results " << "\r\n";
            std::cout << "########################" << "\r\n";
        }

        if( i > 0 && i < net_layers.size() - 1 ) {
            std::cout << "########################" << "\r\n";
            std::cout << " Hidden Layer " << i << " results " << "\r\n";
            std::cout << "########################" << "\r\n";
        }
        for( auto p : result ) {
            j++;
            std::cout << "Neuron " << j << ": " << p << "\r\n";
        }
        j = 0;
    }
    std::cout << "########################" << "\r\n";
}

/* INCLUDED */
//
// load data from binary file
//

#endif
