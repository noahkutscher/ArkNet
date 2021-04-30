#pragma once
#include <cmath>
#include <memory>
#include <iostream>
#include <cstring>

#include "Core/core.h"

namespace AN {

	class Mat {

	public:
		ARKNET_EXPORT static void mul(Mat& src1, Mat& src2, Mat& dst);
		ARKNET_EXPORT static Mat abs(Mat& src1);
		ARKNET_EXPORT static double sum(Mat& src);
		ARKNET_EXPORT static Mat transpose(Mat& src);
		ARKNET_EXPORT static Mat log(Mat& src);
	
	private:
		size_t m_rows;
		size_t m_cols;
		std::shared_ptr<double[]> m_data;
	
	public:
		ARKNET_EXPORT Mat();
		ARKNET_EXPORT Mat(size_t rows, size_t cols);
		ARKNET_EXPORT ~Mat() = default;

		ARKNET_EXPORT void copyTo(Mat& dst);
		ARKNET_EXPORT void log();
		ARKNET_EXPORT void realloc(size_t rows, size_t cols);
		ARKNET_EXPORT void reset(double* ptr);
		ARKNET_EXPORT void resize(size_t rows, size_t cols);
		ARKNET_EXPORT void add(Mat& src);

		ARKNET_EXPORT void mul(Mat& src, Mat& dst) const;
		ARKNET_EXPORT void mul(double scalar, Mat& dst) const;
		ARKNET_EXPORT void mul_elem(Mat& src, Mat& dst) const;

		ARKNET_EXPORT Mat operator+(Mat& src) const;
		ARKNET_EXPORT Mat operator-(Mat& src) const;
		ARKNET_EXPORT Mat operator*(Mat& src) const;
		ARKNET_EXPORT Mat operator*(double scalar) const;

		ARKNET_EXPORT inline double* data_raw() const { return m_data.get(); }
		ARKNET_EXPORT inline size_t rows() const { return m_rows; }
		ARKNET_EXPORT inline size_t cols() const { return m_cols; }
		ARKNET_EXPORT inline size_t size() const { return (m_cols * m_rows); }

		ARKNET_EXPORT inline double max();
		
		ARKNET_EXPORT inline double& at(size_t row, size_t col) const {
			ARKNET_ASSERT(row < m_rows&& col < m_cols, "tried to get an item out of range!");
			return m_data[row * m_cols + col];
		
		}

		ARKNET_EXPORT inline double& at(size_t idx) const {
			ARKNET_ASSERT(idx < size(), "tried to get an item out of range!");
			return m_data[idx];

		}

	};

}