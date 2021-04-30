#include "Core/core.h"
#include "DenseLayer.h"

namespace AN {

	std::shared_ptr<DenseLayer> DenseLayer::create(size_t num_inputs, size_t num_outputs)
	{
		return std::shared_ptr<DenseLayer>(new DenseLayer(num_inputs, num_outputs));
	}

	DenseLayer::DenseLayer(size_t num_inputs, size_t num_outputs) {
		m_inputs = num_inputs;
		m_outputs = num_outputs;

		m_inputBuffer.realloc(m_inputs, 1);
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

		ARKNET_ASSERT(input.rows() == m_weights.cols(), "Output size of layer must match the input size of the next layer");
		input.copyTo(m_inputBuffer);
		Mat::mul(m_weights, input, m_outBuffer);

		// m_outBuffer.add(m_bias);
	}

	Mat DenseLayer::update(Mat& error, double lr)
	{
		Mat grad;
		m_outBuffer.mul_elem(error, grad);

		Mat transposed = Mat::transpose(m_inputBuffer);
		Mat delta_weights = (grad * transposed) * lr;
		m_weights = m_weights + delta_weights;

		//printf("------------\n");
		//m_weights.log();

		return Mat::transpose(m_weights) * error;

	}

}
