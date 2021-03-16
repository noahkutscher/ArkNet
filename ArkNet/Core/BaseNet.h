#pragma once
#include <vector>
#include <memory>

#include "Layers/DenseLayer.h"
#include "Layers/Layer.h"
#include "Math/ArkMath.h"
#include "Math/Mat.h"

namespace AN {

	class NeuralNet {
	public:
		double m_learningRate;
		int m_numLayers = 0;

		NeuralNet(double lr);
		~NeuralNet() = default;

		std::vector<std::shared_ptr<Layer>> m_layers;
		void addLayer(std::shared_ptr<Layer> layer);
		void predict(Mat& input, Mat& output);
		void fit(std::vector<Mat>& inputs, std::vector<Mat>& labels, size_t numEpochs);
		void debugOutBuffers();
	};

}
