#pragma once 
#include "Math/Mat.h"
#include "Math/ArkMath.h"
#include "Layers/Layer.h"

namespace AN {



	class DenseLayer : public Layer {

	public:
		static std::shared_ptr<DenseLayer> create(size_t num_inputs, size_t num_outputs);

	public:

		Mat m_weights;
		Mat m_bias;

		DenseLayer(size_t num_inputs, size_t num_outputs);


		void forward(Mat& input) override;
		Mat update(Mat& error, double lr) override;
	
	};
	
}
