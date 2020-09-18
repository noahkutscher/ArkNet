#include <time.h>

#include "core.h"
#include "BaseNet.h"
#include "Math/Mat.h"
#include "Layers/DenseLayer.h"

namespace AN {
	void TestFunctionality(const char* test) {

		srand(time(NULL));

		NeuralNet net;

		std::shared_ptr<DenseLayer> layer1 = std::make_shared<DenseLayer>(3,4);
		std::shared_ptr<DenseLayer> layer2 = std::make_shared<DenseLayer>(4,2);

		layer1->setActivation(AN::ActivationFunc::RELU);
		layer1->setActivation(AN::ActivationFunc::SIGMOID);

		net.addLayer(layer1);
		net.addLayer(layer2);

		Mat outMat;
		Mat inputMat(3, 1);
		inputMat.at(0, 0) = 1;
		inputMat.at(1, 0) = 2;
		inputMat.at(2, 0) = 1;

		net.predict(inputMat, outMat);

		outMat.log();
	}
}