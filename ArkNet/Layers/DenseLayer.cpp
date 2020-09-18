#include "DenseLayer.h"


namespace AN {

	DenseLayer::DenseLayer(size_t num_inputs, size_t num_outputs) {
		//num_inputs + 1 for bias
		m_inputs = num_inputs + 1;
		m_outputs = num_outputs;
		m_outBuffer.resize(m_outputs, 1);
		m_weights.resize(m_outputs, m_inputs);

		for (int i = 0; i < m_weights.rows(); i++) {
			for (int j = 0; j < m_weights.cols(); j++) {
				double init_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

				//init_value = 1.0;

				init_value = (init_value * 2) - 1.0;
				m_weights.at(i, j) = init_value;
			}
		}
	}

	void DenseLayer::test()
	{
	}

	// ToDo: Add bias
	void DenseLayer::forward(Mat& input)
	{
		if (input.rows() != m_weights.cols()) {
			printf("[ERROR] Output size of layer must match the input size of the next layer\n");
			return;
		}

		Mat::mul(m_weights, input, m_outBuffer);
		activate();
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
