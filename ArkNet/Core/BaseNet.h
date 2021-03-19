#pragma once
#include <vector>
#include <memory>

#include "Layers/DenseLayer.h"
#include "Layers/Layer.h"
#include "Math/ArkMath.h"
#include "Math/Mat.h"

namespace AN {

	class NeuralNet {
	private:
		std::vector<std::shared_ptr<Layer>> m_layers;
		double m_learningRate;
		int m_numLayers = 0;

	public:
		ARKNET_EXPORT NeuralNet(double lr);
		ARKNET_EXPORT ~NeuralNet() = default;

		ARKNET_EXPORT void addLayer(std::shared_ptr<Layer> layer);
		ARKNET_EXPORT void predict(Mat& input, Mat& output);
		ARKNET_EXPORT void fit(std::vector<Mat>& inputs, std::vector<Mat>& labels, size_t numEpochs);
		ARKNET_EXPORT void debugOutBuffers();
	};

}
