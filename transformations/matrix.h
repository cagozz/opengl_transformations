#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Mat4f
{
private:
	float data[16];
public:
	Mat4f(float a00, float a01, float a02, float a03,
		  float a10, float a11, float a12, float a13,
		  float a20, float a21, float a22, float a23,
		  float a30, float a31, float a32, float a33)
		:
		data{ a00, a01, a02, a03,
	          a10, a11, a12, a13,
			  a20, a21, a22, a23,
			  a30, a31, a32, a33 } {}

	Mat4f(float diag) :
		data { diag, 0, 0, 0,
			   0, diag, 0, 0,
			   0, 0, diag, 0,
			   0, 0, 0, diag } {}

	Mat4f() : 
		data { 0, 0, 0, 0,
			   0, 0, 0, 0,
			   0, 0, 0, 0,
			   0, 0, 0, 0 } {}
	
	void set(float a00, float a01, float a02, float a03,
			 float a10, float a11, float a12, float a13,
			 float a20, float a21, float a22, float a23,
			 float a30, float a31, float a32, float a33)
	{
		data[0]  = a00; data[1] = a01;  data[2]  = a02; data[3]  = a03;
		data[4]  = a10; data[5] = a11;  data[6]  = a12; data[7]  = a13;
		data[8]  = a20; data[9] = a21;  data[10] = a22; data[11] = a23;
		data[12] = a30; data[13] = a31; data[14] = a32; data[15] = a33;
	}

	float* get() { return data; }
	
	float& operator[](int index) { return data[index]; }

	Mat4f operator*(const Mat4f& r)
	{
		Mat4f result(	data[0]  * r.data[0] + data[1]  * r.data[4] + data[2]  * r.data[8]  + data[3]  * r.data[12],
						data[0]  * r.data[1] + data[1]  * r.data[5] + data[2]  * r.data[9]  + data[3]  * r.data[13],
						data[0]  * r.data[2] + data[1]  * r.data[6] + data[2]  * r.data[10] + data[3]  * r.data[14],
						data[0]  * r.data[3] + data[1]  * r.data[7] + data[2]  * r.data[11] + data[3]  * r.data[15],
													    
						data[4]  * r.data[0] + data[5]  * r.data[4] + data[6]  * r.data[8]  + data[7]  * r.data[12],
						data[4]  * r.data[1] + data[5]  * r.data[5] + data[6]  * r.data[9]  + data[7]  * r.data[13],
						data[4]  * r.data[2] + data[5]  * r.data[6] + data[6]  * r.data[10] + data[7]  * r.data[14],
						data[4]  * r.data[3] + data[5]  * r.data[7] + data[6]  * r.data[11] + data[7]  * r.data[15],
													    
						data[8]  * r.data[0] + data[9]  * r.data[4] + data[10] * r.data[8]  + data[11] * r.data[12],
						data[8]  * r.data[1] + data[9]  * r.data[5] + data[10] * r.data[9]  + data[11] * r.data[13],
						data[8]  * r.data[2] + data[9]  * r.data[6] + data[10] * r.data[10] + data[11] * r.data[14],
						data[8]  * r.data[3] + data[9]  * r.data[7] + data[10] * r.data[11] + data[11] * r.data[15],

						data[12] * r.data[0] + data[13] * r.data[4] + data[14] * r.data[8]  + data[15] * r.data[12],
						data[12] * r.data[1] + data[13] * r.data[5] + data[14] * r.data[9]  + data[15] * r.data[13],
						data[12] * r.data[2] + data[13] * r.data[6] + data[14] * r.data[10] + data[15] * r.data[14],
						data[12] * r.data[3] + data[13] * r.data[7] + data[14] * r.data[11] + data[15] * r.data[15] );


		return result;
	}

	Mat4f inverse()
	{
        Mat4f result;
        result[0] = data[5] * data[10] * data[15] -
                    data[5] * data[11] * data[14] -
                    data[9] * data[6] * data[15] +
                    data[9] * data[7] * data[14] +
                    data[13] * data[6] * data[11] -
                    data[13] * data[7] * data[10];

        result[4] = -data[4] * data[10] * data[15] +
                    data[4] * data[11] * data[14] +
                    data[8] * data[6] * data[15] -
                    data[8] * data[7] * data[14] -
                    data[12] * data[6] * data[11] +
                    data[12] * data[7] * data[10];

        result[8] = data[4] * data[9] * data[15] -
                    data[4] * data[11] * data[13] -
                    data[8] * data[5] * data[15] +
                    data[8] * data[7] * data[13] +
                    data[12] * data[5] * data[11] -
                    data[12] * data[7] * data[9];

        result[12] = -data[4] * data[9] * data[14] +
                      data[4] * data[10] * data[13] +
                      data[8] * data[5] * data[14] -
                      data[8] * data[6] * data[13] -
                      data[12] * data[5] * data[10] +
                      data[12] * data[6] * data[9];

        result[1] = -data[1] * data[10] * data[15] +
                    data[1] * data[11] * data[14] +
                    data[9] * data[2] * data[15] -
                    data[9] * data[3] * data[14] -
                    data[13] * data[2] * data[11] +
                    data[13] * data[3] * data[10];

        result[5] = data[0] * data[10] * data[15] -
                    data[0] * data[11] * data[14] -
                    data[8] * data[2] * data[15] +
                    data[8] * data[3] * data[14] +
                    data[12] * data[2] * data[11] -
                    data[12] * data[3] * data[10];

        result[9] = -data[0] * data[9] * data[15] +
                    data[0] * data[11] * data[13] +
                    data[8] * data[1] * data[15] -
                    data[8] * data[3] * data[13] -
                    data[12] * data[1] * data[11] +
                    data[12] * data[3] * data[9];

        result[13] = data[0] * data[9] * data[14] -
                    data[0] * data[10] * data[13] -
                    data[8] * data[1] * data[14] +
                    data[8] * data[2] * data[13] +
                    data[12] * data[1] * data[10] -
                    data[12] * data[2] * data[9];

        result[2] = data[1] * data[6] * data[15] -
                    data[1] * data[7] * data[14] -
                    data[5] * data[2] * data[15] +
                    data[5] * data[3] * data[14] +
                    data[13] * data[2] * data[7] -
                    data[13] * data[3] * data[6];

        result[6] = -data[0] * data[6] * data[15] +
                    data[0] * data[7] * data[14] +
                    data[4] * data[2] * data[15] -
                    data[4] * data[3] * data[14] -
                    data[12] * data[2] * data[7] +
                    data[12] * data[3] * data[6];

        result[10] = data[0] * data[5] * data[15] -
                    data[0] * data[7] * data[13] -
                    data[4] * data[1] * data[15] +
                    data[4] * data[3] * data[13] +
                    data[12] * data[1] * data[7] -
                    data[12] * data[3] * data[5];

        result[14] = -data[0] * data[5] * data[14] +
                    data[0] * data[6] * data[13] +
                    data[4] * data[1] * data[14] -
                    data[4] * data[2] * data[13] -
                    data[12] * data[1] * data[6] +
                    data[12] * data[2] * data[5];

        result[3] = -data[1] * data[6] * data[11] +
                    data[1] * data[7] * data[10] +
                    data[5] * data[2] * data[11] -
                    data[5] * data[3] * data[10] -
                    data[9] * data[2] * data[7] +
                    data[9] * data[3] * data[6];

        result[7] = data[0] * data[6] * data[11] -
                    data[0] * data[7] * data[10] -
                    data[4] * data[2] * data[11] +
                    data[4] * data[3] * data[10] +
                    data[8] * data[2] * data[7] -
                    data[8] * data[3] * data[6];

        result[11] = -data[0] * data[5] * data[11] +
                     data[0] * data[7] * data[9] +
                     data[4] * data[1] * data[11] -
                     data[4] * data[3] * data[9] -
                     data[8] * data[1] * data[7] +
                     data[8] * data[3] * data[5];

        result[15] = data[0] * data[5] * data[10] -
                     data[0] * data[6] * data[9] -
                     data[4] * data[1] * data[10] +
                     data[4] * data[2] * data[9] +
                     data[8] * data[1] * data[6] -
                     data[8] * data[2] * data[5];

        float det = data[0] * result[0] + data[1] * result[4] + data[2] * result[8] + data[3] * result[12];
        if (det == 0)
            return Mat4f(1);

        det = 1.0 / det;

        for (int i = 0; i < 16; i++)
            result[i] = result[i] * det;

        return result;
	}

    Mat4f transpose()
    {
        Mat4f result;

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result[i * 4 + j] = data[j * 4 + i];
            }
        }  

        return result;
    }

    Vec3f operator*(Vec3f vec)
    {
        Vec3f result;

        result.x() = data[0] * vec.x() + data[1] * vec.y() + data[2] * vec.z();
        result.y() = data[4] * vec.x() + data[5] * vec.y() + data[6] * vec.z();
        result.z() = data[8] * vec.x() + data[9] * vec.y() + data[10] * vec.z();

        return result;
    }

	friend std::ostream& operator<<(std::ostream& os, const Mat4f& v);
};

inline std::ostream& operator<<(std::ostream& os, const Mat4f& m)
{
	os << "\n";
	os << m.data[0]  << "\t" << m.data[1]  << "\t" << m.data[2]  << "\t" << m.data[3]  << std::endl;
	os << m.data[4]  << "\t" << m.data[5]  << "\t" << m.data[6]  << "\t" << m.data[7]  << std::endl;
	os << m.data[8]  << "\t" << m.data[9]  << "\t" << m.data[10] << "\t" << m.data[11] << std::endl;
	os << m.data[12] << "\t" << m.data[13] << "\t" << m.data[14] << "\t" << m.data[15] << std::endl;
	return os;
}

class Mat3f
{
private:
	float data[9];
public:

	Mat3f(float a00, float a01, float a02,
		  float a10, float a11, float a12,
		  float a20, float a21, float a22)
		:
		data{ a00, a01, a02, 
			  a10, a11, a12, 
			  a20, a21, a22 } {}

	Mat3f(float diag) :
		data{  diag, 0,  0, 
			   0,  diag, 0,
			   0,    0, diag} {}
	Mat3f() : 
		data { 0, 0, 0,
			   0, 0, 0,
			   0, 0, 0} {}
};

#endif // !MATRIX_H
