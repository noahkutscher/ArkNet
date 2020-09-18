#pragma once
#include <cmath>
#include <memory>
#include <iostream>

#include "Core/core.h"

namespace AN {

	class Mat {
	
	private:
		size_t m_rows;
		size_t m_cols;
		std::shared_ptr<double[]> m_data;
	
	public:
		Mat();
		Mat(Mat&);
		Mat(size_t rows, size_t cols);
		~Mat() = default;

		void add(Mat& src);
		void mul(Mat& src, Mat& dst) const;
		Mat operator+(Mat& src) const;
		Mat operator*(Mat& src) const;

		void copyTo(Mat& dst);
		void log();
		void realloc(size_t rows, size_t cols);
		void resize(size_t rows, size_t cols);

		inline double* data_raw() { return m_data.get(); }
		inline size_t rows() { return m_rows; }
		inline size_t cols() { return m_cols; }
		
		inline double& at(size_t row, size_t col) { 
			ARKNET_ASSERT(row < m_rows&& col < m_cols, "tried to get an item out pf range!");
			return m_data[row * m_cols + col];
		
		}
		inline double& at(size_t row, size_t col) const { return m_data[row * m_cols + col]; }

	public:
		static void mul(Mat& src1, Mat& src2, Mat& dst);

	};

}