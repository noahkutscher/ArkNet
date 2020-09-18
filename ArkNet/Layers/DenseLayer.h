#pragma once 
#include "Math/Mat.h"
#include "Math/ArkMath.h"

namespace AN {

	enum class ActivationFunc {
		NONE = 0, SIGMOID, RELU 
	};

	class DenseLayer {

	public:
		int m_inputs;
		int m_outputs;
		Mat m_weights;
		Mat m_bias;
		Mat m_outBuffer;

		DenseLayer(size_t num_inputs, size_t num_outputs);

		void activate();
		void forward(Mat& input);
		void backprob();
		void setActivation(ActivationFunc actFunc);

	private:
		ActivationFunc m_actFunc = ActivationFunc::NONE;


	};
	
}
