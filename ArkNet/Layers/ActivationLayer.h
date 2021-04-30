#pragma once
#include <cmath>

#include "Layers/Layer.h"
#include "Math/Mat.h"
#include "Math/ArkMath.h"
namespace AN {

	enum class ActivationFunc {
		NONE = 0, SIGMOID, RELU, SOFTMAX, LEAKY_RELU
	};

	class ActivationLayer : public Layer {

	private:
		ActivationFunc m_actFunc = ActivationFunc::NONE;

	public:
		ARKNET_EXPORT static std::shared_ptr<ActivationLayer> create(size_t num_inputs, ActivationFunc type);

	public:
		ActivationLayer(size_t num_inputs, ActivationFunc type);
		void forward(Mat& input) override;
		Mat update(Mat& error, double lr) override;
	};
}