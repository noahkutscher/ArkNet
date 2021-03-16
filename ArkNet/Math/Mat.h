#pragma once
#include <cmath>
#include <memory>
#include <iostream>

#include "Core/core.h"

namespace AN {

	class Mat {

	public:
		static void mul(Mat& src1, Mat& src2, Mat& dst);
		static Mat abs(Mat& src1);
		static double sum(Mat& src);
		static Mat transpose(Mat& src);
	
	private:
		size_t m_rows;
		size_t m_cols;
		std::shared_ptr<double[]> m_data;
	
	public:
		Mat();
		Mat(size_t rows, size_t cols);
		~Mat() = default;

		void copyTo(Mat& dst);
		void log();
		void realloc(size_t rows, size_t cols);
		void reset(double* ptr);
		void resize(size_t rows, size_t cols);
		void add(Mat& src);

		void mul(Mat& src, Mat& dst) const;
		void mul(double scalar, Mat& dst) const;
		void mul_elem(Mat& src, Mat& dst) const;

		Mat operator+(Mat& src) const;
		Mat operator-(Mat& src) const;
		Mat operator*(Mat& src) const;
		Mat operator*(double scalar) const;

		inline double* data_raw() const { return m_data.get(); }
		inline size_t rows() const { return m_rows; }
		inline size_t cols() const { return m_cols; }
		inline size_t size() const { return (m_cols * m_rows); }
		
		inline double& at(size_t row, size_t col) const { 
			ARKNET_ASSERT(row < m_rows&& col < m_cols, "tried to get an item out of range!");
			return m_data[row * m_cols + col];
		
		}

		inline double& at(size_t idx) const {
			ARKNET_ASSERT(idx < size(), "tried to get an item out of range!");
			return m_data[idx];

		}

	};

}