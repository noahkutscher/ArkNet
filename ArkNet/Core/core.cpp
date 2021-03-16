#include <time.h>

#include "Core/core.h"
#include "Core/BaseNet.h"
#include "Math/Mat.h"
#include "Layers/DenseLayer.h"
#include "Layers/ActivationLayer.h"

#include "Datasets/Iris.h"




namespace AN {

	

	void TestFunctionality(const char* test) {

		srand(time(NULL));
		std::vector<Mat> samples;
		std::vector<Mat> labels;
		get_iris_data_classification(samples, labels);

		NeuralNet net(0.01);

		net.addLayer(DenseLayer::create(4, 5));
		net.addLayer(ActivationLayer::create(5, ActivationFunc::SIGMOID));
		net.addLayer(DenseLayer::create(5, 3));
		net.addLayer(ActivationLayer::create(3, ActivationFunc::SIGMOID));

		net.fit(samples, labels, 100);

	}
}