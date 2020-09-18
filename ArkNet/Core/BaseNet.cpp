#include "BaseNet.h"

namespace AN {
	NeuralNet::NeuralNet()
	{
		m_numLayers = 0;
	}

	void NeuralNet::addLayer(std::shared_ptr<DenseLayer> layer)
	{
		m_numLayers++;
		m_layers.push_back(layer);
	}

	void NeuralNet::predict(Mat& input, Mat& output)
	{
		m_layers[0]->forward(input);

		for (int i = 1; i < m_numLayers; i++) {
			m_layers[i]->forward(m_layers[i - 1]->m_outBuffer);
		}

		m_layers[m_numLayers - 1]->m_outBuffer.copyTo(output);
	}
}
