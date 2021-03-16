#include "Layers/ActivationLayer.h"
namespace AN {

	std::shared_ptr<ActivationLayer> ActivationLayer::create(size_t num_inputs, ActivationFunc type)
	{
		return std::shared_ptr<ActivationLayer>(new ActivationLayer(num_inputs, type));
	}

	ActivationLayer::ActivationLayer(size_t num_inputs, ActivationFunc type) {
		m_inputs = num_inputs;
		m_outputs = num_inputs;
		m_outBuffer.realloc(num_inputs, 1);
		m_actFunc = type;
	}

	void ActivationLayer::forward(Mat& input)
	{
		//ToDo: Better reference generation at this point!!!
		m_inputBuffer = input;
		switch (m_actFunc) {
		case ActivationFunc::SIGMOID:
			for (int i = 0; i < m_outputs; i++) {
				m_outBuffer.at(i) = sigmoid(input.at(i));
			}
			break;
		case ActivationFunc::RELU:
			for (int i = 0; i < m_outputs; i++) {
				m_outBuffer.at(i) = input.at(i) < 0 ? 0 : input.at(i);
			}
			break;
		default:
			ARKNET_ASSERT(false, "Prediction for given Activation function not implemented");
		}
	}

	Mat ActivationLayer::update(Mat& error, double lr)
	{
		// transfomr the output of the previous layer using the deriv of the activation
		switch (m_actFunc){
		case ActivationFunc::SIGMOID:
			for (size_t i = 0; i < m_inputs; i++)
				m_inputBuffer.at(i) = sigmoid_deriv(m_inputBuffer.at(i));
			break;
		case ActivationFunc::RELU:
			for (int i = 0; i < m_outputs; i++) {
				m_inputBuffer.at(i) = m_inputBuffer.at(i) < 0 ? 0 : 1;
			}
			break;
		default:
			ARKNET_ASSERT(false, "Backprop for given Activation function not implemented");
		}
		return error;
	}

}