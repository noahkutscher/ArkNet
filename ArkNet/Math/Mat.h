#pragma once
#include <memory>
#include <iostream>

namespace AN {

	class Mat {
	
	private:
		size_t m_rows;
		size_t m_cols;
		std::unique_ptr<double[]> m_data;
	
	public:
		Mat();
		Mat(size_t rows, size_t cols);
		~Mat() = default;

		double& at(size_t row, size_t col);
		void copyTo(Mat& dst);
		void log();
		void resize(size_t rows, size_t cols);

		inline double* data_raw() { return m_data.get(); }
		inline size_t rows() { return m_rows; }
		inline size_t cols() { return m_cols; }

	public:
		static void mul(Mat& src1, Mat& src2, Mat& dst);

	};

}