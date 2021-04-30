#include <vector>

#include "Math/Mat.h"

#include "Core/core.h"
#include "Core/BaseNet.h"

#include "Layers/ActivationLayer.h"
#include "Layers/DenseLayer.h"

#include "Datasets/Iris.h"

int main() {
	srand((int)time(NULL));

	std::vector<AN::Mat> samples;
	std::vector<AN::Mat> labels;

	AN::get_iris_data_classification(samples, labels);

	AN::NeuralNet net(0.01);

	net.addLayer(AN::DenseLayer::create(4, 5));
	net.addLayer(AN::ActivationLayer::create(5, AN::ActivationFunc::SIGMOID));
	net.addLayer(AN::DenseLayer::create(5, 3));
	net.addLayer(AN::ActivationLayer::create(3, AN::ActivationFunc::SIGMOID));

	net.fit(samples, labels, 100);

}