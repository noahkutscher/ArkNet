#include "BaseNet.h"

namespace AN {
	NeuralNet::NeuralNet(double lr)
	{
		m_learningRate = lr;
		m_numLayers = 0;
	}

	void NeuralNet::addLayer(std::shared_ptr<Layer> layer)
	{
		m_numLayers++;
		m_layers.push_back(layer);
	}

	void NeuralNet::predict(Mat& input, Mat& output)
	{
		m_layers[0]->forward(input);

		for (size_t i = 1; i < m_numLayers; i++) {
			m_layers[i]->forward(m_layers[i - 1]->m_outBuffer);
		}

		m_layers[m_numLayers - 1]->m_outBuffer.copyTo(output);

	}

	void NeuralNet::debugOutBuffers()
	{
		for (std::shared_ptr<Layer> l : m_layers) {
			printf("--------\n");
			l->m_outBuffer.log();
		}
	}



	void NeuralNet::fit(std::vector<Mat>& inputs, std::vector<Mat>& labels, size_t numEpochs)
	{
		
		ARKNET_ASSERT(inputs.size() == labels.size(), "number of inputs and outputs doesnt match");

		Mat pred;
		Mat error;
		Mat sq_error;
		Mat deriv_error;

		for (int e = 0; e < numEpochs; e++) {
			double mse = 0.0;
			for (int i = 0; i < inputs.size(); i++) {
				predict(inputs[i], pred);
				error = (labels[i] - pred);
				error.mul_elem(error, sq_error);
				mse += Mat::sum(sq_error) / sq_error.size();

				//epoch_ce += Mat::sum(labels[i] * -1 * Mat::log(pred));

				deriv_error = error * 2;

				for (int layer_idx = m_numLayers - 1; layer_idx >= 0; layer_idx--) {
					deriv_error = m_layers[layer_idx]->update(deriv_error, m_learningRate);
				}
			}
			mse /= inputs.size();
			printf("Mean Square Error: %f\n", mse);
		}


	}
}
