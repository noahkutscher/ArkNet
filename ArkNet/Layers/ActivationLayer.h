#pragma once
#include "Layers/Layer.h"
#include "Math/Mat.h"
#include "Math/ArkMath.h"
namespace AN {

	enum class ActivationFunc {
		NONE = 0, SIGMOID, RELU, SOFTMAX
	};

	class ActivationLayer : public Layer {

	public:
		static std::shared_ptr<ActivationLayer> create(size_t num_inputs, ActivationFunc type);

	public:
		ActivationLayer(size_t num_inputs, ActivationFunc type);
		void forward(Mat& input) override;
		Mat update(Mat& error, double lr) override;
	private:
		ActivationFunc m_actFunc = ActivationFunc::NONE;
	};
}