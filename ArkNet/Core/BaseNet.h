#pragma once
#include <vector>
#include <memory>

#include "Layers/DenseLayer.h"

namespace AN {

	class NeuralNet {
	public:
		int m_numLayers;

		NeuralNet();
		~NeuralNet() = default;

		std::vector<std::shared_ptr<DenseLayer>> m_layers;
		void addLayer(std::shared_ptr<DenseLayer> layer);
		void predict(Mat& input, Mat& output);
	};

}
