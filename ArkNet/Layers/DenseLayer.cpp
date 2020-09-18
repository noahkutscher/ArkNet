#include "Core/core.h"
#include "DenseLayer.h"

namespace AN {

	DenseLayer::DenseLayer(size_t num_inputs, size_t num_outputs) {
		m_inputs = num_inputs;
		m_outputs = num_outputs;
		m_outBuffer.realloc(m_outputs, 1);
		m_bias.realloc(m_outputs, 1);
		m_weights.realloc(m_outputs, m_inputs);
		
		double init_value;
		for (int i = 0; i < m_weights.rows(); i++) {
			for (int j = 0; j < m_weights.cols(); j++) {
				init_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
				init_value = (init_value * 2) - 1.0;
				m_weights.at(i, j) = init_value;
			}
		}

		for (int i = 0; i < m_bias.rows(); i++) {
			init_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
			init_value = (init_value * 2) - 1.0;
			m_bias.at(i, 0) = init_value;
		}
	}

	void DenseLayer::forward(Mat& input)
	{
		if (input.rows() != m_weights.cols()) {
			ARKNET_ERROR("Output size of layer must match the input size of the next layer");
			return;
		}

		Mat::mul(m_weights, input, m_outBuffer);
		m_outBuffer.add(m_bias);
		activate();
	}

	void DenseLayer::backprob() {

	}

	void DenseLayer::activate()
	{
		switch (m_actFunc) {
		case ActivationFunc::SIGMOID:
			for (int i = 0; i < m_outputs; i++) {
				m_outBuffer.at(i, 0) = sigmoid(m_outBuffer.at(i, 0));
			}
			break;
		case ActivationFunc::RELU:
			for (int i = 0; i < m_outputs; i++) {
				m_outBuffer.at(i, 0) = m_outBuffer.at(i, 0) < 0 ? 0 : m_outBuffer.at(i, 0);
			}
			break;
		default:
			break;
		}
	}

	void DenseLayer::setActivation(ActivationFunc actFunc)
	{
		m_actFunc = actFunc;
	}

}
