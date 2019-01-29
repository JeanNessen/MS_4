//////////////////////////////////////////////////////////////////
///
///
///
///
///
//////////////////////////////////////////////////////////////////

#ifndef NEURON_H
#define NEURON_H

#include <stdlib.h>
#include <vector>
#include <math.h>

using std::vector;

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron
{
public:
  struct connection {
    double prev_weight;
    double weight;
    double change_weight = 0;
  };

  double eta = 20;
  std::vector <connection> output_weights;

  Neuron(size_t outputs_num, size_t number)
  {
    for (size_t c = 0; c != outputs_num; c++) {
      output_weights.push_back(connection());
      output_weights.back().weight = random_weight();
      output_weights.back().prev_weight = output_weights.back().weight;
    }
    neuron_number = number;
  }

  void set_output_value(double value) { output_value = value; }
  double get_output_value() const { return output_value; }

  void analize(const Layer &prev_layer);
  void calc_output_gradients(double target_value);
  void calc_hidden_gradients(const Layer &next_layer);
  void update_input_weights(Layer &prev_layer);
  void change_tempo(bool speed);
  void get_neuron_weights(std::vector <double> &neuron_weights);

  ~Neuron()
  {}
private:
  size_t neuron_number;
  double output_value;
  double gradient;

  static double random_weight() { return rand() / double(RAND_MAX) - 0.5; }
  static double activation_function(double x) { return 1 / (1 + exp(-x)); }
  static double activation_function_derivative(double x) { return activation_function(x) * (1 - activation_function(x)); }

  double sum_weight_gradients(const Layer &next_layer) const;
  double alpha = 0.9;
};


inline void Neuron::analize(const Layer &prev_layer)
{
  double sum = 0;
  for (size_t n = 0; n != prev_layer.size(); n++) {
    sum += prev_layer[n].get_output_value() * prev_layer[n].output_weights[neuron_number].weight;
  }
  output_value = activation_function(sum);
}

inline void Neuron::calc_output_gradients(double target_value)
{
  double difference = target_value - output_value;
  gradient = difference * activation_function_derivative(output_value);
}

inline double Neuron::sum_weight_gradients(const Layer &next_layer) const
{
  double sum = 0;
  for (size_t n = 0; n != next_layer.size() - 1; n++) {
    sum += output_weights[n].weight * next_layer[n].gradient;
  }
  return sum;
}

inline void Neuron::calc_hidden_gradients(const Layer &next_layer)
{
  double  derivative_difference = sum_weight_gradients(next_layer);
  gradient = derivative_difference * activation_function_derivative(output_value);
}

inline void Neuron::update_input_weights(Layer &prev_layer)
{
  for (size_t n = 0; n != prev_layer.size(); n++) {
    Neuron &neuron = prev_layer[n];
    double old_change_weight = neuron.output_weights[neuron_number].change_weight;
    double new_change_weight = (1 - neuron.alpha) * neuron.eta * neuron.get_output_value() * gradient + neuron.alpha * old_change_weight;
    neuron.output_weights[neuron_number].change_weight = new_change_weight;
    neuron.output_weights[neuron_number].weight += new_change_weight;
  }
}

inline void Neuron::change_tempo(bool speed)
{
  if (speed) {
    eta *= 2.0;
  }
  else if (eta > 0.001) {
    eta *= 0.1;
  }
}

inline void Neuron::get_neuron_weights(std::vector <double> &neuron_weights)
{
  for (size_t i = 0; i != output_weights.size(); i++) {
    neuron_weights.push_back(output_weights[i].weight);
  }
}

#endif
