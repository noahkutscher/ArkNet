#pragma once
#include "Math/Mat.h"
namespace AN {
	class Layer {

	public:
		int m_inputs = 0;
		int m_outputs = 0;
		Mat m_inputBuffer;
		Mat m_outBuffer;

		virtual void forward(Mat& input) = 0;
		virtual Mat update(Mat& error, double lr) = 0;
	};
}